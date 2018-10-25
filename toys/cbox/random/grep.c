#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);

int match(char *regexp, char *text)
{
    if (regexp[0] == '^') {
        // since we have a ^, the pattern must
        // match at the beginning of line
        return matchhere(regexp+1, text);
    }
    do {
        // otherwise, it can match anywhere
        if (matchhere(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}

int matchhere(char *regexp, char *text)
{
    if (regexp[0] == '\0') {
        return 1;
    }
    if (regexp[1] == '*') { // match any number of the
                           // preceding char [0]
        return matchstar(regexp[0], regexp+2, text);
    }
    if (regexp[0] == '$' && regexp[1] == '\0') {
        return *text == '\0';
    }
    if (*text != '\0'  && (regexp[0] == '.' || regexp[0] == *text)) {
        return matchhere(regexp+1, text+1);
    }
    return 0;
}

// greedy matchstar - right to left
// useful for substitution operations
int matchstar2(int c, char *regexp, char *text)
{
    char *t;
    for (t = text; *t != '\0' && (*t == c || c == '.'); t++) ;
    do { // matches zero or more
        if (matchhere(regexp, t)) {
            return 1;
        }
    } while (t --> text);
    return 0;
}

// non-greedy matchstar
int matchstar(int c, char *regexp, char *text)
{
    do {
        if (matchhere(regexp, text)) {
            return 1;
        }
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}

// scan single file, calling match on each line
int grep(char *regexp, FILE *f, char *name)
{
    int n, nmatch, lineno=0;
    char buf[BUFSIZ];

    //printf("grep: regex: %s, name: %s\n", regexp, name);
    nmatch = 0;
    while (fgets(buf, sizeof(buf), f) != NULL) {
        n = strlen(buf);
        if (n > 0 && buf[n-1] == '\n') {
            buf[n-1] = '\0';
        }
        if (match(regexp, buf)) {
            nmatch++;
            if (name != NULL) {
                printf("=> %s: ", name);
            }
            printf("line %d :  %s\n", lineno, buf);
        }
        lineno++;
    }
    return nmatch;
}

void usage()
{
    printf("usage: grep regexp [file ...]");
}

int main(int argc, char *argv[])
{
    int i, nmatch;
    FILE *f;

    //setprogname("grep");
    if (argc < 2) {
        usage();
    }

    nmatch = 0;
    if (argc == 2) {
        if (grep(argv[1], stdin, NULL)) {
            nmatch++;
        }
    } else {
        for (i = 2; i < argc; i++) {
            f = fopen(argv[i], "r");
            if (f == NULL) {
                printf("can't open %s:", argv[i]);
                continue;
            }
            if (grep(argv[1], f, argc>3 ? argv[i] : NULL) > 0) {
                nmatch++;
            }
            fclose(f);
        }
    }
    return nmatch == 0;
}
