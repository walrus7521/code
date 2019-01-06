#include <iostream>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <regex>
#include <cstring>

using namespace std;

typedef enum token_type {
    TranslationUnitDecl,
    TypedefDecl,
    RecordDecl,
    FieldDecl,
    EnumDecl,
    EnumConstantDecl,
    FunctionDecl,
    ParmVarDecl,
    VarDecl,
    Undef,

} token_type;

typedef enum token_class {
    Terminal,
    Nonterminal
} token_class;

typedef struct field_t {
    token_class tclass;
    string type;
    string name;
} field_t;

typedef struct symbol_t {
    string name;
    string addr;
    vector<shared_ptr<field_t>> fields;
} symbol_t;


int level = 0;
int current_level = 0;
vector<shared_ptr<symbol_t>> symtab;
vector<string> file;

token_type find_token(const char *line, string &address);
char *get_text_type(token_type type);
shared_ptr<symbol_t> lookup(string name);


shared_ptr<symbol_t> lookup(string name)
{
    for (auto& sym : symtab) {
        if (sym->name == name) {
            return sym;
        }
    }
    return nullptr;
}

string get_address(const char *line)
{
    char num[8] = {0};
    char *pnum = num;
    while (*line++ != '0') ;
    while (*line++ != 'x') ;
    while (*line != ' ') {
        *pnum++ = *line++;
    }
    int inum = strtoul(num, NULL, 16);
    //printf("num: %s %x\n", num, inum);
    return string(num);
}

token_type find_token(const char *line, string &address)
{
    char *next = NULL;
    unsigned int addr;
    token_type type;
    if ((next = (char *) strstr(line, "TranslationUnitDecl"))) {
        type = TranslationUnitDecl;
    } else
    if ((next = (char *) strstr(line, "TypedefDecl"))) {
        type = TypedefDecl;
    } else
    if ((next = (char *) strstr(line, "RecordDecl"))) {
        type = RecordDecl;
    } else
    if ((next = (char *) strstr(line, "FieldDecl"))) {
        type = FieldDecl;
    } else
    if ((next = (char *) strstr(line, "EnumDecl"))) {
        type = EnumDecl;
    } else
    if ((next = (char *) strstr(line, "EnumConstantDecl"))) {
        type = EnumConstantDecl;
    } else
    if ((next = (char *) strstr(line, "FunctionDecl"))) {
        type = FunctionDecl;
    } else
    if ((next = (char *) strstr(line, "ParmVarDecl"))) {
        type = ParmVarDecl;
    } else
    if ((next = (char *) strstr(line, "VarDecl"))) {
        type = VarDecl;
    } else {
        type = Undef;
    }
    if (next) {
        address = get_address(next);
    }
    return type;
}

token_class find_class(const char *line)
{
    token_class tclass = Nonterminal;
    if (strstr(line, "F32")) {
        tclass = Terminal;
    } else
    if (strstr(line, "U32")) {
        tclass = Terminal;
    }
    if (strstr(line, "U8")) {
        tclass = Terminal;
    }
    return tclass;
}

char *get_text_type(token_type type)
{
    switch (type) {
        case TranslationUnitDecl: return (char *) "TranslationUnitDecl";
        case TypedefDecl: return (char *) "TypedefDecl";
        case RecordDecl: return (char *) "RecordDecl";
        case FieldDecl: return (char *) "FieldDecl";
        case EnumDecl: return (char *) "EnumDecl";
        case EnumConstantDecl: return (char *) "EnumConstantDecl";
        case FunctionDecl: return (char *) "FunctionDecl";
        case ParmVarDecl: return (char *) "ParmVarDecl";
        case VarDecl: return (char *) "VarDecl";
        case Undef: return (char *) "Undef";
    }
}

