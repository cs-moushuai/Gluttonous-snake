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

void Help();
void InitMap();
void DrawSnake();
void DrawFood();
void DrawSpeed();
void GotoXy(int x, int y);
void InitData();
void Welcome();
void DrawWelcome();
void RunGame();
void NormalGame();
void HidenCursor();
void GiveXySnake(Snake *a, Snake *b);
bool JudgeEatFood();
void JudgeDeath();
void GameOver();
void NewFood();
void DrawScore();
void NewNode();
void PrintGrade();
void SwapInt(int *a,int *b);
// void PlayMusic();



#define DEBUG