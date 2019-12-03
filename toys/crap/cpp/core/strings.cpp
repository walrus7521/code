#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <limits.h>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

#define NHASH 29989
#define MULT  31
typedef struct node *nodeptr;
typedef struct node {
    char *word;
    int count;
    nodeptr next;
} node;
nodeptr bin[NHASH];

static unsigned int hasher(char *p)
{
    unsigned int h = 0;
    for ( ; *p; p++) h = MULT * h + *p;
    return h % NHASH;
}

void incword(char *s)
{
    int h = hasher(s);
    nodeptr p;
    for (p = bin[h]; p != NULL; p = p->next) {
        if (strcmp(s, p->word) == 0) {
            (p->count)++; return;
        }
    }
    p = (nodeptr) malloc(sizeof(struct node));
    p->count = 1;
    p->word = (char *) malloc(strlen(s)+1);
    strcpy(p->word, s);
    p->next = bin[h];
    bin[h] = p;
}

void strings_hash()
{
    int i;
    nodeptr p;
    char buf[256];
    for (i = 0; i < NHASH; i++) bin[i] = NULL;
    while (scanf("%s", buf) != EOF) incword(buf);
    for (i = 0; i < NHASH; i++) {
        for (p = bin[i]; p != NULL; p = p->next) {
            printf("rad: %s => %d\n", p->word, p->count);
        }
    }
}

void strings_set()
{
    set<string> S;
    set<string>::iterator j;
    string t;
    while (cin >> t) S.insert(t);
    for (j = S.begin(); j != S.end(); ++j) {
        cout << *j << endl;
    }
}

void strings_map()
{
    map<string, int> M;
    map<string, int>::iterator j;
    string t;
    while (cin >> t) M[t]++;
    for (j = M.begin(); j != M.end(); ++j) {
        cout << j->first << " " << j->second << endl;
    }
}

int main()
{
    //strings_set();
    //strings_map();
    strings_hash();
}

