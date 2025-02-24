#include "patient.h"
void add_patient(FILE *fp, char *name, int id)
{
    int result = fprintf(fp, "%s  %d  \n", name, id);
    if (result < 0)
        printf("写入失败\n");
}
void del_patient()
{
    while (1)
    {
        printf("\n1.通过姓名移除患者\n2.通过ID移除患者\n0.返回上级");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':

            break;

        case '2':
            break;

        case '0':
            return;
        default:
            printf("数字无效，请重新输入");
            continue;
        }
    }
}
void print_patient();
void pos_patient_byid(int patient_id);
void pos_patient_byname(char patient_name);
void del_patient_byid(FILE *fp, int id)
{
}
void del_patient_byname(FILE *fp, char *name);