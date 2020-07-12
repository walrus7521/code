#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int costs[21][21];
int reachable[21][201];
int N,M,C;

void show_reachable()
{
    printf("\n      ");
    for (int m = 0; m <= M; m++) printf("%02d ", m);
    printf("\n      ");
    for (int m = 0; m <= M; m++) printf("===");
    printf("\n");
    for (int g = 0; g < C; g++) {
        printf("g %02d: ", g);
        for (int k = 0; k <= M; k++) printf("%02d ", reachable[g][k]);
        printf("\n");
    }
}

int wedding3()
{
    int g, money, k, retval = -1;
    // first row - loop over choices in garment 0
    for (g = 1; g <= costs[0][0]; g++) {
        if (M - costs[0][g] >= 0) {
            reachable[0][M-costs[0][g]] = true;
        }
    }
    show_reachable();
    for (g = 1; g < C; g++) {
        printf("g: %d\n", g);
        for (money = 0; money < M; money++) {
            if (reachable[g-1][money]) {
                printf("reachable[%d][%d]\n", g-1, money);
                for (k = 1; k <= costs[g][0]; k++) {
                    if (money - costs[g][k] >= 0) {
                        printf("setting: [%d][%d]\n", g, money-costs[g][k]);
                        reachable[g][money-costs[g][k]] = true;
                    }
                }
            }
        }
        show_reachable();
    }
    for (money = 0; money <= M && !reachable[C-1][money]; money++) ;
    if (money == M+1) printf("no solution\n");
    else retval = M - money;
    return retval;
}

int main()
{
    M = 20; C = 3;
    costs[0][0] = 3;   costs[1][0] =  2;  costs[2][0] = 4; 
    costs[0][1] = 6;   costs[1][1] =  5;  costs[2][1] = 1; 
    costs[0][2] = 4;   costs[1][2] = 10;  costs[2][2] = 5; 
    costs[0][3] = 8;                      costs[2][3] = 3; 
                                          costs[2][3] = 5;  
    memset(reachable, false, sizeof(reachable));
    printf("wedding3: %d\n", wedding3());
    return 0;
}

