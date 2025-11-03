#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include "board.h"
#include "game.h"

void sigintHandler(int sig_num) 
{ 
    signal(SIGINT, sigintHandler);
    printf("\n Goodbye! \n"); 
    system("stty icanon echo");
    exit(0);
    fflush(stdout); 
} 

int main() {
    Board b;
    char ui;
    signal(SIGINT, sigintHandler); 
    printf("\e[?25l");
    system("stty -icanon -echo");

    srand(time(NULL));

    printHeader();
    initBoard(&b);
    addNumber(&b, 3, 2, 4);

    while (!b.win && !b.lose) {
        printBoard(&b);
        ui = userMove();
        handleInput(&b, ui);
        spawnNumber(&b);
    }

    return 0;
}

