#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

// gcc repl0.c mpc.c -ledit

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


int startup_puma()
{
    mpc_parser_t *Adjective = mpc_new("adjective");
    mpc_parser_t *Noun      = mpc_new("noun");
    mpc_parser_t *Phrase    = mpc_new("phrase");
    //mpc_parser_t *Number    = mpc_new("number");
    mpc_parser_t *Puma      = mpc_new("puma");

    mpca_lang(MPCA_LANG_DEFAULT,
            "                               \
            adjective : \"wow\"             \
                      | \"many\"            \
                      | \"so\"              \
                      | \"such\";           \
            noun      : \"puma\"            \
                      | \"language\"        \
                      | \"book\"            \
                      | \"build\"           \
                      | \"c\";              \
            phrase    : <adjective> <noun>; \
            puma      : <phrase>*;          \
            ",
            Adjective, Noun, Phrase, Puma);


    while (1) {
        char *input = readline("puma> "); // prompt
        add_history(input);
        if (strcmp(input, "quit") == 0) break;
        printf("%s\n", input);
        mpc_result_t r;
        if (mpc_parse("<stdin", input, Puma, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            // there was an error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);
    }

    mpc_cleanup(1, Adjective, Noun, Phrase, Puma);

    return 0;
}

int main(int argc, char *argv[])
{

    puts("puma ver 0.01");
    puts("press ^-C to exit\n");

    startup_puma();

}

