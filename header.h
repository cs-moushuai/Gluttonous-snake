#pragma once

//gcc main.c functions.c -o main.exe

typedef struct NODE
{
    int x, y;
} NODE;

typedef struct SNAKE
{
    int length;
    NODE *nodes;

} SNAKE;



void Map();
void Gotoxy(int x, int y);
void Init();