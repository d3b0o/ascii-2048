#include <stdio.h>
#include "game.h"

void printHeader()
{
    printf("Welcome to the 2048 game! (CLI version)\n");
}

char userMove()
{
    char ui;
    ui = getchar();

    while (ui != 'w' && ui != 'a' && ui != 's' && ui != 'd' && ui != 'h')
    {
        printf("Invalid\n");
        ui = getchar();
    }

    return ui;
}

