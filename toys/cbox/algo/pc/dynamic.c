#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATCH   0
#define INSERT  1
#define DELETE  2

#define MAXLEN  255

typedef struct {
    int cost;
    int parent;
} cell;

cell m[MAXLEN+1][MAXLEN+1];

void row_init(int i)
{
    m[0][i].cost = i;
    if (i > 0)
        m[0][i].parent = INSERT;
    else
        m[0][i].parent = -1;
}

void column_init(int i)
{
    m[i][0].cost = i;
    if (i > 0)
        m[i][0].parent = DELETE;
    else 
        m[0][i].parent = -1;
}

int match(char c, char d)
{
    if (c == d) return (0);
    else return (1);
}

int indel(int i)
{
    return (1);
}

void goal_cell(char *s, char *t, int *i, int *j)
{
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}

void insert_out(char *t, int j)
{
    printf("I");
}

void delete_out(char *s, int i)
{
    printf("D");
}

void match_out(char *s, char *t, int i, int j)
{
    if (s[i] == t[j]) printf("M");
    else printf("S");
}

void reconstruct_path(char *s, char *t, int i, int j)
{
    if (m[i][j].parent == -1) return;

    if (m[i][j].parent == MATCH) {
        reconstruct_path(s, t, i-1, j-1);
        match_out(s, t, i, j);
        return;
    }
    if (m[i][j].parent == INSERT) {
        reconstruct_path(s, t, i, j-1);
        insert_out(t, j);
        return;
    }
    if (m[i][j].parent == DELETE) {
        reconstruct_path(s, t, i-1, j);
        delete_out(s, i);
        return;
    }
}

int string_compare(char *s, char *t, int i, int j)
{
    int k;
    int opt[3];
    int lowest_cost;

    if (i == 0) return (j * indel(' '));
    if (j == 0) return (i * indel(' '));

    opt[MATCH]  = string_compare(s,t,i-1,j-1) + match(s[i],t[j]);
    opt[INSERT] = string_compare(s,t,i,j-1) + indel(t[j]);
    opt[DELETE] = string_compare(s,t,i-1,j) + indel(s[i]);

    lowest_cost = opt[MATCH];
    for (k = INSERT; k <= DELETE; k++) {
        if (opt[k] < lowest_cost) lowest_cost = opt[k];
    }

    return lowest_cost;
}

int string_compare2(char *s, char *t)
{
    int i, j, k;
    int opt[3];

    for (i = 0; i < MAXLEN; i++) {
        row_init(i);
        column_init(i);
    }

    for (i = 1; i < strlen(s); i++) {
        for (j = 1; j < strlen(t); j++) {
            opt[MATCH]  = m[i-1][j-1].cost + match(s[i], t[j]);
            opt[INSERT] = m[i][j-1].cost + indel(t[j]);
            opt[DELETE] = m[i-1][j].cost + indel(s[i]);

            m[i][j].cost = opt[MATCH];
            m[i][j].parent = MATCH;
            for (k = INSERT; k <= DELETE; k++) {
                if (opt[k] < m[i][j].cost) {
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                }
            }
        }
    }

    goal_cell(s, t, &i, &j);
    return (m[i][j].cost);
}



int main()
{
    int i=1, j=1;
    char str1[] = " thou-shalt-not"; // pre-pad w/' '
    char str2[] = " you-should-not";
    i = j = 11; // larger than 11 takes too long
    //int m = string_compare(str1, str2, i, j);
    int m = string_compare2(str1, str2);
    printf("cost = %d\n", m);
    i = j = 14;
    reconstruct_path(str1, str2, i, j);
    printf("\n");
    return 0;
}
