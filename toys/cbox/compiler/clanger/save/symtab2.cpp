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
#include <iterator> 
#include "symtab.h"

using namespace std;

vector<shared_ptr<symbol_t>> symtab;
vector<string> file;

shared_ptr<symbol_t> lookup(string name)
{
    for (auto& sym : symtab) {
        if (sym->name == name) {
            return sym;
        }
    }
    return nullptr;
}

void symtab_dump(string locate)
{
    printf("enter: %s\n", locate.c_str());
    if (locate.length() == 0) {
        printf("zero len\n");
        return;
    } else {
        shared_ptr<symbol_t> sym = lookup(locate);
        printf("sym\n");
        for (auto& field : sym->fields) {
            printf("next\n");
            //if (nullptr == field) {
            //    printf("\n");
            //    continue;
            //}
            if (field->tclass == Nonterminal) {
                symtab_dump(field->name);
            } else {
                printf("%s : %s\n", field->name.c_str(), field->type.c_str());
            }
        }
    }
}

void symtab_dump2(string locate)
{
    if (locate.length() == 0) {
        for (auto& sym : symtab) {
            printf("[%08x]: %s\n", sym->addr.c_str(), sym->name.c_str());
            for (auto& field : sym->fields) {
                printf("  [%s]: %s class: %d\n", field->type.c_str(), field->name.c_str(), field->tclass);
            }
        }
    } else {
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
                printf("%s : %s\n", field->name.c_str(), field->type.c_str());
            }
        }
    }
}

token_type get_token(string line, prim_type& ptype)
{
    char *next = NULL;
    unsigned int addr;
    token_type type = Undef;
    char *pline = (char *) line.c_str();
    //printf("find token: %s\n", pline);
    if ((next = (char *) strstr(pline, "struct"))) {
        type = Struct;
    } else
    if ((next = (char *) strstr(pline, "union"))) {
        type = Union;
    } else
    if ((next = (char *) strstr(pline, "void"))) {
        type = Function;
    } else
    if ((next = (char *) strstr(pline, "enum"))) {
        type = Enum;
    }
    if (type == Struct) {
        if ((next = (char *) strstr(pline, "float"))) {
            type = Primitive;
            ptype = Float;
        } else if ((next = (char *) strstr(pline, "unsigned char"))) {
            type = Primitive;
            ptype = Unsigned_Char;
        } else if ((next = (char *) strstr(pline, "signed char"))) {
            type = Primitive;
            ptype = Signed_Char;
        } else if ((next = (char *) strstr(pline, "unsigned short"))) {
            type = Primitive;
            ptype = Unsigned_Short;
        } else if ((next = (char *) strstr(pline, "signed short"))) {
            ptype = Signed_Short;
            type = Primitive;
        } else if ((next = (char *) strstr(pline, "unsigned long"))) {
            type = Primitive;
            ptype = Unsigned_Long;
        } else if ((next = (char *) strstr(pline, "signed long"))) {
            type = Primitive;
            ptype = Signed_Long;
        } else if ((next = (char *) strstr(pline, "unsigned __int64"))) {
            type = Primitive;
            ptype = Unsigned_LongLong;
        } else if ((next = (char *) strstr(pline, "_Bool"))) {
            type = Primitive;
            ptype = Boolean;
        } else if ((next = (char *) strstr(pline, "unsigned char*"))) {
            type = Primitive;
            ptype = Pointer;
        } else if ((next = (char *) strstr(pline, "char*"))) {
            type = Primitive;
            ptype = Pointer;
        } else if ((next = (char *) strstr(pline, "int"))) {
            type = Primitive;
            ptype = Signed_Long;
        } else if ((next = (char *) strstr(pline, "long"))) {
            type = Primitive;
            ptype = Signed_Long;
        } else if ((next = (char *) strstr(pline, "u8"))) {
            type = Primitive;
            ptype = Boolean;
        } else if ((next = (char *) strstr(pline, "U8"))) {
            type = Primitive;
            ptype = Boolean;
        }

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
        case Struct:    return (char *) "Struct";
        case Union:     return (char *) "Union";
        case Enum:      return (char *) "Enum";
        case Primitive: return (char *) "Primitive";
        case Undef:     return (char *) "Undef";
    }
    return (char *) "Undef";
}


int get_last_line(int line_nr)
{
    stack<char> s;
    int line_no = line_nr;
    int level = 0;
    char c;
    //printf("first: %d\n", line_no);
    while (true) {
        string line = file[line_no];
        if (strstr(line.c_str(), "{")) {
            //printf("push0: %d\n", line_no);
            s.push('{');
            line_no++;
            level++;
            break;
        }
        line_no++;
    }

    while (level) {
        string line = file[line_no];
        if (strstr(line.c_str(), "{")) {
            s.push('{');
            level++;
        } else if (strstr(line.c_str(), "}")) {
            c = s.top();
            s.pop();
            level--;
        }
        line_no++;
    }

    return line_no-1;

}

