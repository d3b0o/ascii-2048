#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

int main() {
    Board b;
    char ui;
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

