#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) printf("ungetch: too many characters\n");
    else buf[bufp++] = c;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;
    while (isspace(c = getch())) ;
    if (c != EOF) *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d, %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL) {
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w); p->count = 1; p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) p->count++;
    else if (cond < 0) p->left = addtree(p->left, w);
    else p->right = addtree(p->right, w);
    return p;
}

int main()
{
    struct tnode *root = NULL;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0])) root = addtree(root, word);
    treeprint(root);
}
