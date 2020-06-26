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

void Help()
{
    system("cls");

    GotoXy(16, 5);
    printf("***************************************************************************************");
    GotoXy(16, 6);
    printf("*                                                                                     *");
    GotoXy(16, 7);
    printf("*                                Gluttonous Snake                                     *");
    GotoXy(16, 8);
    printf("*                                                                                     *");
    GotoXy(16, 9);
    printf("*              in this game, you can use ↑ → ← ↓ to control your snake                *");
    GotoXy(16, 10);
    printf("*                                                                                     *");
    GotoXy(16, 11);
    printf("*   when your snake get a food, it will lengthen a block and you will get 20 scores   *");
    GotoXy(16, 12);
    printf("*                                                                                     *");
    GotoXy(16, 13);
    printf("*             when your snake eat itself or crash wall, game will be over!            *");
    GotoXy(16, 14);
    printf("*                                                                                     *");
    GotoXy(16, 15);
    printf("*                       then you can choose y/n to new a game                         *");
    GotoXy(16, 16);
    printf("*                                                                                     *");
    GotoXy(16, 17);
    printf("*                                  Good lucky!                                        *");
    GotoXy(16, 18);
    printf("*                                                                                     *");
    GotoXy(16, 19);
    printf("***************************************************************************************");

    Sleep(9000);

    system("cls");
    DrawWelcome();
}

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

void NewNode(int x, int y)
{
    snake_end->next = (Snake *)malloc(sizeof(Snake));
    snake_end = snake_end->next;
    snake_end->x = x;
    snake_end->y = y;

    snake_end->next = NULL;
}

void InitData()
{
    SetConsoleTitle("Gluttonous Snake");

    score = 0;

    snake_head = (Snake *)malloc(sizeof(Snake));
    snake_end = (Snake *)malloc(sizeof(Snake));
    snake_head->x = 13;
    snake_head->y = 10;
    snake_end->x = 12;
    snake_end->y = 10;

    snake_head->next = snake_end;

    NewNode(11, 10);

    NewNode(10, 10);

    NewFood();

    HidenCursor();
}

void Welcome()
{
    DrawWelcome();
    InitData();
}

void DrawWelcome()
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
        Sleep(500);
        DrawScore();

        //ch = getch();
        // system("cls");
        /* switch (ch)
        {
        case 72: //上
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
        } */

        if (GetAsyncKeyState(VK_UP) && d_flag != 's')
        { //判断键盘输入的如果是↑键，且蛇的方向没有向下，那就进入循环，把蛇的方向的状态改成向上
            d_flag = 'w';
        }
        if (GetAsyncKeyState(VK_DOWN) && d_flag != 'w')
        { //判断键盘输入的如果是↓键，且蛇的方向没有向上，那就进入循环，把蛇的方向的状态改成向下

            d_flag = 's';
        }
        if (GetAsyncKeyState(VK_LEFT) && d_flag != 'd')
        { //判断键盘输入的如果是左键，且蛇的方向没有向右，那就进入循环，把蛇的方向的状态改成向左

            d_flag = 'a';
        }
        if (GetAsyncKeyState(VK_RIGHT) && d_flag != 'a')
        { //判断键盘输入的如果是右键，且蛇的方向没有向左，那就进入循环，把蛇的方向的状态改成向右

            d_flag = 'd';
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        { //如果键盘输入ESC键，那就状态改成退出
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

void PrintGrade()
{
    FILE *fp;
    if (!(fp = fopen("Grade.txt", "a+")))
    {
        printf("Failure!\n");
        exit(EXIT_FAILURE);
    }

    int history_grade[50] = {0};
    int max = 0;
    size_t i = 0;

    while (fscanf(fp, "%d", &history_grade[i]) && !feof(fp))
    {
        ++i;
    }

    for (i = 0; i < 50 - 1; i++)
    {
        max = i;
        for (size_t j = i + 1; j < 50; j++)
        {
            if (history_grade[j] > history_grade[max])
            {
                max = j;
            }
        }
        SwapInt(&history_grade[i], &history_grade[max]);
    }

    fprintf(fp, "%d\n", score);

    system("cls");
    GotoXy(16, 5);
    printf("***************************************************************************************");
    GotoXy(16, 6);
    printf("*                                                                                     *");
    GotoXy(16, 7);
    printf("*                                Gluttonous Snake                                     *");
    GotoXy(16, 8);
    printf("*                                                                                     *");
    GotoXy(16, 9);
    printf("*                                History   Grades                                     *");
    GotoXy(16, 10);
    printf("*                                                                                     *");
    GotoXy(16, 11);
    printf("*                                      1.%d                                           *", history_grade[0]);
    GotoXy(16, 12);
    printf("*                                                                                     *");
    GotoXy(16, 13);
    printf("*                                      2.%d                                           *", history_grade[1]);
    GotoXy(16, 14);
    printf("*                                                                                     *");
    GotoXy(16, 15);
    printf("*                                      3.%d                                           *", history_grade[2]);
    GotoXy(16, 16);
    printf("*                                                                                     *");
    GotoXy(16, 17);
    printf("*                             your score this game: %d                                *", score);
    GotoXy(16, 18);
    printf("*                                                                                     *");
    GotoXy(16, 19);
    printf("***************************************************************************************");

    fclose(fp);
}

void SwapInt(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
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

    GotoXy(15, 10);
    printf("***********************************");
    GotoXy(15, 11);
    printf("*           Game is over!         *");
    GotoXy(15, 12);
    printf("* press y/n to try again or exit! *");
    GotoXy(15, 13);
    printf("***********************************");

    char ch;

    while (1)
    {
        ch = getch();

        if (ch == 'y' || ch == 'Y')
        {
            InitData();
            RunGame();
        }
        else if (ch == 'n' || ch == 'N')
        {
            PrintGrade();
            system("pause");
            exit(EXIT_SUCCESS);
        }
    }
}