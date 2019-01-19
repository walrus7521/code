
#ifdef LLVM
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>
#endif
#include <vector>
#include <string>
#include <iostream>
#include <stdarg.h>
#include "calc.h"

using namespace llvm;

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

struct ast *root = NULL;

void dump_ast(struct ast *a);
Value* build_ir(struct ast *root);
llvm::Module *module;

//llvm::LLVMContext & context = getGlobalContext();
//llvm::IRBuilder<> builder(getGlobalContext());

static LLVMContext context;
static IRBuilder<> builder(context);

extern FILE *yyin;
extern int yyparse();
#define BUILD
int main(int argc, char **argv)
{
#ifdef BUILD
    module = new llvm::Module("calc", context);
    Value *result = NULL;

    // Setup main function and entry point
    llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
    llvm::Function *mainFunc =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
    builder.SetInsertPoint(entry);

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
#endif
}


