#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include <signal.h>

void printHeader()
{
    printf("Welcome to the 2048 game! (CLI version)\n");
}

char userMove()
{
    char ui;
    ui = getchar();
    while (ui != 'w' && ui != 'a' && ui != 's' && ui != 'd')
    {
        ui = getchar();
    }
    return ui;
}

