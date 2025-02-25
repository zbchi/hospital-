#include <stdio.h>
#include "function.h"
int main()
{
    while (1)
    {
        printf("\n请输入相应的数字：\n1.挂号\n2.退号\n3.打印\n4.添加删除\n5.统计\n0.退出\n");
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
            int count = 0;
            load_doctor(&count);
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
            break;
        case '0':
            return 0;

        default:
            clear();
            break;
        }
    }
    return 0;
}