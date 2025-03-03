#include <stdio.h>
#include "function.h"
int main()
{
    while (1)
    {
        printf("\n请输入相应的数字：\n1.挂号\n2.退号\n3.打印\n4.添加删除\n5.查询挂号记录\n6.排序\n7.查询统计\n0.退出\n");
        char ch;
        scanf(" %c", &ch);
        switch (ch)
        {
        case '1':
            clear();
            Register();
            break;

        case '2':
            clear();
            unregister();
            break;
        case '3':
            clear();
            print();
            break;
        case '4':
            clear();
            adddel();
            break;
        case '5':
            clear();
            patient_search();
            break;
        case '6':
            clear();
            sort();
            break;
        case '7':
            clear();
            doctor_search();
            break;
        case '0':
            clear();
            return 0;

        default:

            break;
        }
    }
    return 0;
}