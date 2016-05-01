//
//  2048.c
//
//  Nelson Odins-Jones, z5122504, nelsonoj
//  01/05/2016
//  Implementation of struct and game functions
//  Detection of stalled game added as of 1700
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "2048.h"

#define SIZE 4
#define EMPTY 0
#define PLAIN_BOARD '*'

#define INIT_TILES 2
#define WIN 2048

struct _twenty{
    int board[SIZE][SIZE];
    int orientation;
    int gameOver;
    int won;
};

Twenty makeNewGame (void) {
    Twenty newGame = malloc(sizeof(struct _twenty));
    assert(newGame != NULL);
    
    int i = 0;
    while (i < SIZE * SIZE) {
        newGame->board[0][i] = EMPTY;
        i++;
    }
    newGame->orientation = 0;
    newGame->gameOver = FALSE;
    
    i = 0;
    while (i < INIT_TILES) {
        newTile(newGame);
        i++;
    }

    return newGame;
}

void printBoard (Twenty game) {
    assert(game != NULL);
    int y = 0;
    while (y < SIZE) {
        int x = 0;
        while (x < SIZE) {
            if (game->board[x][y] == EMPTY) {
                printf("%c\t", PLAIN_BOARD);
            } else {
                printf("%d\t", game->board[x][y]);
            }
            x++;
        }
        printf("\n");
        printf("\n");
        y++;
    }
    printf("\n");
}

void newTile (Twenty game) {
    assert(game != NULL);
    int added = 0;
    int startTiles[2] = { 2, 4 };
    int i = SIZE * SIZE;
    while (!added && i > 0) {
        int randX = rand() % SIZE;
        int randY = rand() % SIZE;
        if (game->board[randX][randY] == EMPTY) { 
            // 10% chance of new tile being a four
            game->board[randX][randY] = startTiles[(rand() % 10 == 9)];
            added = TRUE;
        }
        i--;
    }
}

void moveLeft (Twenty game) {
    assert(game != NULL);
    int y = 0;
    while (y < SIZE) {
        collapseRow(game, y);
        collideRow(game, y);
        collapseRow(game, y);
        y++;
    }
}

void collapseRow (Twenty game, int y) {
    assert(game != NULL);
    int x = 0;
    while (x < SIZE) {
        if (game->board[x][y] != EMPTY) {
            int scan = 0;
            while (scan < x) {
                if (game->board[scan][y] == EMPTY) {
                    game->board[scan][y] = game->board[x][y];
                    game->board[x][y] = EMPTY;
                }
                scan++;
            }
            
        }
        x++;
    }
}

void collideRow (Twenty game, int y) {
    assert(game != NULL);
    int x = 0;
    while (x < SIZE) {
        if (game->board[x][y] == game->board[x+1][y]) {
            game->board[x][y] *= 2;
            game->board[x+1][y] = EMPTY;
        }
        x++;
    }
}

void rotateClockwise (Twenty game) {
    assert(game != NULL);
    int temp[SIZE][SIZE] = { { 0 } };
    int y = 0;
    // transpose array then reverse it
    while (y < SIZE) {
        int x = 0;
        while (x < SIZE) {
            temp[x][y] = game->board[y][x];
            x++;
        }
        y++;
    }
    y = 0;
    while (y < SIZE) {
        swap(&temp[0][y], &temp[SIZE-1][y]);
        swap(&temp[1][y], &temp[SIZE-2][y]);
        int x = 0;
        while (x < SIZE) {
            game->board[x][y] = temp[x][y];
            x++;
        }
        y++;
    }
}

void swap (int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

int winDetect (Twenty game) {
    assert(game != NULL);
    int isWin = 0;
    int i = 0;
    while (i < SIZE * SIZE && !isWin) {
        isWin = (game->board[0][i] == WIN);
        game->won = isWin;
        i++;
    }
    return isWin;
}

int stalemateDetect (Twenty game) {
    assert(game != NULL);
    int isStale = TRUE;
    int i = 0;
    // if the board isn't full then it can't be over
    while (i < SIZE * SIZE && isStale) {
        if (game->board[0][i] == EMPTY) {
            isStale = FALSE;
        }
        i++;
    }
    // if the board is full and nothing is adjacent to
    // a tile of the same value, it is over
    int y = 0;
    while (y < SIZE && isStale) {
        int x = 0;
        while (x < SIZE && isStale) {
            if (game->board[x][y] == game->board[x+1][y]) {
                isStale = FALSE;
            }
            x++;
        }
        y++;
    }
    rotateClockwise(game);
    y = 0;
    while (y < SIZE && isStale) {
        int x = 0;
        while (x < SIZE && isStale) {
            if (game->board[x][y] == game->board[x+1][y]) {
                isStale = FALSE;
            }
            x++;
        }
        y++;
    }
    rotateClockwise(game);
    rotateClockwise(game);
    rotateClockwise(game);
    return isStale;
}

int getWon (Twenty game) {
    assert(game != NULL);
    return game->won;
}

int getStatus (Twenty game) {
    assert(game != NULL);
    return game->gameOver;
}

void endGame (Twenty game, int type) {
    assert(game != NULL);
    assert(getStatus(game) == FALSE);
    game->gameOver = TRUE;
    free(game);
    game = NULL;
    if (type == END_LOSE) {
        printf("Game Over!\n");
    }
    printf("Goodbye!\n");

}
