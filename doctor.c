
#include "doctor.h"

void clear()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}
void add_doctor(FILE *fp, char *name, int id, char *dept)
{
    int count = 0;
    struct doctor *d = load_doctor(&count);
loop:
    for (int i = 0; i < count; i++)
    {
        if (id == d[i].id)
        {
            printf("\nID重复,请重新输入ID:");
            scanf(" %d", &id);
            goto loop;
        }
    }

    free(d);

    int result = fprintf(fp, "%s  %d  %s \n", name, id, dept);
    if (result < 0)
        printf("添加失败\n");
    else
        printf("添加成功\n");
    sleep(1);
}
void del_doctor()
{
    while (1)
    {
        printf("\n1.通过姓名移除医生\n2.通过ID移除医生\n0.返回上级\n");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':
            printf("请输入医生姓名：");
            char name[64];
            scanf("%s", name);
            del_doctor_bynameid(name, -1);
            break;

        case '2':
            printf("请输入医生ID：");
            int id;
            scanf("%d", &id);
            del_doctor_bynameid(NULL, id);
            break;

        case '0':
            return;
        default:
            printf("数字无效，请重新输入");
            clear();
        }
    }
}
void del_doctor_bynameid(char *name, int id)
{
    FILE *fp = fopen("doctor.txt", "r");
    FILE *tmp = fopen("tmp_doctor.txt", "w");
    struct doctor d;
    int found = 0;
    while (fscanf(fp, "%63s %d %63s", d.name, &d.id, d.dept) == 3)
    {

        if (id == -1)
        {
            if (strcmp(name, d.name) == 0)
                found = 1;
            else
                fprintf(tmp, "%s %d %s\n", d.name, d.id, d.dept);
        }
        else if (name == NULL)
        {
            if (id == d.id)
                found = 1;
            else
                fprintf(tmp, "%s %d %s\n", d.name, d.id, d.dept);
        }
    }
    fclose(fp);
    fclose(tmp);
    if (found == 1)
    {
        remove("doctor.txt");
        rename("tmp_doctor.txt", "doctor.txt");
        printf("成功移除\n");
    }
    else
    {
        remove("tmp_dpctpr.txt");
        printf("未找到此医生\n");
        clear();
    }
    sleep(1);
}
struct doctor *load_doctor(int *count)
{

    *count = 0;
    FILE *fp = fopen("doctor.txt", "r");
    int size = 64;
    struct doctor *doctor = (struct doctor *)malloc(sizeof(struct doctor) * 64);
    struct doctor tmp;
    while (fscanf(fp, "%63s %d %63s\n", tmp.name, &tmp.id, tmp.dept) == 3)
    {
        // printf("%s %d %s\n", tmp.name, tmp.id, tmp.dept);
        if (*count > size)
        {
            size *= 2;
            struct doctor *new = realloc(doctor, size * sizeof(struct doctor));

            doctor = new;
        }
        strcpy(doctor[*count].name, tmp.name);
        strcpy(doctor[*count].dept, tmp.dept);
        doctor[*count].id = tmp.id;
        (*count)++;
        // printf("%s %d %s\n", doctor[*count - 1].name, doctor[*count - 1].id, doctor[*count - 1].dept);
    }
    /*for (int i = 0; i < *count; i++)
    {
        printf("%s %d %s\n", doctor[i].name, doctor[i].id, doctor[i].dept);
    }*/
    return doctor;
}

int compare_id_doctor(const void *a, const void *b)
{
    struct doctor *A = (struct doctor *)a;
    struct doctor *B = (struct doctor *)b;

    if (A->id < B->id)
        return -1;
    if (A->id > B->id)
        return 1;
    return 0;
}
int compare_name_doctor(const void *a, const void *b)
{
    struct doctor *A = (struct doctor *)a;
    struct doctor *B = (struct doctor *)b;
    return strcmp(A->name, B->name);
}

int compare_dept_doctor(const void *a, const void *b)
{
    struct doctor *A = (struct doctor *)a;
    struct doctor *B = (struct doctor *)b;
    return strcmp(A->dept, B->dept);
}

void sort_doctor(char ch)
{

    int count = 0;
    struct doctor *d = load_doctor(&count);
    switch (ch)
    {
    case '1':
        qsort(d, count, sizeof(struct doctor), compare_id_doctor);
        break;
    case '2':
        qsort(d, count, sizeof(struct doctor), compare_name_doctor);
        break;
    case '3':
        qsort(d, count, sizeof(struct doctor), compare_dept_doctor);
        break;
    }

    FILE *tmp = fopen("tmp.txt", "w");
    for (int i = 0; i < count; i++)

        fprintf(tmp, "%s %d %s\n", d[i].name, d[i].id, d[i].dept);

    remove("doctor.txt");
    rename("tmp.txt", "doctor.txt");

    printf("排序成功\n");

    sleep(1);
    free(d);

    fclose(tmp);
}
