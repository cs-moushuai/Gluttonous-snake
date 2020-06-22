#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

#include "header.h"




int main(void)
{
    char ch;

    system("cls");
    system("color a");
    Init();

    bool flag = false;

    while (flag != true)
    {
        ch = getch();

        switch (ch)
        {
        case '1':
            flag = true; //1
            break;

        case '2':
            exit(EXIT_SUCCESS); //2
            break;

        case '0': //0
            break;

        default:
            break;
        }
    }

    system("cls");
    Map();
    system("pause");

    return 0;
}