#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

const int INF = 100000;

int COIN_VALUE[] = {0, 1, 3, 4, 5};
const int NUM_DENOM = 4; // number of denominations
const int MAKE = 7; // make change for MAKE
int NUM_COINS[MAKE+1]; // arrays are one-based
 
void show()
{
    int denom, value;
    printf("COIN_VALUE { ");
    for (denom = 1; denom <= NUM_DENOM; denom++) {
        printf("%d ", COIN_VALUE[denom]);
    }
    printf("}\n");
    for (value = 1; value <= MAKE; value++) {
        printf("NUM_COINS[ value=%d ] => %d coin(s)\n", value, NUM_COINS[value]);
    }
    printf("\n");
    printf("num coins for making value %d is %d\n", MAKE, NUM_COINS[MAKE]);
}


void coins()
{
    int denom, value;
    NUM_COINS[0] = 0;

    for(value = 1; value <= MAKE; value++) {

        int minimum = INF;

        // find the minimum for this amount and for all the denominations
        for(denom = 1; denom <= NUM_DENOM; denom++) {

            if(value >= COIN_VALUE[denom]) { // ensures >0 indices

                printf("N(value: %d, den: %d): %d\n", value, denom, NUM_COINS[value-COIN_VALUE[denom]]);

                minimum = MIN(minimum, 1 + NUM_COINS[value-COIN_VALUE[denom]]);
                
            }
        }
        NUM_COINS[value] = minimum;
    }

}

int main()
{
    coins();
    show();
}

