#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

Snake *snake_head, *snake_end;
Node food;

void Gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void Map()
{
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    srand((unsigned)time(NULL));
    food.x = rand() % 18 + 1;
    food.y = rand() % 18 + 1;
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COL; j++)
        {
            if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1)
            {
                //SetConsoleTextAttribute(handle, 1);
                printf("■");
            }
            else if (j == food.x && i == food.y)
            {
                printf("◎");
            }

            else
            {
                //SetConsoleTextAttribute(handle, 7);
                printf("□");
            }
        }

        printf("\n");
    }
}

void Init()
{
    Gotoxy(20, 5);
    printf("*****************************************************");
    Gotoxy(20, 6);
    printf("*            welcome to Gluttonous Snake!           *");
    Gotoxy(20, 7);
    printf("*         press 1 to start or press 2 to exit       *");
    Gotoxy(20, 8);
    printf("*              Tip:press 0 to get help              *");
    Gotoxy(20, 9);
    printf("*****************************************************");

    snake_head = (Snake *)malloc(sizeof(Snake));
    snake_end = (Snake *)malloc(sizeof(Snake));
    snake_head->next = snake_end;
    snake_end->next = NULL;
}