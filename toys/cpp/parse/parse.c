#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    WHITE, LETTER, DIGIT, SPECIAL, EOF_CODE, COMMENT, SEPARATOR, LABELS,
} CHAR_CODE;

typedef enum {
    TRANSPORT_MODE,
    SCENARIO,
    SEND_SPARSE,
    RING_SPARSE,
    WAIT_ON_SIGNAL,
    END,
    VAR,
    LABEL,
} RESERVED_TYPE;

char *reserved[] = {
    "TRANSPORT_MODE",
    "SCENARIO",
    "SEND_SPARSE",
    "RING_SPARSE",
    "WAIT_ON_SIGNAL",
    "GOTO",
    "END",
    "VAR",
    "LABEL",
};
int num_reserved = sizeof(reserved)/sizeof(reserved[0]);

typedef enum {
    KEYWORD, OPERAND,
} SYM_TYPE;

CHAR_CODE char_table[256];

typedef struct {
    int num;
    RESERVED_TYPE type;
    char toks[32][256];
} tokens;

int line_no = 0;
char token[256];
tokens toks;
char *ptoken;
char *skipwhite(char *line) {
    while (char_table[*line] == WHITE) line++;
    return line;
}

void init() {
    for (int i =  0;  i < 256; ++i) char_table[i] = SPECIAL;
    for (int i = '0'; i < '9'; ++i) char_table[i] = DIGIT;
    for (int i = 'A'; i < 'Z'; ++i) char_table[i] = LETTER;
    for (int i = 'a'; i < 'z'; ++i) char_table[i] = LETTER;
    char_table['_'] = LETTER;
    char_table['('] = SEPARATOR;
    char_table[')'] = SEPARATOR;
    char_table[','] = SEPARATOR;
    char_table[' '] = WHITE;
    char_table['\n'] = WHITE;
    char_table['\t'] = WHITE;
    char_table['#']  = COMMENT;
    char_table[':']  = LABELS;
}

int is_white(char ch) {
    if (char_table[ch] == WHITE) return 1;
    return 0;
}

int is_sep(char ch) {
    if (char_table[ch] == SEPARATOR) return 1;
    return 0;
}

int is_label(char ch) {
    if (char_table[ch] == LABELS) return 1;
    return 0;
}

int is_comment(char ch) {
    if (char_table[ch] == COMMENT) return 1;
    return 0;
}

char *get_word(char *line) {
    memset(token, 0, 256);
    ptoken = token;
    while ((char_table[*line] == LETTER) ||
           (char_table[*line] == DIGIT)) {
        //printf("%c ", *line);
        *ptoken++ = *line++;
    }
    *ptoken = '\0';
    //printf("get_word: %s\n", token);
    return token;
}

char *get_number(char *line) {
    memset(token, 0, 256);
    ptoken = token;
    while (char_table[*line] == DIGIT) {
        //printf("%c ", *line);
        *ptoken++ = *line++;
    }
    *ptoken = '\0';
    //printf("get_word: %s\n", token);
    return token;
}

void handler(tokens *toks) {
    //printf("token[0]: %s\n", toks->toks[0]);
    //return;
    for (int i = 0; i < toks->num; ++i) {
        printf("token[%02d]: %s\n", i, toks->toks[i]);
    }
}

tokens* scan(char *line, size_t len) {
    int i = 0, tok_num = 0;
    //printf("line[%02d]: %s", line_no++, line);
    memset((void *) &toks, 0, sizeof(tokens));
    while (i < len) {
        memset(token, 0, 256);
        memset(&toks.toks[tok_num], 0, 256);
        while (i < len && is_white(line[i])) ++i;
        int j = i;
        if (is_comment(line[i])) break;
        while (j < len && !is_white(line[j]) && !is_sep(line[j])) ++j;
        if (i != j) {
            int k;
            for (k = 0; k < j-i; ++k) token[k] = line[i+k];
            token[k] = '\0';
            if (is_label(line[j-1])) {
                char tmp[256] = {0};
                token[k-1] = '\0'; // delete the colon
                sprintf(tmp, "%s:=%s", "LABEL", token);
                memset(token, 0, 256);
                sprintf(token, "%s", tmp);
                //printf("label[%02d]: %s\n", tok_num, token);
                ++j;
                toks.type = LABEL;
            } else {
                //printf("token[%02d]: %s\n", tok_num, token);
            }
            if (is_sep(line[j])) ++j;
            i = j;
        }
        strcpy(toks.toks[tok_num], token);
        toks.num++;
        tok_num++;
    }
    return &toks;
}

int main(void)
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    tokens *toks;

    stream = fopen("puma.sc", "r");
    if (stream == NULL)
        exit(EXIT_FAILURE);

    init();
    while ((read = getline(&line, &len, stream)) != -1) {
        toks = scan(line, read);
        for (int i = 0; i < num_reserved; ++i) {
            if (!strcmp((const char *) toks->toks[0], reserved[i])) {
                //printf("%s...\n", reserved[i]);
                handler(toks);
                break;
            }
        }
        if (toks->type == LABEL) {
            handler(toks);
        }
    }

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}

