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

#define MAX_BUFFER 9

#define NUM_ACTIONS 6
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
#define UP 'w'
#define HELP 'h'
#define QUIT 'q'

void greet (void);
void showHelp (void);
void winGame (void);

int main (int argc, char *argv[]) {
    
    srand(time(NULL));
    Twenty game = makeNewGame();
    greet();
    printBoard(game);
    
    char actions[NUM_ACTIONS] = { LEFT, DOWN, RIGHT, UP,
        HELP, QUIT };
    
    char input[MAX_BUFFER];
    
    while (getStatus(game) != TRUE) {
        scanf("%s", input);
        if (input[0] == QUIT) {
            endGame(game, END_QUIT);
        } else if (input[0] == HELP) {
            showHelp();
        } else if (input[0] == LEFT) {
            moveLeft(game);
            newTile(game);
            printBoard(game);
        } else {
            int i = 1;
            while (i < NUM_ACTIONS) {
                if (input[0] == actions[i]) {
                    int j = 0;
                    while (j < i) {
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
    printf("Controls: %c %c %c %c to move, %c to exit, and %c to show this help.\n",
           UP, LEFT, DOWN, RIGHT, QUIT, HELP);
    printf("\n");
}

void showHelp (void) {
    printf("Terminal 2048 created on 1/5/16 by Nelson O-J\n");
    printf("Controls: %c %c %c %c to move, %c to exit, and %c to show this help.\n",
           UP, LEFT, DOWN, RIGHT, QUIT, HELP);
    printf("\n");
}

void winGame (void) {
    printf("Congratulations! You won!\n");
    printf("Feel free to keep playing, or enter %c to quit.\n", QUIT);
    printf("\n");
}