void get_fields(shared_ptr<symbol_t> sym)
{
    string address;
    string line;
    int line_no = 1;
    token_type tok;
    char *next = NULL;
    bool trace = false;
    if (sym->name == string("TELEMETRY_LOG_STRUCT")) {
        trace = true;
        printf("find: %s %s\n", sym->addr.c_str(), sym->name.c_str());
    }
    for (auto& line : file) {
        tok = find_token(line.c_str(), address);
        if (tok == RecordDecl) {
            //if (trace) printf("got rec: %s\n", line.c_str());
            if (strstr(line.c_str(), sym->addr.c_str()) &&
                strstr(line.c_str(), "struct definition")) {
                if (trace) printf("found rec: %s\n", line.c_str());
                string field = file[line_no];
                int i = line_no;
                while ((tok = find_token(file[i].c_str(), address)) != Undef) {
                    line = file[i];
                    if (tok == FieldDecl) {
                        std::string key ("col:");
                        size_t found = line.rfind(key);
                        if (found != std::string::npos) {
                            int len = line.size() - found - 1;
                            std::string syms = line.substr(found,len);
                            char *lsyms = (char *) syms.c_str();
                            char name[256] = {0};
                            char type[256] = {0};
                            int j = 0;
                            int k = 0;
                            while (lsyms[j] != ' ') j++;
                            while (lsyms[j] == ' ') j++;
                            if (trace) printf("ine: %d field: %s\n", i, lsyms);
                            token_class tclass = find_class(lsyms);

                            k = 0;
                            while (lsyms[j] != ' ') name[k++] = lsyms[j++];
                            name[k] = '\0';
                            while (lsyms[j] != '\'') j++; j++; // twice
                            k = 0;
                            while ((lsyms[j] != '\'') && (lsyms[j] != ' ')) type[k++] = lsyms[j++];
                            type[k] = '\0';
                            if (trace) printf("line: %d name: '%s' is a [%s]\n", i, name, type);
                            shared_ptr<field_t> field = std::make_shared<field_t>();
                            field->tclass = tclass;
                            field->name   = string(name);
                            field->type   = string(type);
                            sym->fields.push_back(field);
                        }
                    } else
                    if (tok == RecordDecl) {
                        if (strstr(line.c_str(), "union definition")) {
                            printf("union line: %d field: %s\n", i, line.c_str());
                        } else if (strstr(line.c_str(), "struct definition")) {
                            printf("struct line: %d field: %s\n", i, line.c_str());
                        }
                    }
                    i++;
                }
            }
        }
        line_no++;
    }
}

void build_symtab(string line, int line_no)
{
    std::string key (":'");
    size_t found = line.rfind(key);
    if (found != std::string::npos) {
        found += 2;
        int len = line.size() - found - 1;
        std::string symbol = line.substr(found,len);
        string addr_line = file[line_no+2];
        string addr = get_address(addr_line.c_str());
        //printf("sym: %d : %s @ 0x%x\n", line_no, symbol.c_str(), addr);
        shared_ptr<symbol_t> sym = std::make_shared<symbol_t>();
        sym->name = symbol;
        sym->addr = addr;
        symtab.push_back(sym);
        get_fields(sym);
    }
}

int main()
{
    string address;
    string line;
    token_type tok;
    int line_no = 1;
    while (getline(std::cin, line)) file.push_back(line);

    for (auto& line : file) {
        tok = find_token(line.c_str(), address);
        if (tok == TypedefDecl) {
            build_symtab(line, line_no);
        }
        line_no++;
    }


    //string locate = string("EULER_ANGLES");
    string locate = string("TELEMETRY_LOG_STRUCT");

#if 1
    shared_ptr<symbol_t> sym = lookup(locate);
    for (auto& field : sym->fields) {
        if (nullptr == field) {
            printf("\n");
            continue;
        }
        if (field->tclass == Nonterminal) {
            //printf("%s", field->name.c_str());
            shared_ptr<symbol_t> sym2 = lookup(field->type);
            if (nullptr == sym2) {
                printf("\n");
                continue;
            }
            for (auto& field2 : sym2->fields) {
                if (nullptr == field2) {
                    printf("\n");
                    continue;
                }
                printf("%s.%s : %s\n", field->name.c_str(), field2->name.c_str(), field2->type.c_str());
            }
        } else {
            printf("%s.%s : %s\n", field->name.c_str(), field->name.c_str(), field->type.c_str());
        }
    }
    
    return 0;
#endif
#if 0
    printf("dump symtab for %s\n", locate.c_str());
    for (auto& sym : symtab) {
        if (sym->name == locate) {
            printf("[%08x]: %s\n", sym->addr.c_str(), sym->name.c_str());
            for (auto& field : sym->fields) {
                //if (field->tclass == Nonterminal) {
                //    printf("locate: %s\n", field->name.c_str());
                //} else {
                    printf("  [%s]: %s class: %d\n", field->type.c_str(), field->name.c_str(), field->tclass);
                //}
            }
        }
    }
#endif
}

