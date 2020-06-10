#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


int M = 20;
const int C = 3;
int price[C][4] = {
    {6,  4, 8, 0},
    {5, 10, 0, 0},
    {1,  5, 3, 5}
};
int model[3] = {0,0,0};

int garment_id = 0;
int max_so_far = 0;

int shop(int money, int g)
{
    //printf("shop m: %d, g: %d\n", money, g);
    if (money < 0) return -999;
    if (g == C) return M - money;
    int max = 0, cur_max = 0;
    for (int i = 0; i <= C; i++) {
        max = MAX(shop(money-price[g][i], g+1), price[g][i]);
        if (max > cur_max) cur_max = max;
    }
    return cur_max;
}

int main()
{
    int money_left = M;
    int garments_bought = 0;
    while (1) {
        if (garment_id >= C) garment_id = 0;
        money_left = shop(money_left, garment_id);
        printf("money left: %d\n", money_left);
        garment_id++;
        if (money_left < 0) break;
    }
}

