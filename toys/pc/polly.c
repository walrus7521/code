#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELENGTH      30
#define NSUITORS        100

#define BESTHEIGHT      180
#define BESTWEIGHT      75

typedef struct {
    char first[NAMELENGTH];
    char last[NAMELENGTH];
    int height;
    int weight;
} suitor;

suitor suitors[NSUITORS];
int nsuitors;

void read_suitors()
{
    char first[NAMELENGTH], last[NAMELENGTH];
    int height, weight;

    nsuitors = 0;

    while (scanf("%s %s %d %d\n", suitors[nsuitors].first,
                suitors[nsuitors].last, &height, &weight) != EOF) {
        suitors[nsuitors].height = abs(height - BESTHEIGHT);
        if (weight > BESTWEIGHT)
            suitors[nsuitors].weight = weight - BESTWEIGHT;
        else
            suitors[nsuitors].weight = -weight;
        nsuitors++;
    }
}

int __cdecl suitor_compare(const void *sa, const void *sb)
{
    suitor *a, *b;
    int result;

    a = sa;
    b = sb;

    if (a->height < b->height) return (-1);
    if (a->height > b->height) return (1);

    if (a->weight < b->weight) return (-1);
    if (a->weight > b->weight) return (1);

    if ((result = strcmp(a->last, b->last)) != 0) return result;

    return (strcmp(a->first, b->first));
}

int __cdecl main()
{
    int i;
    
    read_suitors();
    qsort((void *) suitors, (size_t) nsuitors, sizeof(suitor), suitor_compare);

    for (i = 0; i < nsuitors; i++) 
        printf("%s, %s\n", suitors[i].last, suitors[i].first);

    return 0;
}
