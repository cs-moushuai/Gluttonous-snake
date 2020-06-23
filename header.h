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

void Map();
void Gotoxy(int x, int y);
void Init();