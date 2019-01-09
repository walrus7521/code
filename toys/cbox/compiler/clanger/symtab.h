#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <regex>
#include <iterator> 

typedef enum token_type {
    Struct,
    Union,
    Enum,
    Primitive,
    Function,
    Undef,

} token_type;

typedef enum prim_type {
    Unsigned_Char,
    Signed_Char,
    Unsigned_Short,
    Signed_Short,
    Unsigned_Long,
    Signed_Long,
    Float,
    Boolean,
    Prim_undef

} prim_type;

typedef enum token_class {
    Terminal,
    Nonterminal
} token_class;

typedef struct field_t {
    token_class tclass;
    std::string name;
    std::string type;
} field_t;

typedef struct symbol_t {
    std::string name;
    std::string type;
    std::string addr;
    std::vector<std::shared_ptr<field_t>> fields;
} symbol_t;

token_type get_token(std::string line, std::string &address);
char *get_text_type(token_type type);
std::shared_ptr<symbol_t> lookup(std::string name);


#endif // _SYMTAB_H_
