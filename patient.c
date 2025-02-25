#include "patient.h"

void clear1()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void add_patient(FILE *fp, char *name, int id)
{
    int result = fprintf(fp, "%s  %d  \n", name, id);
    if (result < 0)
        printf("添加失败\n");
    else
        printf("添加成功\n");
    sleep(1);
}
void del_patient()
{
    while (1)
    {
        printf("\n1.通过姓名移除患者\n2.通过ID移除患者\n0.返回上级\n");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':
            printf("请输入患者姓名：");
            char name[64];
            scanf("%s", name);
            del_patient_bynameid(name, 0);
            break;

        case '2':
            printf("请输入患者ID：");
            int id;
            scanf(" %d", &id);
            del_patient_bynameid(NULL, id);
            break;

        case '0':
            return;
        default:
            printf("数字无效，请重新输入");
            clear1();
            continue;
        }
    }
}
void print_patient();
void del_patient_bynameid(char *name, int id)
{
    FILE *fp = fopen("patient.txt", "r");
    FILE *tmp = fopen("tmp_patient.txt", "w");
    struct patient p;
    int found = 0;
    while (fscanf(fp, "%63s %d", p.name, &p.id) == 2)
    {
        if (id == 0)
        {
            if (strcmp(name, p.name) == 0)
                found = 1;
            else
                fprintf(tmp, "%s %d\n", p.name, p.id);
        }
        else if (name == NULL)
        {
            if (id == p.id)
                found = 1;
            else
                fprintf(tmp, "%s %d\n", p.name, p.id);
        }
    }
    fclose(fp);
    fclose(tmp);
    if (found == 1)
    {
        remove("patient.txt");
        rename("tmp_patient.txt", "patient.txt");
        printf("成功移除\n");
    }
    else
    {
        remove("tmp_patient.txt");
        printf("未找到此患者\n");
        clear1();
    }
    sleep(1);
}

struct patient *load_patient(int *count)
{
    *count = 0;
    FILE *fp = fopen("patient.txt", "r");
    int size = 64;
    struct patient *patient = (struct patient *)malloc(sizeof(struct patient) * 64);
    struct patient tmp;
    while (fscanf(fp, "%63s %d", tmp.name, &tmp.id) == 2)
    {
        // printf("%s %d %s\n", tmp.name, tmp.id, tmp.dept);
        if (*count > size)
        {
            size *= 2;
            struct patient *new = realloc(patient, size * sizeof(struct patient));

            patient = new;
        }
        strcpy(patient[*count].name, tmp.name);
        patient[*count].id = tmp.id;
        (*count)++;
        // printf("%s %d %s\n", doctor[*count - 1].name, doctor[*count - 1].id, doctor[*count - 1].dept);
    }
    /*for (int i = 0; i < *count; i++)
    {
        printf("%s %d %s\n", doctor[i].name, doctor[i].id, doctor[i].dept);
    }*/
    return patient;
}
