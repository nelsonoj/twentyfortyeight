//
//  playGame.c
//
//  Nelson Odins-Jones, z5122504, nelsonoj
//  01/05/2016
//  Get user input and run the game of 2048 accordingly
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "2048.h"

#define SQUARE_SIDES 4

#define NUM_ACTIONS 7
#define HELP 'h'
#define QUIT 'q'
#define LOAD 'l'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
#define UP 'w'


void greet (void);
void showHelp (void);
void winGame (void);

int main (int argc, char *argv[]) {

    srand(time(NULL));
    Twenty game = makeNewGame();
    greet();
    printBoard(game);

    char actions[NUM_ACTIONS] = { HELP, QUIT, LOAD,
                                  LEFT, DOWN, RIGHT, UP };

    char input;

    while (getStatus(game) != TRUE) {
        input = getchar();
        if (input == QUIT) {
            saveGame(game);
            endGame(game, END_QUIT);
        } else if (input == HELP) {
            showHelp();
        } else if (input == LOAD) {
            loadGame(game);
            printBoard(game);
        }
        else if (input == LEFT) {
            moveLeft(game);
            newTile(game);
            printBoard(game);
        } else {
            int i = 4;
            while (i < NUM_ACTIONS) {
                if (input == actions[i]) {
                    int j = 0;
                    while (j < i-3) {
                        rotateClockwise(game);
                        j++;
                    }
                    moveLeft(game);
                    while (j < SQUARE_SIDES) {
                        rotateClockwise(game);
                        j++;
                    }
                    newTile(game);
                    printBoard(game);
                }
                i++;
            }
        }
        if (getWon(game) == FALSE && winDetect(game)) {
            winGame();
        }
        if (stalemateDetect(game)) {
            endGame(game, END_LOSE);
        }
    }
    return EXIT_SUCCESS;
}

void greet (void) {
    printf("Welcome to Terminal 2048!\n");
    printf("Controls: %c %c %c %c to move, %c to save and exit,\n",
           UP, LEFT, DOWN, RIGHT, QUIT);
    printf("          %c to load a save, and %c to show this help.\n",
           LOAD, HELP);
    printf("\n");
}

void showHelp (void) {
    printf("Terminal 2048 created on 1/5/16 by Nelson O-J\n");
    printf("Controls: %c %c %c %c to move, %c to save and exit,\n",
           UP, LEFT, DOWN, RIGHT, QUIT);
    printf("          %c to load a save, and %c to show this help.\n",
           LOAD, HELP);
    printf("\n");
}

void winGame (void) {
    printf("Congratulations! You won!\n");
    printf("Feel free to keep playing, or enter %c to quit.\n", QUIT);
    printf("\n");
}
