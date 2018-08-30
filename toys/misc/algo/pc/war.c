
#include "queue.h"

#define MAXSTEPS 1000000
#define NCARDS 52
#define NSUITS 4

char values[] = "23456789TJQKA";
char suits[]  = "cdhs";

int rank_card(char value, char suit)
{
    int i, j;
    for (i = 0; i < (NCARDS/NSUITS); i++)
        if (values[i] == value)
            for (j = 0; j < NSUITS; j++)
                if (suits[j] == suit)
                    return (i*NSUITS + j);
}

char suit(int card)
{
    return (suits[card % NSUITS]);
}

char value(int card)
{
    return (values[card/NSUITS]);
}

void clear_queue(queue *a, queue *b)
{
    while (!queue_empty(a)) enqueue(b, dequeue(a));
}

int war(queue *a, queue *b)
{
    int steps = 0;
    int x, y;
    queue c;
    int inwar;

    inwar = 0;
    queue_init(&c);

    while ((!queue_empty(a)) && (!queue_empty(b) && (steps < MAXSTEPS))) {
        steps++;
        x = dequeue(a);
        y = dequeue(b);
        enqueue(&c, x);
        enqueue(&c, y);
        if (inwar)
            inwar = 0;
        else {
            if (value(x) > value(y))
                clear_queue(&c, a); 
            else if (value(x) < value(y))
                clear_queue(&c, b);
            else if (value(y) == value(x))
                inwar = 1;
        }
    }

    if (!queue_empty(a) && queue_empty(b))
        printf("a wins in %d steps\n", steps);
    else if (queue_empty(a) && !queue_empty(b))
        printf("b wins in %d steps\n", steps);
    else if (!queue_empty(a) && !queue_empty(b))
        printf("game tied after %d steps, |a|=%d |b|=%d\n",
                steps, a->count, b->count);
    else
        printf("a and b tie in %d steps\n", steps);


    return 0;
}

int main()
{
    queue decks[2];
    char value, suit, c;
    int i;

    while (1) {
        for (i = 0; i <= 1; i++) {
            queue_init(&decks[i]);

            while ((c = getchar()) != '\n') {
                if (c == EOF) return 0;
                if (c != ' ') {
                    value = c;
                    suit = getchar();
                    enqueue(&decks[i], rank_card(value, suit));
                }
            }
        }
        war(&decks[0], &decks[1]);
    }

    return 0;
}
