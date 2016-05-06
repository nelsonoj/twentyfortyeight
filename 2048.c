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
#include <math.h>
#include <time.h>
#include "2048.h"
#include "colors.h"

#define SIZE 4
#define EMPTY 0
#define PLAIN_BOARD '*'

#define INIT_TILES 2
#define WIN 2048

#define FILE_NAME "save"
#define TIME_SIZE 19
#define FILE_SIZE 39
#define EMPTY_TILE 'e'

struct _twenty{
    int board[SIZE][SIZE];
    int gameOver;
    int won;
};

typedef unsigned char bits8;

void swap (int *first, int *second);
int power (int x, unsigned int exponent);

Twenty makeNewGame (void) {
    Twenty newGame = malloc(sizeof(struct _twenty));
    assert(newGame != NULL);

    int y = 0;
    while (y < SIZE) {
        int x = 0;
        while (x < SIZE) {
            newGame->board[x][y] = EMPTY;
            x++;
        }
        y++;
    }
    newGame->gameOver = FALSE;
    newGame->won = FALSE;

    y = 0;
    while (y < INIT_TILES) {
        newTile(newGame);
        y++;
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
                printf(colorString(game->board[x][y]), game->board[x][y]);
            }
            x++;
        }
        printf("\n");
        printf("\n");
        y++;
    }
    printf("\n");
}

char *colorString (int tile) {

    char *colors[NUM_COLORS] = {
        FG_YELLOW, FG_BLUE, FG_MAGENTA,
        FG_CYAN,   FG_RED,  FG_GREEN,
        BG_YELLOW, BG_BLUE, BG_MAGENTA,
        BG_CYAN,   BG_RED,  BG_GREEN
    };

    return colors[((int)log2(tile) - 1) % (NUM_COLORS-1)];
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
    int y = 0;
    while (y < SIZE && !isWin) {
        int x = 0;
        while (x < SIZE && !isWin) {
            isWin = (game->board[x][y] == WIN);
            game->won = isWin;
            x++;
        }
        y++;
    }
    return isWin;
}

int stalemateDetect (Twenty game) {
    assert(game != NULL);
    int isStale = TRUE;
    int y = 0;
    // if the board isn't full then it can't be over
    while (y < SIZE && isStale) {
        int x = 0;
        while (x < SIZE && isStale) {
            if (game->board[x][y] == EMPTY) {
                isStale = FALSE;
            }
            x++;
        }
        y++;
    }
    // if the board is full and nothing is adjacent to
    // a tile of the same value, it is over
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
    } else if (type == END_QUIT) {
        printf("Saving game...\n");
    }
    printf("Goodbye!\n");
}

void saveGame (Twenty game) {
    time_t rawtime;
    struct tm *timeinfo;
    char timeString[TIME_SIZE+1];
    
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (timeString, TIME_SIZE, "%F %R:%S", timeinfo);
    
    FILE *savefile;
    savefile = fopen(FILE_NAME, "wb");
    assert ((savefile!=NULL) && "Cannot open file");
    
    char header[sizeof(int)+1];
    sprintf(header, "%d", WIN);
    fwrite (header, strlen(header), 1, savefile);
    fwrite (timeString, strlen(timeString), 1, savefile);
    int y = 0;
    while (y < SIZE) {
        int x = 0;
        while (x < SIZE) {
            bits8 boardSquare;
            if (game->board[x][y] == EMPTY) {
                boardSquare = EMPTY_TILE;
            } else {
                boardSquare = (bits8)log2(game->board[x][y]);
            }
            fwrite (&boardSquare, sizeof boardSquare, 1, savefile);
            x++;
        }
        y++;
    }
    bits8 won = (bits8)game->won;
    fwrite (&won, sizeof won, 1, savefile);

    fclose(savefile);
}

void loadGame (Twenty game) {
    FILE *savefile;
    savefile = fopen(FILE_NAME, "rb");
    assert ((savefile!=NULL) && "Cannot open file");
    
    char filebuffer[FILE_SIZE];
    fread(filebuffer, FILE_SIZE, 1, savefile);
    fclose(savefile);
    
    //if the first four arent 2048 crash
    
    int index = sizeof(int);
    char timeString[TIME_SIZE + 1];
    strncpy(timeString, filebuffer+index, TIME_SIZE);
    printf("Loading game from %s...\n", timeString);
    printf("\n");
    index += TIME_SIZE;
    
    int y = 0;
    while (y < SIZE) {
        int x = 0;
        while (x < SIZE) {
            if (filebuffer[index] == EMPTY_TILE) {
                game->board[x][y] = EMPTY;
            } else {
                game->board[x][y] = power(2, filebuffer[index]);
            }
            index++;
            x++;
        }
        y++;
    }
    game->gameOver = FALSE;
    index++;
    game->won = filebuffer[index];
}

int power (int x, unsigned int exponent) {
    int i = 0;
    int answer = 1;
    if (exponent > 0) {
        while (i < exponent) {
            answer *= x;
            i++;
        }
    }
    return answer;
}
