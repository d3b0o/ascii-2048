#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void initBoard(Board *b)
{
    int x, y;

    printf("INFO Initializing board...\n");
    
    for (x=0; x<ROWS; x++)
    {
        for (y=0; y<COLUMNS; y++)
        {
            b -> cells[x][y].x = x;
            b -> cells[x][y].y = y;
            b -> cells[x][y].value = 0;
        }
    }

    b -> win = 0;
    b -> lose = 0;
    b -> score = 0;
    b -> lastScoreUpdate = 0;
}

void printBoard(Board *b)
{
    
    int x, y, value;
    
    system("clear");
    printf("Score: %i", b -> score);
    
    if (b -> lastScoreUpdate != 0)
    {
        printf(" (+%d)", b->lastScoreUpdate);
        b -> lastScoreUpdate = 0;
    }
    
    printf("\n");



    for (x=0; x<ROWS; x++)
    {
        printf("+--------+--------+--------+--------+\n");
        printf("|");
        for (y=0; y<COLUMNS; y++)
        {
            value = b->cells[x][y].value;
            if (value)
            {
                printf("  %4.d  |", value);
            } else 
            {
                printf("        |");
            }
        }
        printf("\n");
    }
    printf("+--------+--------+--------+--------+\n");
}

void addNumber(Board *b, int x, int y, int value)
{
    b -> cells[x][y].value = value;
}

void updateScore(Board *b, int n)
{
    b -> score += n;
    b -> lastScoreUpdate += n; 
};
    
void spawnNumber(Board *b)
{
    Point possibleCells[ROWS * COLUMNS];
    int x, y, count;
    count = 0;
    for (x=0; x<ROWS; x++)
    {
        for (y=0; y<COLUMNS; y++)
        {
            if (!b -> cells[x][y].value)
            {
                possibleCells[count].col = y;
                possibleCells[count].row = x;
                count++;
            }
        }
    }

    int chosen = rand() % count;

    addNumber(b, possibleCells[chosen].row, possibleCells[chosen].col, 2);
}

void moveLeft(Board *b)
{
    int x, y;
    for (x=0; x<ROWS; x++)
    {
        Cell *row = b -> cells[x];
        for (y=0; y<COLUMNS; y++) 
        {
            if (row[y].value != 0)
            {
                int count = 1;
                while (y-count != -1 && row[y-count].value == 0)
                {
                    row[y-count].value = row[y-count+1].value;
                    row[y-count+1].value = 0;
                    count++;
                }
            }
        }

        for(y=0; y<COLUMNS; y++)
        {
            if (row[y].value == row[y-1].value)
            {
                updateScore(b, row[y].value);
                row[y-1].value *= 2;
                row[y].value = 0;
            }
        }

        for (y=0; y<COLUMNS; y++) 
        {
            if (row[y].value != 0)
            {
                int count = 1;
                while (y-count != -1 && row[y-count].value == 0)
                {
                    row[y-count].value = row[y-count+1].value;
                    row[y-count+1].value = 0;
                    count++;
                }
            }
        }
    }
}

void invertHorizontal(Board *b)
{
    int x, y;
    int n = COLUMNS / 2;
    int t = COLUMNS - 1;

    for (x=0; x<ROWS; x++)
    {
        for (y=0; y<n; y++)
        {
            int *j = &b->cells[x][y].value;
            int *i = &b->cells[x][t-y].value;

            *j ^= *i;
            *i ^= *j;
            *j ^= *i;
        }
    }
}

void transposition(Board *b)
{
    int x, y, temp;
    Board tb;
    initBoard(&tb);
    for (x=0; x<ROWS; x++)
    {
        for (y=0; y<COLUMNS; y++)
        {
            tb.cells[y][x].value = b -> cells[x][y].value;
        }
    }
    for (x=0; x<ROWS; x++)
    {
        for (y=0; y<COLUMNS; y++)
        {
            b -> cells[x][y].value = tb.cells[x][y].value; 
        }
    }
}

    

void handleInput(Board *b, char ui)
{
    int x, y;
    switch (ui)
    {
        case 'a':
            moveLeft(b);
            break;

        case 'd':
            invertHorizontal(b);
            moveLeft(b);
            invertHorizontal(b);
            break;

        case 'w':
            transposition(b);
            moveLeft(b);
            transposition(b);
            break;

        case 's':
            transposition(b);
            invertHorizontal(b);
            moveLeft(b);
            invertHorizontal(b);
            transposition(b);
            break;
    }
}
