#include <stdio.h>
#include <string.h>

#define NUM_WORDS (20)
#define MAX_STR_LEN (36)
char words[NUM_WORDS][MAX_STR_LEN] = {
    "AVENTAIL",      "GREATHELM",
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

#define DIM (15)
char puzzle[DIM][DIM] = {
    {'G','T','E','N','O','G','R','U','B','F','P','J','Z','P','A'},
    {'Q','T','E','N','I','C','S','A','B','A','A','R','B','C','I'},
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
char rotation[DIM][DIM];


#define MAX_ENTRIES (128)
// create a dictionary
char dictionary[MAX_ENTRIES][MAX_STR_LEN];
int dict_index = 0;

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

void clear_dict()
{
    int i;
    for (i = 0; i < MAX_ENTRIES; i++) {
        memset(dictionary[i], '\0', MAX_STR_LEN);
    }
}

void add(char *sym, int len)
{
    strncpy(dictionary[dict_index++], sym, len);
}

void dump()
{
    int i;
    for (i = 0; i < MAX_ENTRIES; i++) {
        printf("dict[%02d] : %s\n", i, dictionary[i]);
    }
    for (i = 0; i < NUM_WORDS; i++) {
        printf("words[%d] : %s\n", i, words[i]);
    }
}

void show(char pz[DIM][DIM], int wid)
{
    int i, j;
    for (i = 0; i < wid; i++) {
        for (j = 0; j < wid; j++) {
            printf("%c ", pz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void show_words()
{
    int i;
    for (i = 0; i < NUM_WORDS/2; i++) {
        printf("%14s\t%14s\n", words[i], words[i+i]);
    }
}

void diagonal(int rows, int cols, char pz[DIM][DIM])
{
    int d, j, k;
    int hgt; // row of lowest point
    int pcnt; // points on diagonal
    int l1, l2; // final coordinates
    char diag[33];

    //printf("diagonal order\n");
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
                //printf("(%c) ", pz[l1][l2]);
                if (l1 + l2 > 14) {
                    diag[j-1] = pz[l1][l2];
                } else {
                    diag[j] = pz[l1][l2];
                }
            }
        }
        add(diag, strlen(diag));
        //printf("\n");
    }
    printf("\n");
}

// 90 deg clockwise
void rotate(char input[DIM][DIM], char output[DIM][DIM])
{
    int n =DIM; //input.length();
    int m = DIM; //input[0].length();
    //int [][] output = new int [m][n];

    int i, j;
    for (i=0; i<n; i++) {
	    for (j=0;j<m; j++) {
		    output [j][n-1-i] = input[i][j];
        }
    }
}

void traverse()
{
    char row[16];
    char col[16];
    char diag[33];

    int i, j;
    for (i = 0; i < DIM; i++) {
        memset(row, '\0', 16);
        strncpy(row,puzzle[i],DIM);
        //printf("row[%02d] = %s\n", i, row);
        add(row, strlen(row));
    }
    for (i = 0; i < DIM; i++) {
        memset(col, '\0', 16);
        for (j = 0; j < DIM; j++) {
            col[j] = puzzle[j][i];
        }
        //printf("col[%02d] = %s\n", i, col);
        add(col, strlen(col));
    }

    diagonal(DIM,DIM, puzzle);
    rotate(puzzle, rotation);
    diagonal(DIM,DIM, rotation);
    //show(rotation, DIM);
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
    char *found;
    //printf("find: %s\n", word);
    for (i = 0; i < MAX_ENTRIES; i++) {
        char *dict = dictionary[i];
        char rev[MAX_STR_LEN];
        memset(rev, '\0', MAX_STR_LEN);
        reverse(dict, rev, strlen(dict));
        //printf("check => %s, rev => %s\n", dict, rev);
        if ((found=strstr(dict, word))) {
            printf("found: fwd %s => %s @ %ld\n", word, dict, found-dict);
            return 1;
        }
        if ((found=strstr(rev, word))) {
            printf("found: rev %s => %s @ %ld\n", word, rev, found-rev);
            return 1;
        }
    }
    return 0;
}

int main()
{
    int i;

    show(puzzle, DIM);
    show_words();

    traverse();

    for (i = 0; i < NUM_WORDS; i++) {
        if (search(words[i])) {
            //printf("found: %s\n", words[i]);
        } else {
            printf("not found: %d %s\n", i, words[i]);
        }
    }

}

