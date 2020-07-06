#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum { COMEDY, ACTION, DRAMA, HORROR, ROMANCE, N_CATS } CATS;

typedef struct {
    char name[8];
    int categories[N_CATS];
} user_t;
#define N_USERS (3)
user_t users[] = 
{
    {.name = "Priyanka", .categories = {3, 4, 4, 1, 4}},
    {.name = "Justin",   .categories = {4, 3, 5, 1, 5}},
    {.name = "Morpheus", .categories = {2, 5, 1, 3, 1}},
};

float dxes[N_USERS+1];

float calc_dx(int i, int j)
{
    float dx = 0.0f;
    printf("%s -> %s\n", users[i].name, users[j].name);
    for (int n = 0; n < N_CATS; n++) {
        int diff = users[i].categories[n] - users[j].categories[n];
        float power = pow(diff, 2.0f);
        printf("[%d]: (%d - %d) = %d %f\n", n, users[i].categories[n], users[j].categories[n], diff, power);
        dx += power;
    }
    dx = sqrt(dx);
    printf("dx(%d,%d): %f\n", i, j, dx);
    return dx;
}

int main()
{
    memset(dxes, 0, sizeof(dxes));
    // permute users
    for (int i = 0; i < N_USERS; i++) {
        for (int j = i+1; j < N_USERS; j++) {
            dxes[i+j] = calc_dx(i, j);
        }
    }

    for (int i = 1; i < N_USERS+1; i++) {
        printf("dx[%d] = %f\n", i, dxes[i]);
    }
}

