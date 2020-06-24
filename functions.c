#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#include "header.h"

Snake *snake_head, *snake_end;
Node food;
HANDLE handle;
int score = 0;

char d_flag = 'd';

void GotoXy(int x, int y)
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void InitMap()
{
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    bool flag = false;

    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COL; j++)
        {
            //snake
            for (Snake *p = snake_head; p != NULL; p = p->next)
            {
                if (i == p->y && j == p->x)
                {
                    if (p == snake_head)
                    {
                        printf("※");
                    }
                    /*  else if (p == snake_end)
                    {
                        printf("※");
                    } */
                    else
                    {
                        printf("¤");
                    }

                    flag = true;
                    break;
                }
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

            else if (flag == false)
            {
                //SetConsoleTextAttribute(handle, 7);
                printf("□");
            }
            flag = false;
        }

        printf("\n");
    }
}

void DrawScore()
{
    GotoXy(0, 20);
    printf("************************************score:%d************************************", score);
}

void DrawSnake()
{
    for (Snake *p = snake_head; p != NULL; p = p->next)
    {

        GotoXy(p->x, p->y);
        if (p == snake_head)
        {
            printf("※");
        }
        else
        {
            printf("¤");
        }
    }
}

void DrawFood()
{
    GotoXy(food.x, food.y);
    printf("◎");
}

void Init()
{
    GotoXy(20, 5);
    printf("*****************************************************");
    GotoXy(20, 6);
    printf("*            welcome to Gluttonous Snake!           *");
    GotoXy(20, 7);
    printf("*         press 1 to start or press 2 to exit       *");
    GotoXy(20, 8);
    printf("*              Tip:press 0 to get help              *");
    GotoXy(20, 9);
    printf("*****************************************************");
    SetConsoleTitle("Gluttonous Snake");

    snake_head = (Snake *)malloc(sizeof(Snake));
    snake_end = (Snake *)malloc(sizeof(Snake));
    snake_head->x = 13;
    snake_head->y = 10;
    snake_end->x = 12;
    snake_end->y = 10;

    snake_head->next = snake_end;

    snake_end->next = (Snake *)malloc(sizeof(Snake));
    snake_end = snake_end->next;
    snake_end->x = 11;
    snake_end->y = 10;

    snake_end->next = (Snake *)malloc(sizeof(Snake));
    snake_end = snake_end->next;
    snake_end->x = 10;
    snake_end->y = 10;

    snake_end->next = NULL;

    NewFood();

    HidenCursor();
}

void HidenCursor()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;

    info.bVisible = true;

    SetConsoleCursorInfo(handle, &info);
}

void RunGame()
{
    char ch;
    system("cls");
    InitMap();
    while (1)
    {
        DrawScore();
        ch = getch();
        // system("cls");
        switch (ch)
        {
        case 72: //上*/
            if (d_flag != 's')
            {
                d_flag = 'w';
            }
            break;
        case 80: //下
            if (d_flag != 'w')
            {
                d_flag = 's';
            }
            break;
        case 77: //右
            if (d_flag != 'a')
            {
                d_flag = 'd';
            }
            break;
        case 75: //左
            if (d_flag != 'd')
            {
                d_flag = 'a';
            }
            break;
        case 27: //ESC
            GameOver();
        }


        NormalGame();


        JudgeDeath();

        DrawSnake();
        DrawFood();
    }
}

void NormalGame()
{
    Snake *p = snake_head;
    Snake temp;
    Snake p_prior = *p;
    switch (d_flag)
    {
    case 'w': //上*/
        snake_head->y--;
        break;
    case 's': //下
        snake_head->y++;
        break;
    case 'a': //左
        snake_head->x--;
        break;
    case 'd': //右
        snake_head->x++;
        break;
    }

    for (Snake *p = snake_head->next; p != NULL; p = p->next)
    {
        temp = *p;
        GiveXySnake(p, &p_prior);
        p_prior = temp;
    }
    GotoXy(p_prior.x, p_prior.y);
    printf("□");

    if (JudgeEatFood() == true)
    {
        snake_end->next = (Snake *)malloc(sizeof(Snake));
        snake_end = snake_end->next;
        GiveXySnake(snake_end, &p_prior);
        snake_end->next = NULL;
    }
}

bool JudgeEatFood()
{
    if (snake_head->x == food.x && snake_head->y == food.y)
    {
        score += 20;

        NewFood();

        return true;
    }
    return false;
}

void JudgeDeath()
{
    if (snake_head->x == 0 || snake_head->x == COL - 1 || snake_head->y == 0 || snake_head->y == ROW - 1)
    {
        GameOver();
    }

    for (Snake *p = snake_head->next; p != NULL; p = p->next)
    {
        if (p->x == snake_head->x && p->y == snake_head->y)
        {
            GameOver();
        }
    }
}

void NewFood()
{

    srand((unsigned)time(NULL));
    food.x = rand() % 18 + 1;
    food.y = rand() % 18 + 1;

    for (Snake *p = snake_head; p != NULL; p = p->next)
    {
        JudgeEatFood();
    }
}

void GiveXySnake(Snake *a, Snake *b)
{
    a->x = b->x;
    a->y = b->y;
}

void GameOver()
{
    system("cls");
    Snake *p = snake_head;
    Snake *temp = NULL;
    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p = temp;
    }
    system("pause");
    exit(EXIT_SUCCESS);
}