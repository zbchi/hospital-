#include "function.h"
void add()
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

        case '4':
            del_patient();

        case '0':
            return;
        default:
            printf("数字无效，请重新输入\n");
            continue;
        }
    }
}

void print()
{
    while (1)
    {
        printf("\n1.打印全体医生信息\n2.打印全体患者信息");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':

            break;

        default:
            break;
        }
    }
}