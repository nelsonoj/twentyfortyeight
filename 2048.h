//
//  2048.h
//
//  Nelson Odins-Jones, z5122504, nelsonoj
//  01/05/2016
//  Function prototypes and typedef for abstract game type
//

typedef struct _twenty *Twenty;

#define TRUE 1
#define FALSE 0

#define END_LOSE 0
#define END_QUIT 1

Twenty makeNewGame (void);
void newTile (Twenty game);

void moveLeft (Twenty game);
void collapseRow (Twenty game, int y);
void collideRow (Twenty game, int y);
void rotateClockwise (Twenty game);

void printBoard (Twenty game);
char *colorString (int tile);

int winDetect (Twenty game);
int stalemateDetect (Twenty game);
int getWon (Twenty game);
int getStatus (Twenty game);
void endGame (Twenty game, int type);

void saveGame (Twenty game);
void loadGame (Twenty game);