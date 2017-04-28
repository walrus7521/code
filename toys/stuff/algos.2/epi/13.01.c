#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Anagrams:
 *  1. read lines and split into words
 *  2. append lines to dictionary
 *  3. itrerate over dictionary, and sort characters in each word
 *  4. create hash(string = sorted word, list of strings = list of words);
 *  4. store sorted word and the word in a hash
 *
 * test with /usr/share/dict/words
 *
 */
typedef struct _list {
    struct _list *next;
    char value[256];
} list;

int charcomp(const void *x, const void *y) {
    return *((char *) x) - *((char *) y); 
}

#define WORDMAX 100
void sign()
{
    char word[WORDMAX], sig[WORDMAX];
    while (scanf("%s", word) != EOF) {
        strcpy(sig, word);
        qsort(sig, strlen(sig), sizeof(char), charcomp);
        printf("%s %s\n", sig, word);
    }
}

void squash()
{
    char word[WORDMAX], sig[WORDMAX], oldsig[WORDMAX];
    int linenum = 0;
    strcpy(oldsig, "");
    while (scanf("%s %s", sig, word) != EOF) {
        if (strcmp(oldsig, sig) != 0 && linenum > 0)
            printf("\n");
        strcpy(oldsig, sig);
        linenum++;
        printf("%s ", word);
    }
    printf("\n");
}

void show(list *head)
{
    list *p = head;
    if (!head) return;
    p = head->next;
    while (p) {
        printf("-> %s\n", p->value);
        p = p->next;
    }
}

void insert(list *head, char *value, int len)
{
    list *entry = malloc(sizeof(list));
    memset(entry, sizeof(entry), 0);
    memset(entry->value, 256, '\0');
    strncpy(entry->value, value, len);
    entry->next = head->next;
    head->next = entry;
}

list *split(char *line)
{
    list *words = (list *) malloc(sizeof(list));
    size_t i = 0, len, j;
    char word[256];
    len = strlen(line);
    words->next = NULL;
    //printf("split: enter %s, len %zd\n", line, len);
    while (i != len) {
        while (i != len && isspace(line[i]))
            ++i;
        j = i;
        while (j != len && !isspace(line[j]))
            ++j;
        //printf("split i %zd, j %zd\n", i, j);
        if (i != j) {
            memset(word, 256, '\0');
            strncpy(word, &line[i], j-i);
            word[j-i] = '\0';
            //printf("split: pushing %s\n", word);
            insert(words, word, j-i+1);
            i = j;
        }
    }
    return words;
}

void append(list *master, list *slave)
{
    list *prev, *curr;
    if (master == NULL || slave == NULL) {
        return;
    }
    curr = master->next;
    prev = master;
    while (curr) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = slave->next;
    return;
}

int mygetline(char *line)
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        *line++ = c;
    }
    return c;
}

int main(void)
{
    char line[256];
    char *pline = line;
    size_t len = 256;
    list *words, *dictionary;

    dictionary = (list *) malloc(sizeof(list));
    dictionary->next = NULL;
    //while (getline(&pline, &len, stdin)) {
    memset(line, 256, '\0');
    while (mygetline(line) != EOF) {
        words = split(line);
        append(dictionary, words);
        memset(line, 256, '\0');
    }
    show(dictionary);

    //sign();
    //squash();
}
