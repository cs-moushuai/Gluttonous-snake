#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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
    bool flag = false;

    srand((unsigned)time(NULL));
    food.x = rand() % 18 + 1;
    food.y = rand() % 18 + 1;
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COL; j++)
        {
            //snake 
            for ( Snake *p = snake_head; p != NULL; p=p->next)
            {
                if (i == p->y && j == p->x)
                {
                    printf("¤");
                    flag = true;

                }
                

                p=p->next;
            }
            

            if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1)
            {
                //SetConsoleTextAttribute(handle, 1);
                printf("■");
            }
            else if (j == food.x && i == food.y)
            {
                printf("◎");
            }

            else if(flag == false)
            {
                //SetConsoleTextAttribute(handle, 7);
                printf("□");
            }
            flag = false;
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
    SetConsoleTitle("Gluttonous Snake");

    snake_head = (Snake *)malloc(sizeof(Snake));
    snake_end = (Snake *)malloc(sizeof(Snake));
    snake_head->x=10;
    snake_head->y=10;
    snake_end->x = 16;
    snake_end->y = 10;

    snake_head->next = snake_end;

    snake_end->next=(Snake *)malloc(sizeof(Snake));
    snake_end=snake_end->next;
    snake_end->x = 12;
    snake_end->y = 10;

    snake_end->next=(Snake *)malloc(sizeof(Snake));
    snake_end=snake_end->next;
    snake_end->x = 14;
    snake_end->y = 10;

    snake_end->next = NULL;
}