#pragma once

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
void Goto(int x, int y);