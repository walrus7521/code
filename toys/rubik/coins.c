#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

const int INF = 100000;

int COIN_VALUE[] = {0, 3, 4, 5}; //1, 3, 4, 5};
const int NUM_DENOM = sizeof(COIN_VALUE) / sizeof(COIN_VALUE[0]) - 1; //4; // number of denominations
const int MAKE = 7; // make change for MAKE
int NUM_COINS[MAKE+1]; // arrays are one-based
int table[NUM_DENOM+1][MAKE+1];
 
void show()
{
    int denom, value;
    printf("COIN_VALUE { ");
    for (denom = 1; denom <= NUM_DENOM; denom++) {
        printf("%d ", COIN_VALUE[denom]);
    }
    printf("}\n\n");
    for (value = 1; value <= MAKE; value++) {
        (NUM_COINS[value] < INF) ? 
        printf("NUM_COINS[ value=%d ] => %d coin(s)\n", value, NUM_COINS[value]) :
        printf("NUM_COINS[ value=%d ] => no solution\n", value);

    }
    printf("\n");
    printf("num coins for making value %d is ", MAKE);
    (NUM_COINS[MAKE] <= MAKE) ? 
        printf("%d\n", NUM_COINS[MAKE]) : printf("no solution\n");

    printf("\nAMT    ");
    for (int m = 1; m <= MAKE; m++) printf("%d ", m);
    printf("\n");
    printf("       ");
    for (int m = 1; m <= MAKE; m++) printf("==");
    printf("\n");
    for (int d = 1; d <= NUM_DENOM; d++) {
        printf("DEN(%d) ", COIN_VALUE[d]);
        for (int m = 1; m <= MAKE; m++) {
            (table[d][m] <= NUM_DENOM) ? 
                printf("%d ", table[d][m]) : printf("%c ", 'x');
        }
        printf("\n");
    }
}


void coins()
{
    int denom, amt;
    NUM_COINS[0] = 0;

    for(amt = 1; amt <= MAKE; amt++) {

        int minimum = INF;

        // find the minimum for this amount and for all the denominations
        for(denom = 1; denom <= NUM_DENOM; denom++) {

            if(amt >= COIN_VALUE[denom]) { // ensures >0 indices

                //printf("N(value: %d, den: %d): %d\n", amt, denom, NUM_COINS[amt-COIN_VALUE[denom]]);

                minimum = MIN(minimum, 1 + NUM_COINS[amt-COIN_VALUE[denom]]);
                
            }
            table[denom][amt] = minimum;
        }

        NUM_COINS[amt] = minimum;
    }

}

int main()
{
    printf("NUM_DENOM: %d\n", NUM_DENOM);
    coins();
    show();
}

