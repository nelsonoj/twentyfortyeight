//
//  2048.h
//
//  Nelson Odins-Jones, z5122504, nelsonoj
//  01/05/2016
//  Function prototypes and typedef for abstract game type
//

typedef struct _twenty *Twenty;

Twenty makeNewGame (void);
void newTile (Twenty game);

void moveLeft (Twenty game);
void collapseRow (Twenty game, int y);
void collideRow (Twenty game, int y);

void rotateClockwise (Twenty game);
void swap (int *first, int *second);

void printBoard (Twenty game);

int winDetect (Twenty game);
int getWon (Twenty game);
int getStatus (Twenty game);
void endGame (Twenty game);


