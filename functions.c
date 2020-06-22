#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"

const int ROW = 20, COL = 20;

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
    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COL; j++)
        {
            if (1)
            {
                printf("□");
            }
            else
            {
                printf("■");
            }
            
        }

        Gotoxy(i,0);
        
    }
    
}