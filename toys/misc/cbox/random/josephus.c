#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *next;
};

int main()
{
    int i, N, M;
    struct node *t, *x;
    scanf("%d %d", &M, &N);
    printf("there are %d people, and %d rounds per selection\n", N, M);
    t = (struct node *) malloc(sizeof(struct node));
    t->key = 1;
    x = t;
    for (i = 2; i <= N; i++) {
        t->next = (struct node *) malloc(sizeof(struct node));
        t = t->next;
        t->key = i;
    }
    t->next = x; // completes the circular list
    while (t != t->next) {
        for (i = 1; i < M; i++) t = t->next;
        printf("kill: %d\n", t->next->key);
        x = t->next;
        t->next = t->next->next;
        free(x);
    }
    printf("%d\n", t->key);
    return 0;
}
