#include <stdio.h>
#include <stdlib.h>

// gcc repl0.c -ledit

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {
}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
//#include <editline/history.h>
#endif


//static char input[2048];

int main(int argc, char *argv[])
{
    puts("repl ver 0.01");
    puts("press ^-C to exit\n");

    while (1) {
        char *input = readline("repl> "); // prompt

        add_history(input);

        printf("%s\n", input);

        free(input);
    }
}

