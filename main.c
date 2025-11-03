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
    printf("\e[?25h");
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
    addNumber(&b, 3, 2, 1024);
    addNumber(&b, 3, 1, 1024);

    while (!b.win && !b.lose) {
        printBoard(&b);
        ui = userMove();
        handleInput(&b, ui);
        spawnNumber(&b);
    }
    
    printBoard(&b);

    if (b.win)
    {
        printf("\nYou win!\n");
    }
    else
    {
        printf("\nYou lose!\n");
    }

    printf("========\n");
    printf("[+] Score: %d\n", b.score);
    printf("[+] Moves: %d\n", b.moves);

    return 0;
}

