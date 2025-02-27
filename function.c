#include "function.h"
void any_continue()
{
    clear();
    printf("按回车以继续:");
    getchar();
}

void get_date(char *date)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(date, 20, "%Y-%m-%d", tm);
}

struct registration *load_registration(int *count)
{
    *count = 0;
    int size = 64;
    FILE *fp = fopen("registration.txt", "r");
    struct registration tmp;
    struct registration *reg = (struct registration *)malloc(sizeof(struct registration) * 64);
    while (fscanf(fp, "%d %d %s", &tmp.doctor_id, &tmp.patient_id, tmp.date) == 3)
    {
        if (*count > size)
        {
            size *= 2;
            struct registration *new = realloc(reg, size * sizeof(struct registration));
            reg = new;
        }
        reg[*count].doctor_id = tmp.doctor_id;
        reg[*count].patient_id = tmp.patient_id;
        strcpy(reg[*count].date, tmp.date);
        (*count)++;
    }
    return reg;
}

void add_registration(int doctor_id, int patient_id, char *date)
{
    FILE *fp = fopen("registration.txt", "a");
    int result = fprintf(fp, "%d  %d  %s\n", doctor_id, patient_id, date);
    if (result < 0)
        printf("挂号失败\n");

    else
        printf("挂号成功\n");

    sleep(1);
    fclose(fp);
}
void adddel()
{
    while (1)
    {
        printf("\n1.添加医生\n2.添加患者\n3.移除医生\n4.移除患者\n0.返回上级\n");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':
            FILE *fp1 = fopen("doctor.txt", "a");

            printf("输入医生姓名：");
            char name1[64];
            scanf(" %s", name1);
            printf("输入医生ID:");
            int id1;
            scanf(" %d", &id1);
            printf("输入医生科室：");
            char dept[64];
            scanf(" %s", dept);

            add_doctor(fp1, name1, id1, dept);
            fclose(fp1);

            break;
        case '2':
            FILE *fp2 = fopen("patient.txt", "a");

            printf("输入患者姓名：");
            char name2[64];
            scanf(" %s", name2);
            printf("输入患者ID：");
            int id2;
            scanf(" %d", &id2);
            add_patient(fp2, name2, id2, 0);
            fclose(fp2);

            break;

        case '3':
            del_doctor();
            break;

        case '4':
            del_patient();
            break;

        case '0':
            return;
        default:
            printf("\n数字无效,请重新输入\n");
            clear();
            continue;
        }
    }
}

void print()
{
    while (1)
    {
        printf("\n1.打印全体医生信息\n2.打印全体患者信息\n3.打印所有挂号记录\n0.返回上级\n");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':
            print_doctors();
            break;
        case '2':
            print_patients();
            break;
        case '3':
            print_registration();
            break;
        case '0':
            return;
        default:
            clear();
            break;
        }
    }
}

void Register()
{
    char name[64];
    int id;
    struct patient p;
    printf("请输入患者姓名：");
    scanf("%s", p.name);
    printf("请输入患者ID:");
    scanf(" %d", &p.id);
    FILE *fp = fopen("patient.txt", "a");
    add_patient(fp, p.name, p.id, 1);
    fclose(fp);

    int count = 0;

    int dept_count = 0;
    char dept[20][50];
    struct doctor *doctors = load_doctor(&count);
    for (int i = 0; i < count; i++)
    {
        int exist = 0;
        for (int j = 0; j < dept_count; j++)
        {
            if (strcmp(doctors[i].dept, dept[j]) == 0)
            {
                exist = 1;
                break;
            }
        }
        if (!exist)
        {
            strcpy(dept[dept_count++], doctors[i].dept);
        }
    }

loop:
    printf("\n可选的科室:\n");
    for (int i = 0; i < dept_count; i++)
        printf("%d.%s\n", i + 1, dept[i]);
    int which;
    printf("0.返回上级\n");
    printf("请输入科室的编号:");
    clear();
    scanf(" %d", &which);
    if (which < 0 || which > dept_count)
    {
        printf("无效的编号\n");
        sleep(1);
        goto loop;
    }
    else if (which == 0)
        return;
leep:
    int suoyin[50] = {0};
    printf("\n可选择的医生:\n");
    char doctorName[20][50];
    int nameCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(doctors[i].dept, dept[which - 1]) == 0)
        {
            suoyin[nameCount + 1] = i;
            strcpy(doctorName[nameCount++], doctors[i].name);
            printf("%d.%s\n", nameCount, doctorName[nameCount - 1]);
        }
    }
    printf("0.返回上级\n\n");
    printf("请输入医生的编号:");
    int whichdoctor;
    clear();
    scanf(" %d", &whichdoctor);
    if (whichdoctor == 0)
    {
        for (int i = 0; i < dept_count; i++)
            printf("%d.%s\n", i + 1, dept[i]);
        goto loop;
    }
    if (whichdoctor < 0 || whichdoctor > nameCount)
    {
        printf("无效的编号\n");
        sleep(1);
        goto leep;
    }

    struct registration r;
    r.patient_id = p.id;
    r.doctor_id = doctors[suoyin[whichdoctor]].id;

    char date[12];
    get_date(date);
    add_registration(r.doctor_id, r.patient_id, date);
    free(doctors);
}