string get_name(int line_no)
{
    string line = file[line_no];
    string name = string("");
    if (strstr(line.c_str(), "}")) {
        int j = line.size() - 1;
        while (line[j] != ' ') j--;
        int len = line.size() - j - 1;
        name = line.substr(j+1,len-1);
    }
    return name;
}

void Parse_Field(string line, int line_no, string& name, string& type)
{
    char n[256] = {0};
    char t[256] = {0};
    int i = 0;
    
    //printf("parse field: %s\n", line.c_str());

    while (line[i] == ' ') i++;
    int j = 0;
    while (line[i] != ' ') t[j++] = line[i++];

    while (line[i] == ' ') i++;
    j = 0;
    if (line[i] == '*') {
        i++;
        while (line[i] == ' ') i++;
    }
    while (line[i] != ';') n[j++] = line[i++];

    name = string(n);
    type = string(t);
}

void Parse_Struct(string line, int lstart, int lend)
{
    string name = get_name(lend);
    //printf("struct[%d,%d]: %s\n", lstart, lend, name.c_str());
    shared_ptr<symbol_t> sym = std::make_shared<symbol_t>();
    sym->name = name;
    sym->type = string("struct");
    // walk fields
    for (int i = lstart+1; i < lend; i++) { //+1 skips '{'
        string line = file[i];
        if (line[0] == '#') continue;
        if (line.length() == 0) continue;
        if (strstr(line.c_str(), "union")) continue;
        if (strstr(line.c_str(), "struct")) continue;
        string name, type;
        Parse_Field(line, i, name, type);
        //printf("field: %s %s\n", name.c_str(), type.c_str());
        shared_ptr<field_t> field = std::make_shared<field_t>();
        token_class tclass = find_class(line.c_str());
        field->tclass = tclass;
        field->name   = name;
        field->type   = type;
        sym->fields.push_back(field);
    }
    symtab.push_back(sym);
}

void Parse_Union(string line, int lstart, int lend)
{
    //printf("union[%d,%d]: %s\n", lstart, lend, line.c_str());
}

void Parse_Enum(string line, int lstart, int lend)
{
    //printf("enum[%d,%d]: %s\n", lstart, lend, line.c_str());
    // walk fields
}

void Parse_Primitive(string line, prim_type ptype, int lstart, int lend)
{
    //printf("prim[%d,%d]: %s", lstart, lend, line.c_str());
    if (lstart == lend) {
        switch (ptype) {
            case Unsigned_Char:     break;
            case Signed_Char:       break; 
            case Unsigned_Short:    break; 
            case Signed_Short:      break; 
            case Unsigned_Long:     break; 
            case Signed_Long:       break; 
            case Float:             break; 
            case Boolean:           break; 
            case Prim_undef:        break; 
        }
        int j = line.size() - 1;
        while (line[j] != ' ') j--;
        int len = line.size() - j - 1;
        std::string name = line.substr(j+1,len-1);
        //printf("name: %s\n", name.c_str());
        shared_ptr<symbol_t> sym = std::make_shared<symbol_t>();
        sym->name = name;
        sym->type = string("primitive");
        symtab.push_back(sym);
    }
}

int main()
{
    string address;
    prim_type ptype;
    string line;
    token_type tok;
    int line_no = 1;
    int last_line;
    int i;
    while (getline(std::cin, line)) file.push_back(line);
    int num_lines = file.size();

    for (i = 0; i < num_lines; i++) {
        line = file[i];
        //printf("%s\n", line.c_str());
        if (strstr(line.c_str(), "typedef")) {
            tok = get_token(line, ptype);
            //printf("tok %s %s @ %d\n", get_text_type(tok), line.c_str(), line_no);
            switch (tok) {
                case Struct:
                    //printf("struct %s @ %d\n", line.c_str(), line_no);
                    last_line = get_last_line(line_no);
                    Parse_Struct(line, line_no, last_line); 
                    break;
                case Union:
                    last_line = get_last_line(line_no);
                    Parse_Union(line, line_no, last_line); 
                    break;
                case Enum:
                    last_line = get_last_line(line_no);
                    Parse_Enum(line, line_no, last_line); 
                    break;
                case Primitive:
                    Parse_Primitive(line, ptype, line_no, line_no); 
                    break;
                case Undef:
                default:
                    //printf("undef: %s\n", line.c_str()); break;
                    break;
            }
        }
        line_no++;
    }

    string locate = "";
    //locate = string("MCP_COEFF_STRUCT");
    //locate = string("TELEMETRY_LOG_STRUCT");
    //string locate = string("EULER_ANGLES");
    //symtab_dump(locate);
    symtab_dump2(locate);

    return 0;
}

