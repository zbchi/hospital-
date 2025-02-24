#include "doctor.h"
void add_doctor(FILE *fp, char *name, int id, char *dept)
{
    int result = fprintf(fp, "%s  %d  %s \n", name, id, dept);
    if (result < 0)
        printf("写入失败\n");
}
void del_doctor()
{
    while (1)
    {
        printf("\n1.通过姓名移除医生\n2.通过ID移除医生\n0.返回上级");
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
void print_doctor(struct doctor *doctor);
void doctor_patients(int doctor_id);
void pos_doctor_byid(int doctor_id);
void pos_doctor_byname(char doctor_name);
