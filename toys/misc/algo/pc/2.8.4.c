#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 6
 * and
 * dick
 * jane
 * puff
 * spot
 * yertle
 * bjvg xsb hxsn xsb qymm xsb rqat xsb pnetfn
 * xxxx yyy zzzz www yyyy aaa bbbb ccc dddddd
 */

//#define dprintf printf
#define dprintf(...)

#define MAX_WORD 32
#define MAX_LINE 120
#define MAX_DICT 1024
#define MAX_ALPHA 26
#define INVALID_CODE '*'
int       candidates[MAX_DICT];
int            idict[MAX_DICT];
char            dict[MAX_DICT][MAX_WORD];
int           icrypt[MAX_DICT];
char           crypt[MAX_DICT][MAX_WORD];
int          decoder[MAX_ALPHA];
int alpha_candidates[MAX_ALPHA];

int permute(char *cypher, char *dict, int len)
{
    int i, k, idx, match_count;
    char c, d, cc;
    int intra_alpha_candidates[MAX_ALPHA], intra_alpha_values[MAX_ALPHA];
    for (i = 0; i < MAX_ALPHA; i++) intra_alpha_candidates[i] = 1;
    for (i = 0; i < MAX_ALPHA; i++) intra_alpha_values[i] = INVALID_CODE;
    match_count = 0;
    for (i = 0; i < len; i++) { /* loop over dictionary entry */
        cc = c = cypher[i];
        d = dict[i];
        for (k = 0; k < MAX_ALPHA; k++, c++) { /* loop over alphabet */
            dprintf("    c[%d] = %c\n", k, c);
            if (c > 'z') c = 'a';
            idx = cc - 'a';
            if (d == c) {
                if ((intra_alpha_candidates[idx] == 1) || (intra_alpha_values[idx] == d)) {
                    dprintf("match goto next i = %d on cc = %c d = %c\n", idx, cc, d);
                    match_count++;
                    intra_alpha_candidates[idx] = 0;
                    intra_alpha_values[idx] = d;
                    goto next_i;
                }
            }
        }
next_i: ;
    }

    if (match_count == len) {
        for (k = 0; k < len; k++) {
            idx = cypher[k] - 'a';
            dprintf("decoder[%d] = %c\n", idx, decoder[idx]);
            if (decoder[idx] == INVALID_CODE && alpha_candidates[idx] == 1) {
                decoder[idx] = dict[k];
                alpha_candidates[idx] = 0;
                dprintf("adding decoder[%d] = %c\n", idx, decoder[idx]);
            }
        }
    }
    return (match_count == len);
}

void decypher(int icypher)
{
    int i, match, idx, cylen;
    char c; 
    char *cystr = crypt[icypher];
    char *dict_str;
    cylen = icrypt[icypher];
    dprintf("decypher: %s\n", cystr);
    for (i = 0; i < MAX_DICT; i++) {
        if (idict[i] == cylen && candidates[i]) {
            dict_str = dict[i];
            candidates[i] = 0;
            dprintf("candidate: %s\n", dict_str);
            match = permute(cystr, dict_str, cylen);
            if (match) {
                dprintf("match..%s = %s, len %d\n", cystr, dict_str, cylen);
                return;
            } else {
                dprintf("not a match..%s = %s, len %d\n", cystr, dict_str, cylen);
            }
        }
    }
}

void decode(char *cystr, int len)
{
    int i, idx;
    for (i = 0; i < len; i++) {
        idx = cystr[i] - 'a';
        printf("%c", decoder[idx]);
    }
    printf(" ");
}

int main()
{
    int i, n, len, wc;
    char word[MAX_WORD], line[MAX_LINE], soln[MAX_WORD], *pline;
    scanf("%d\n", &n);
    dprintf("n = %d\n", n);
    for (i = 0; i < n; i++) {
        memset(dict[i], '\0', MAX_WORD);
        scanf("%s\n", dict[i]);
        idict[i] = strlen(dict[i]);
        dprintf("word[%d] = %s, len %d\n", i, dict[i], idict[i]);
    }
    memset(line, '\0', MAX_LINE);
    while (fgets(line, MAX_LINE, stdin)) {
        for (i = 0; i < MAX_ALPHA; i++) {
            decoder[i] = INVALID_CODE;
            alpha_candidates[i] = 1;
        }
        for (i = 0; i < MAX_DICT; i++) {
            candidates[i] = 1;
        }
        dprintf("line: %s", line);
        pline = line;
        wc = 0;
        while (*pline != '\0') {
            memset(crypt[wc], '\0', MAX_WORD);
            sscanf(pline, "%s", crypt[wc]);
            icrypt[wc] = strlen(crypt[wc]);
            decypher(wc);
            pline += icrypt[wc]+1;
            wc++;
        }
        dprintf("wc: %d\n", wc);
        for (i = 0; i < wc; i++) {
            decode(crypt[i], icrypt[i]);
        }
        printf("\n");
        memset(line, '\0', MAX_LINE);
        i = 0;
    }
    return 0;
}

