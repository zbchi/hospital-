#include "function.h"
void adddel()
{
    while (1)
    {
        printf("\n1.添加医生\n2.添加患者\n3.删除医生\n4.删除患者\n0.返回上级\n");
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
            add_patient(fp2, name2, id2);
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
            printf("数字无效，请重新输入\n");
            clear();
            continue;
        }
    }
}

void print()
{
    while (1)
    {
        printf("\n1.打印全体医生信息\n2.打印全体患者信息\n0.返回上级\n");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':
            int count = 0;
            struct doctor *doctors = load_doctor(&count);
            for (int i = 0; i < count; i++)
                printf("%-16s\t%8d\t%-16s\t\n", doctors[i].name, doctors[i].id, doctors[i].dept);
            free(doctors);
            break;
        case '2':
            int count2;
            struct patient *patients = load_patient(&count2);
            for (int i = 0; i < count2; i++)
                printf("%-16s\t%8d\t\n", patients[i].name, patients[i].id);
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
    FILE *fp = fopen("patient.txt", "w");
    add_patient(fp, p.name, p.id);
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

    free(doctors);
}
