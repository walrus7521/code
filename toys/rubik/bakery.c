// k-nearest neighbor bakery regression

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int index;
    int weather;
    int weekday;
    int game;
    float value;
    float dx;
} profile_t;

#define N_PROFILES (6)
profile_t profiles[N_PROFILES] = 
{
    {.index=0, .weather=5, .weekday=1, .game=0, .value=300, .dx=0},
    {.index=1, .weather=3, .weekday=1, .game=1, .value=225, .dx=0},
    {.index=2, .weather=1, .weekday=1, .game=0, .value=75,  .dx=0},
    {.index=3, .weather=4, .weekday=0, .game=1, .value=200, .dx=0},
    {.index=4, .weather=4, .weekday=0, .game=0, .value=150, .dx=0},
    {.index=5, .weather=2, .weekday=0, .game=0, .value=50,  .dx=0},
};

float calc_dx(int i, profile_t *p)
{
    float sum = 0 ;
    float dx = 0.0f;
    sum += pow(profiles[i].weather - p->weather, 2.0f);
    sum += pow(profiles[i].weekday - p->weekday, 2.0f);
    sum += pow(profiles[i].game - p->game, 2.0f);
    //dx = sqrt(sum);
    return sum;
}

float calc_soft_cosine_similarity(int i, profile_t *p)
{
    // all features are similar to eachother
    float sum_ab = 0 ;
    float sum_aa = 0 ;
    float sum_bb = 0 ;
    sum_ab += profiles[i].weather * p->weather;
    sum_ab += profiles[i].weekday * p->weekday;
    sum_ab += profiles[i].game    * p->game;
    
    sum_aa += profiles[i].weather * profiles[i].weather;
    sum_aa += profiles[i].weekday * profiles[i].weekday;
    sum_aa += profiles[i].game    * profiles[i].game;
    sum_aa = sqrt(sum_aa);
    
    sum_bb += p->weather * p->weather;;
    sum_bb += p->weekday * p->weekday;
    sum_bb += p->game    * p->game;
    sum_bb = sqrt(sum_bb);

    float dx = sum_ab / (sum_aa * sum_bb);
    return dx;
}

int cmp(const void *a, const void *b)
{
    profile_t *a1 = (profile_t *)a;
    profile_t *a2 = (profile_t *)b;
    if ((*a1).dx > (*a2).dx)
        return 1;
    else if ((*a1).dx < (*a2).dx)
        return -1;
    else
        return 0;
}

int main()
{
    int K = 4; // nearest neighbors
    profile_t dxes[N_PROFILES];
    profile_t p = {.index=0, .weather=4, .weekday=1, .game=0, .value=0, .dx=0};
    for (int i = 0; i < N_PROFILES; i++) {
        profiles[i].dx = calc_soft_cosine_similarity(i, &p); // calc_dx(i, &p);
        printf("dx[%d] = %f\n", i, profiles[i].dx);
    }
    qsort(profiles, N_PROFILES, sizeof(profile_t), cmp);
    float avg = 0.0f;
    for (int i = 0; i < K; i++) {
        avg += profiles[i].value;
    }
    avg /= K;
    printf("avg num loaves: %f\n", avg);
}

