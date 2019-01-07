
#ifdef LLVM
#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#endif
#include <vector>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "calc.h"


void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

struct ast *root = NULL;

extern FILE *yyin;
extern int yyparse();
int main(int argc, char **argv)
{
    if (argc < 2) { /* just use stdin */
        yyin = stdin;
        printf("> ");
        yyparse();
    } else {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror(argv[1]);
            return (1);
        }
        yyin = f;
        yyparse();
        fclose(f);
    }
}


