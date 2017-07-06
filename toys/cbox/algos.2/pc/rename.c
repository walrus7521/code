#include <stdio.h>
#include <string.h>

#define MAXLEN      1001
#define MAXCHANGES   101

typedef char string[MAXLEN];

string mergers[MAXCHANGES][2];  /* store before/after corporate names */
int nmergers;                   /* number of different name changes */

void read_quoted_string(char *s)
{
    int i = 0;
    char c;

    while ((c = getchar()) != '\"') ;
    while ((c = getchar()) != '\"') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
}

void read_changes()
{
    int i;
    scanf("%d\n", &nmergers);
    for (i = 0; i < nmergers; i++) {
        read_quoted_string((mergers[i][0]));
        read_quoted_string((mergers[i][1]));
    }
}

int findmatch(char *p, char *t)
{
    int i, j;
    int plen, tlen;

    plen = strlen(p);
    tlen = strlen(t);

    for (i = 0; i <= (tlen-plen); i++) {
        j = 0;
        while ((j < plen) && (t[i+j] == p[j]))
            j++;
        if (j == plen) return (i);
    }
    return (-1);
}

void replace_x_with_y(char *s, int pos, int xlen, char *y)
{
    int i;
    int slen, ylen;

    slen = strlen(s);
    ylen = strlen(y);

    if (xlen >= ylen)
        for (i = (pos+xlen); i <= slen; i++)
            s[i+(ylen-xlen)] = s[i];
    else
        for (i = slen; i>= (pos+xlen); i--)
            s[i+(ylen-xlen)] = s[i];

    for (i = 0; i < ylen; i++)
        s[pos+i] = y[i];
}

int main()
{
    string s;
    char c;
    int nlines;
    int i, j;
    int pos;

    read_changes();
    scanf("%d\n", &nlines);
    for (i = 1; i <= nlines; i++) {
        j = 0;
        while ((c = getchar()) != '\n') {
            s[j] = c;
            j++;
        }
        s[j] = '\0';

        for (j = 0; j < nmergers; j++)
            while ((pos = findmatch(mergers[j][0], s)) != -1) {
                replace_x_with_y(s, pos,
                        strlen(mergers[j][0]), mergers[j][1]);
            }
        printf("%s\n", s);
    }

    return 0;
}