void print_registration()
{
    int count;
    struct registration *reg = load_registration(&count);
    for (int i = 0; i < count; i++)
        printf("%8d\t%8d\t%-12s\t\n", reg[i].doctor_id, reg[i].patient_id, reg[i].date);
    free(reg);

    any_continue();
}
void print_doctors()
{
    int count = 0;
    struct doctor *doctors = load_doctor(&count);
    for (int i = 0; i < count; i++)
        printf("%-16s\t%8d\t%-16s\t\n", doctors[i].name, doctors[i].id, doctors[i].dept);
    free(doctors);
    any_continue();
}
void print_patients()
{
    int count = 0;
    struct patient *patients = load_patient(&count);
    for (int i = 0; i < count; i++)
        printf("%-16s\t%8d\t\n", patients[i].name, patients[i].id);
    free(patients);
    any_continue();
}

void unregister()
{
    printf("请输入患者ID:");
    int id;

    scanf(" %d", &id);

    // printf("------------------------\n");
    printf("\n输入需要退号的编号:\n");

    // struct registration* unreg=(struct registration*)malloc(sizeof(struct registration));
    // struct registration unreg[10];

loop:
    int undoctor_id[10] = {0};
    char date[10][12];
    int undoctor_count = 0;
    struct doctor undoctor[10];

    print_reg_patient(id, undoctor_id, date, &undoctor_count, undoctor);

    if (undoctor_count == 0)
    {
        printf("\n你还没有挂号\n");
        sleep(1);
        return;
    }
    int which;

    scanf("%d", &which);
    if (which < 1 || which > undoctor_count)
        goto loop;
    which--;

    struct registration unreg;
    strcpy(unreg.date, date[which]);
    unreg.doctor_id = undoctor[which].id;
    unreg.patient_id = id;

    del_registration(&unreg);
}

void del_registration(struct registration *unreg)
{
    // printf("%d %d %s", unreg->doctor_id, unreg->patient_id, unreg->date);
    FILE *fp = fopen("registration.txt", "r");
    FILE *tmp = fopen("tmp.txt", "w");
    struct registration regtmp;
    while (fscanf(fp, "%d %d %s", &regtmp.doctor_id, &regtmp.patient_id, regtmp.date) == 3)
    {
        if (unreg->doctor_id == regtmp.doctor_id && unreg->patient_id == regtmp.patient_id && strcmp(regtmp.date, unreg->date) == 0)
            continue;

        else
            fprintf(tmp, "%d  %d  %s\n", regtmp.doctor_id, regtmp.patient_id, regtmp.date);
    }
    fclose(fp);
    fclose(tmp);
    remove("registration.txt");
    rename("tmp.txt", "registration.txt");
    printf("退号成功\n");
    sleep(1);
}

void print_reg_patient(int id, int *undoctor_id, char (*date)[12], int *undoctor_count, struct doctor *undoctor)
{
    int count = 0;
    struct registration *reg = load_registration(&count);
    // printf("------------------------\n");

    for (int i = 0; i < count; i++)
    {
        if (id == reg[i].patient_id)
        {
            undoctor_id[*undoctor_count] = reg[i].doctor_id;
            strcpy(date[*undoctor_count], reg[i].date);
            (*undoctor_count)++;
        }
    }

    // printf("%d", undoctor_id[0]);

    count = 0;
    struct doctor *doctor = load_doctor(&count);
    // printf("------------------------\n");

    for (int i = 0; i < *undoctor_count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (undoctor_id[i] == doctor[j].id)
            {
                strcpy(undoctor[i].name, doctor[j].name);
                strcpy(undoctor[i].dept, doctor[j].dept);
                undoctor[i].id = doctor[j].id;
            }
        }
    }

    free(doctor);
    free(reg);

    for (int i = 0; i < *undoctor_count; i++)
    {
        printf("%d.医生姓名:%-16s\t所属科室:%-16s\t医生ID:%8d\t日期:%-12s\t\n", i + 1, undoctor[i].name, undoctor[i].dept, undoctor[i].id, date[i]);
    }
}

void patient_search()
{

    printf("请输入患者ID:");
    int id;

    scanf(" %d", &id);

    printf("\n你的挂号记录:\n");

    int undoctor_id[10] = {0};
    char date[10][12];
    int undoctor_count = 0;
    struct doctor undoctor[10];

    print_reg_patient(id, undoctor_id, date, &undoctor_count, undoctor);

    if (undoctor_count == 0)
    {
        printf("\n你还没有挂号\n");
        sleep(1);
        return;
    }
    any_continue();
}