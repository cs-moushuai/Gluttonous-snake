#pragma once

//gcc main.c functions.c -o main.exe

typedef struct Node
{
    int x, y;
} Node;

typedef struct Snake
{
    int x;
    int y;
    struct Snake *next;

} Snake;

#define ROW 20
#define COL 20*2

void InitMap();
void DrawSnake();
void DrawFood();
void GotoXy(int x, int y);
void InitData();
void Welcome();
void RunGame();
void NormalGame();
void HidenCursor();
void GiveXySnake(Snake *a, Snake *b);
bool JudgeEatFood();
void JudgeDeath();
void GameOver();
void NewFood();
void DrawScore();



#define DEBUG