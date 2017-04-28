#ifndef _LIFE_H_
#define _LIFE_H_

#define MAXROW      20
#define MAXCOL      60

typedef enum boolean { TRUE, FALSE } Boolean;
typedef enum state { DEAD, ALIVE } State;

typedef State Grid[MAXROW+2][MAXCOL+2];

void CopyMap(Grid map, Grid newmap);
Boolean UserSaysYes(void);
void Initialize(Grid map, FILE *in);
int NeighborCount(Grid map, int row, int col);
void WriteMap(Grid map);

#endif
