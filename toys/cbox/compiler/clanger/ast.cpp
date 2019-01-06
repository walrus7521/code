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

typedef struct ast_node {
    token_type type;
    int level;
    string address;
    vector<shared_ptr<ast_node>> sibs;
    shared_ptr<ast_node> child;
} ast_node;

int level = 0;
int current_level = 0;
stack<shared_ptr<ast_node>> node_stack;
vector<shared_ptr<symbol_t>> symtab;
vector<string> file;

shared_ptr<ast_node> create_ast_node(token_type type, const string address);
void add_sibling(shared_ptr<ast_node> tree, shared_ptr<ast_node> node);
void add_child(shared_ptr<ast_node> tree, shared_ptr<ast_node> node);
token_type find_token(const char *line, string &address);
char *get_text_type(token_type type);
shared_ptr<symbol_t> lookup(string name);

shared_ptr<ast_node> create_ast_node(token_type type, const string address)
{
    shared_ptr<ast_node> node = std::make_shared<ast_node>();
    node->type = type;
    node->address = address;
    return node;
}

shared_ptr<symbol_t> lookup(string name)
{
    for (auto& sym : symtab) {
        if (sym->name == name) {
            return sym;
        }
    }
    return nullptr;
}

void add_sibling(shared_ptr<ast_node> tree, shared_ptr<ast_node> node)
{
    if (nullptr == tree || nullptr == node) return;
    tree->sibs.push_back(node);
}

void add_child(shared_ptr<ast_node> tree, shared_ptr<ast_node> node)
{
    if (nullptr == tree || nullptr == node) return;
    //printf("add child: %s->%s\n", get_text_type(tree->type), get_text_type(node->type));
    tree->child = node;
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
    if (next = strstr(line, "TranslationUnitDecl")) {
        type = TranslationUnitDecl;
    } else
    if (next = strstr(line, "TypedefDecl")) {
        type = TypedefDecl;
    } else
    if (next = strstr(line, "RecordDecl")) {
        type = RecordDecl;
    } else
    if (next = strstr(line, "FieldDecl")) {
        type = FieldDecl;
    } else
    if (next = strstr(line, "EnumDecl")) {
        type = EnumDecl;
    } else
    if (next = strstr(line, "EnumConstantDecl")) {
        type = EnumConstantDecl;
    } else
    if (next = strstr(line, "FunctionDecl")) {
        type = FunctionDecl;
    } else
    if (next = strstr(line, "ParmVarDecl")) {
        type = ParmVarDecl;
    } else
    if (next = strstr(line, "VarDecl")) {
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

int get_level(const char *line)
{
    //printf("level: '%s'\n", line);
    if (line[0] != '|' && line[0] != '`') return 0;
    int level = 1;
    int i = 0;
    if (line[0] == ' ' || line[0] == '`') return current_level;
    while (true) {
        if (line[i] == '|') {
            if (line[i+1] == '-') return level;
            if (line[i+1] == ' ') {
                i+=2;
                level++;
                continue;
            } else {
                return current_level;
            }
        } else {
            return current_level;
        }
    }
}

void walk(shared_ptr<ast_node> root, char *pattern, int level)
{
    printf("%s\n", get_text_type(root->type));
    printf("sibs: ");
    for (auto& sib : root->sibs) {
        printf("%s ", get_text_type(sib->type));
    }
    printf("\n");
    if (root->child) {
        walk(root->child, pattern, level+1);
    }
}

void get_fields(shared_ptr<symbol_t> sym)
{
    string address;
    string line;
    int line_no = 1;
    token_type tok;
    char *next = NULL;
    //printf("find: %s\n", sym->addr.c_str());
    for (auto& line : file) {
        tok = find_token(line.c_str(), address);
        if (tok == RecordDecl) {
            //printf("got rec: %s\n", line.c_str());
            if (strstr(line.c_str(), sym->addr.c_str()) &&
                strstr(line.c_str(), "struct definition")) {
                //printf("found rec: %s\n", line.c_str());
                string field = file[line_no+1];
                int i = line_no+1;
                while ((tok = find_token(file[i].c_str(), address)) == FieldDecl) {
                    line = file[i];
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
                        //printf("ine: %d field: %s\n", line_no, lsyms);
                        token_class tclass = find_class(lsyms);

                        k = 0;
                        while (lsyms[j] != ' ') name[k++] = lsyms[j++];
                        name[k] = '\0';
                        while (lsyms[j] != '\'') j++; j++; // twice
                        k = 0;
                        while ((lsyms[j] != '\'') && (lsyms[j] != ' ')) type[k++] = lsyms[j++];
                        type[k] = '\0';
                        //printf("line: %d name: '%s' is a [%s]\n", line_no, name, type);
                        shared_ptr<field_t> field = std::make_shared<field_t>();
                        field->tclass = tclass;
                        field->name   = string(name);
                        field->type   = string(type);
                        sym->fields.push_back(field);
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
    shared_ptr<ast_node> root;
    shared_ptr<ast_node> current_node = nullptr;
    string address;
    string line;
    token_type tok;
    int line_no = 1;
    while (getline(std::cin, line)) file.push_back(line);

    for (auto& line : file) {
        tok = find_token(line.c_str(), address);
        if (tok  != Undef) {
            //printf("bam %d @ %x line: %d\n", tok, address, line_no);
            level = get_level(line.c_str());
            shared_ptr<ast_node> node = create_ast_node(tok, address);
            if (tok == TranslationUnitDecl) {
                // create root
                root = node;
                current_node = root;
            } else {
                if (tok == TypedefDecl) {
                    build_symtab(line, line_no);
                }
#if 0
                printf("bam %d @ %x %d -> %s line: %d\n", tok, address, level, get_text_type(tok), line_no);
                if (current_level != level) {
                    printf("chg level %d\n", level-current_level);
                    if (level > current_level) {
                        node_stack.push(node);
                        add_child(current_node, node);
                        current_node = node;
                    } else {
                        current_node = node_stack.top();
                        node_stack.pop();
                    }
                    current_level = level;
                } else {
                    add_sibling(current_node, node);
                }
#endif
            }
        }
        line_no++;
    }

    //string locate = string("EULER_ANGLES");
    string locate = string("TELEMETRY_LOG_STRUCT");
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

    printf("dump symtab for %s\n", locate.c_str());
    for (auto& sym : symtab) {
        if (sym->name == locate) {
            printf("[%08x]: %s\n", sym->addr.c_str(), sym->name.c_str());
            for (auto& field : sym->fields) {
                if (field->tclass == Nonterminal) {
                    printf("locate: %s\n", field->name.c_str());
                } else {
                    printf("  [%s]: %s class: %d\n", field->type.c_str(), field->name.c_str(), field->tclass);
                }
            }
        }
    }

    //printf("walk the tree\n");
    //walk(root, "dude", 0);
}

