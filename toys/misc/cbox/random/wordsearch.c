#include <stdio.h>
#include <string.h>

// 1. implement a word search
// 2. reverse dict strings

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

// create a dictionary
char dictionary[64][36];
int dict_index = 0;

char words[20][32] = {
    "AVENTIL",       "GREATHELM",
    "BALLISTICVEST", "GREAVE",
    "BASCINET",      "HAUBERK",
    "BURGONET",      "HELMET",
    "CLOSEHELM",     "KETTLEHAT",
    "CODPIECE",      "KEVLAR",
    "CUIRASS",       "SABATON",
    "FAULD",         "SPAULDER",
    "FLAKJACKET",    "VAMBRACE",
    "GAUNTLET",      "VISOR"
};

void clear_dict()
{
    int i;
    for (i = 0; i < 64; i++) {
        memset(dictionary[i], '\0', 36);
    }
}

void add(char *sym, int len)
{
    strncpy(dictionary[dict_index++], sym, len);
}

void dump()
{
    int i;
    for (i = 0; i < 64; i++) {
        printf("dict[%02d] : %s\n", i, dictionary[i]);
    }
    for (i = 0; i < 20; i++) {
        printf("words[%d] : %s\n", i, words[i]);
    }
}

char puzzle[15][15] = {
    {'G','T','E','N','O','G','R','U','B','F','P','J','Z','P','A'},
    {'Q','T','E','N','E','C','S','A','B','A','A','R','B','C','I'},
    {'R','R','C','L','I','O','R','K','R','E','B','U','A','H','Q'},
    {'V','O','A','K','T','C','L','O','S','E','H','E','L','M','Z'},
    {'U','T','R','F','M','N','G','U','P','R','C','C','L','D','P'},
    {'S','U','B','I','L','R','U','X','A','K','U','E','I','A','U'},
    {'I','S','M','N','E','A','S','A','E','S','I','I','S','J','C'},
    {'X','E','A','A','H','V','K','T','G','R','R','P','T','I','Y'},
    {'A','H','V','B','T','R','T','J','O','Y','A','D','I','U','R'},
    {'S','E','E','D','A','L','H','O','A','U','S','O','C','L','T'},
    {'N','L','N','Z','E','T','T','Z','L','C','S','C','V','P','R'},
    {'E','M','T','H','R','T','O','D','R','V','K','I','E','O','A'},
    {'O','E','A','G','G','C','E','N','W','B','S','E','S','R','X'},
    {'F','T','I','G','P','R','A','L','V','E','K','I','T','R','A'},
    {'G','E','L','P','K','A','T','F','W','U','V','E','N','E','E'},
};

void diagonal(int rows, int cols)
{
    int d, j, k;
    int hgt; // row of lowest point
    int pcnt; // points on diagonal
    int l1, l2; // final coordinates
    char diag[33];

    printf("diagonal order\n");
    for (d = 0; d < rows+cols; d++) {
        hgt = max(0,(d-cols));
        pcnt = 1 + min(d, (rows-hgt+1));
        memset(diag, '\0', 33);
        for (j = 0; j < pcnt; j++) {
            l1 = min(cols,d)-j;
            l2 = hgt+j;
            // range check
            if (   l1 >= 0 && l1 < rows
                && l2 >= 0 && l2 < cols) {
                //printf("[%2d][%2d]=(%02d) ", l1, l2, a[l1][l2]);
                //printf("(%c) ", puzzle[l1][l2]);
                if (l1 + l2 > 14) {
                    diag[j-1] = puzzle[l1][l2];
                } else {
                    diag[j] = puzzle[l1][l2];
                }
            }
        }
        add(diag, strlen(diag));
        //printf("\n");
    }
    printf("\n");
}

void traverse()
{
    char row[16];
    char col[16];
    char diag[33];

    int i, j;
    for (i = 0; i < 15; i++) {
        memset(row, '\0', 16);
        strncpy(row,puzzle[i],15);
        //printf("row[%02d] = %s\n", i, row);
        add(row, strlen(row));
    }
    for (i = 0; i < 15; i++) {
        memset(col, '\0', 16);
        for (j = 0; j < 15; j++) {
            col[j] = puzzle[j][i];
        }
        //printf("col[%02d] = %s\n", i, col);
        add(col, strlen(col));
    }

    diagonal(15,15);
}

void reverse(char *word, char *rev, int len)
{
    int i;
    for (i = len-1; i >= 0; --i) {
        *rev++ = word[i];
    }
}

int search(char *word)
{
    int i;
    printf("find: %s\n", word);
    for (i = 0; i < 64; i++) {
        char *dict = dictionary[i];
        char rev[36];
        memset(rev, '\0', 36);
        reverse(dict, rev, strlen(dict));
        //printf("check => %s, rev => %s\n", dict, rev);
        if (strstr(dict, word)) {
            printf("found one: %s => %s\n", word, dictionary[i]);
        }
    }
    return 0;
}

int main()
{
    int i;
    traverse();
    for (i = 0; i < 20; i++) {
        search(words[i]);
    }

}

