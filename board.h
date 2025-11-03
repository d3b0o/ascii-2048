#ifndef BOARD_H
#define BOARD_H

#define ROWS 4
#define COLUMNS 4
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

typedef struct {
    int x;
    int y;
    int value;
} Cell;

typedef struct {
    Cell cells[ROWS][COLUMNS];
    int score;
    int lastScoreUpdate;
    int win;
    int lose;
} Board;

typedef struct {
    int row;
    int col;
} Point;

void initBoard(Board *b);
void printBoard(Board *b);

void addNumber(Board *b, int x, int y, int value);
void updateScore(Board *b, int n);

void spawnNumber(Board *b);
void moveLeft(Board *b);
void invertHorizontal(Board *b);
void transposition(Board *b);
void handleInput(Board *b, char ui);

#endif

