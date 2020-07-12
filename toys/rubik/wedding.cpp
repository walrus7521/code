#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;


int costs[21][21];
int memo[21][201];
int reachable[21][201];
int N,M,C;

int wedding1()
{
    int i, j, l;
    bool can_reach[210][25];
    int retval = -1;

    memset(can_reach, false, sizeof(can_reach));
    for (i = 1; i < costs[0][0]; i++) {
        can_reach[M - costs[0][i]][0] = true;
    }

    for (j = 1; j < C; j++) {
        for (i = 0; i < M; i++) {
            for (l = 1; l <= costs[j][0]; l++) {
                can_reach[i - costs[j][l]][j] = true;
            }
        }
    }

    for (i = 0; i <= M && !can_reach[i][C-1]; i++);

    if (i == M+1) 
        printf("no solution\n");
    else retval = M-1;
    return retval;

}


int shop(int money, int garment)
{
    int ans;
    
    if (money < 0) return -10000000;
    if (garment == C) return M - money;

    ans = -1;
    for (int model = 1; model <= costs[garment][0]; ++model) {
        ans = max(ans, shop(money-costs[garment][model], garment+1));
    }
    return ans;
}

int wedding2()
{
    return shop(M, 0);
}

void print_shop(int money, int g)
{
    if (money < 0 || g == C) return;
    for (int model = 1; model <= costs[g][0]; model++) {
        if (shop(money - costs[g][model], g+1) == memo[g][money]) {
            printf("%d%c", costs[g][model], g == C-1 ? '\n' : '-');
        }
        print_shop(money-costs[g][model], g+1);
        break;
    }
}

void show_reachable()
{
    printf("\n      ");
    for (int m = 0; m <= M; m++) {
        printf("%02d ", m);
    }
    printf("\n      ");
    for (int m = 0; m <= M; m++) {
        printf("===");
    }
    printf("\n");
    for (int g = 0; g < C; g++) {
        printf("g %02d: ", g);
        for (int k = 0; k <= M; k++) {
            printf("%02d ", reachable[g][k]);
        }
        printf("\n");
    }
}

// bottom up DP
int wedding3()
{
    int g, money, k, retval = -1;
    // first row
    for (g = 1; g <= costs[0][0]; g++) {
        if (M - costs[0][g] >= 0) {
            reachable[0][M-costs[0][g]] = true;
        }
    }
    show_reachable();
    for (g = 1; g < C; g++) {
        for (money = 0; money < M; money++) {
            if (reachable[g-1][money]) {
                for (k = 1; k <= costs[g][0]; k++) {
                    if (money - costs[g][k] >= 0) {
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

void init()
{
    M = 20;
    C = 3;

    costs[0][0] = 3;
    costs[0][1] = 6;
    costs[0][2] = 4;
    costs[0][3] = 8;

    costs[1][0] = 2;
    costs[1][1] = 5;
    costs[1][2] = 10;

    costs[2][0] = 4;
    costs[2][1] = 1;
    costs[2][2] = 5;
    costs[2][3] = 3;
    costs[2][4] = 5;
   
    memset(reachable, false, sizeof(reachable));
}

int main()
{
    init();
    //printf("wedding1: %d\n", wedding1());
    //printf("wedding2: %d\n", wedding2());
    printf("wedding3: %d\n", wedding3());
    return 0;
}

