#include <stdio.h>
#include "function.h"
#define MAX_ATTEMPTS 3
int main()
{

    char correctUsername[] = "admin";
    char correctPassword[] = "123";

    char username[20];
    char password[20];

    int attempts = 0;
    int loggedIn = 0;

    printf("欢迎登录系统\n");

    while (attempts < MAX_ATTEMPTS)
    {
        printf("\n请输入用户名: ");
        scanf("%19s", username);

        printf("请输入密码: ");
        scanf("%19s", password);

        if (strcmp(username, correctUsername) == 0 &&
            strcmp(password, correctPassword) == 0)
        {
            loggedIn = 1;
            break;
        }
        else
        {
            attempts++;
            printf("登录失败，剩余尝试次数: %d\n", MAX_ATTEMPTS - attempts);
        }
    }

    if (loggedIn)
    {
        printf("\n登录成功！欢迎 %s\n", username);
    }
    else
    {
        printf("\n超过最大尝试次数，登录失败！\n");
        return 0;
    }

    while (1)
    {
        printf("\n请输入相应的数字：\n1.挂号\n2.退号\n3.打印\n4.添加删除\n5.查询挂号记录\n6.排序\n7.查询统计\n0.退出\n");
        int ch;
        if ((scanf(" %d", &ch)) != 1)
        {
            clear();
            printf("\n数字无效，请重新输入\n");
            continue;
        }
        switch (ch)
        {
        case 1:
            clear();
            Register();
            break;

        case 2:
            clear();
            unregister();
            break;
        case 3:
            clear();
            print();
            break;
        case 4:
            clear();
            adddel();
            break;
        case 5:
            clear();
            patient_search();
            break;
        case 6:
            clear();
            sort();
            break;
        case 7:
            clear();
            doctor_search();
            break;
        case 0:
            clear();
            return 0;

        default:
            clear();
            printf("\n数字无效，请重新输入\n");
            break;
        }
    }
    return 0;
}