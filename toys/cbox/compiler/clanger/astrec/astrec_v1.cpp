#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <stack>
#include <memory>
#include <string>
#include <vector>

#define ARRAY_SUPPORT (0)

static bool in_struct = false;
static bool in_field = false;
static bool got_leaf = false;
static bool in_skip = false;
static bool is_array = false;
static std::stack<std::string> stacker;

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
  tok_eof = -1,

  tok_pipe = -2,

  // primary
  tok_type = -3,
  tok_type_ident = -4, // union, struct, enum
  tok_identifier = -5,
  tok_offset = -6,
  tok_attributes = -7,

  tok_comment = -8,
};

static std::string TagStr;        // 
static std::string TypeStr;       // 
static std::string TypeIdentStr;  // 
static std::string IdentifierStr; // Filled in if tok_identifier
static std::string CommentStr;    // 
static std::string AttribsStr;    // Filled in if tok_attributes
static std::string ArraySzStr;    // 
static int OffsetVal;             // 
static int ArraySize;
#define LEVEL_INTERVAL (2)
static int indentation = 0;

int set_indent(int indent)
{
    indentation = indent;
}

int get_indent()
{
    return indentation;
}

/// gettok - Return the next token from standard input.
static int gettok()
{
    static int LastChar = ' ';
    static int indent = 0;

    // Skip any whitespace.
    while (isspace(LastChar)) {
        indent++;
        LastChar = getchar();
    }

    // Get OFFSET
    //printf("last: %c\n", LastChar);
    if (isdigit(LastChar)) { // Number: [0-9]+
        std::string NumStr;
        do {
            indent++;
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar));
        OffsetVal = strtoul(NumStr.c_str(), nullptr, 0);    
        return tok_offset;
    }
  
    while (isspace(LastChar)) LastChar = getchar();
    // Get PIPE
    if (LastChar == '|') {
        LastChar = getchar();
        return tok_pipe;
    }

    while (isspace(LastChar)) LastChar = getchar();
    // Get TYPE_IDENT? (union, struct, enum)
    if (islower(LastChar)) { // identifier: [a-z]+
        //printf("start type\n");
        TypeIdentStr = LastChar;
        set_indent(indent);
        indent = 0;
        while (islower((LastChar = getchar()))) {
            TypeIdentStr += LastChar;
        }
        if ((LastChar == '\n') || (LastChar == '\r')) {
            //printf("end type1: %s\n", TypeStr.c_str());
            return tok_type_ident;
        }
        while (isspace(LastChar)) LastChar = getchar();
        if ((LastChar == '\n') || (LastChar == '\r')) {
            //printf("end type2: %s\n", TypeStr.c_str());
            return tok_type_ident;
        }
    }// else 
    // Get IDENTIFIER
    if (isalpha(LastChar) || (LastChar == '_')) { // identifier: [a-zA-Z][a-zA-Z0-9_]*
        //printf("start type\n");
        TypeStr = LastChar;
        set_indent(indent);
        indent = 0;
        while (isalnum((LastChar = getchar())) || (LastChar == '_')) {
            TypeStr += LastChar;
        }
        if ((LastChar == '\n') || (LastChar == '\r')) {
            //printf("end type1: %s\n", TypeStr.c_str());
            return tok_type;
        }
        while (isspace(LastChar)) LastChar = getchar();
        if ((LastChar == '\n') || (LastChar == '\r')) {
            //printf("end type2: %s\n", TypeStr.c_str());
            return tok_type;
        }
        // check for array here
        if (LastChar == '[') { // could be array or attribs -- lookahead for 'sizeof'
#if ARRAY_SUPPORT
            is_array = true;
#endif
            ArraySzStr.clear();
            //printf("%s in [", TypeStr.c_str());
            do {
                LastChar = getchar();
                ArraySzStr += LastChar;
            } while (LastChar != ']');
            ArraySize = strtoul(ArraySzStr.c_str(), nullptr, 0);    
            //printf("%d%c out\n", ArraySize, LastChar);
            LastChar = getchar();
            while (isspace(LastChar)) LastChar = getchar();
        }
        if (isalpha(LastChar) || (LastChar == '_')) { // identifier: [a-zA-Z][a-zA-Z0-9_]*
            IdentifierStr = LastChar;
            while (isalnum((LastChar = getchar())) || (LastChar == '_')) {
                IdentifierStr += LastChar;
            }
            //printf("end ident: %s %s\n", TypeStr.c_str(), IdentifierStr.c_str());
            return tok_identifier;
        }
    }

    if (LastChar == '[') { // could be array or attribs -- lookahead for 'sizeof'
        AttribsStr.clear();
        AttribsStr += LastChar;
        // Comment until end of line.
        do {
            LastChar = getchar();
            AttribsStr += LastChar;
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
        if (LastChar != EOF) {
            return tok_attributes; //gettok();
        }
    }

    if (LastChar == '*') {
        CommentStr += LastChar;
        // Comment until end of line.
        do {
            LastChar = getchar();
            CommentStr += LastChar;
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF) {
            return tok_comment; //gettok();
        }
    }

    // Check for end of file.  Don't eat the EOF.
    if (LastChar == EOF) {
        return tok_eof;
    }

    // Otherwise, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = getchar();

    return ThisChar;
}

//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the current
/// token the parser is looking at.  getNextToken reads another token from the
/// lexer and updates CurTok with its results.
static int CurTok;
static int getNextToken() { return CurTok = gettok(); }

std::string primitives[] = {
    "U8", "u8",
    "S8", "s8",
    "U16", "u16",
    "S16", "s16",
    "U32", "u32",
    "S32", "s32",
    "F32", "f32",
    "int",
    "BOOLEAN", "boolean",
    "",""
};
int num_prims = sizeof(primitives)/sizeof(primitives[0]);
bool is_leaf(std::string tok)
{
    for (auto& s : primitives) {
        if (tok == s) return true;
    }
    return false;
}

std::string type_idents[] = {
    "struct",
    "union",
    "enum"
    "",""
};
int num_type_idents = sizeof(type_idents)/sizeof(type_idents[0]);
bool is_type_idents(std::string id)
{
    for (auto& s : type_idents) {
        if (id == s) return true;
    }
    return false;
}

std::string extract_path(const std::stack<std::string>& path)
{
    std::stack<std::string> tmp = path;
    std::stack<std::string> rev;
    std::string full_path{""};
    bool first = true;

    while (tmp.size())
    {
        std::string item = tmp.top();
        tmp.pop();
        rev.push(item);
    }

    while (rev.size()) {
        if (first) {
            full_path += rev.top();
            first = false;
        } else {
            full_path += "." + rev.top();
        }
        rev.pop();
    }
    return full_path;
}

/// top ::= definition | external | expression | ';'
static void MainLoop()
{
    static int last_indent = 0;
    static int curr_indent = 0;
    static int delta_levels = 0;

    while (true) {
        switch (CurTok) {
        case tok_eof:
            //printf("got eof\n");
            return;
        case tok_pipe:
            //printf("got pipe | \n");
            break;
        case tok_offset:
            //if (in_struct == false) {
            //    in_struct = true;
            //printf("got offset: %d\n", OffsetVal);
            //}
            break;
        case tok_type_ident:
            //if (in_struct == false) {
            //    in_struct = true;
            if (is_type_idents(TypeIdentStr)) {
                printf("got type ident: %s\n", TypeIdentStr.c_str());
            }
            //}
            break;
        case tok_type:
            if (in_struct == false) {
                in_struct = true;
                TagStr = TypeStr;
            }
            // print the top level record name and offset
            printf("top: %d %s %s\n", OffsetVal, IdentifierStr.c_str(), TagStr.c_str());
            stacker=std::stack<std::string>();
            break;
        case tok_identifier:
            curr_indent = get_indent();
            delta_levels = (curr_indent - last_indent) / LEVEL_INTERVAL;
            //printf("%d: curr: %d - last: %d\n", delta_levels, curr_indent, last_indent);
            if (!is_leaf(TypeStr)) {
                if (got_leaf) {
                    got_leaf = false;
                    if (stacker.size() > 0 && delta_levels < 0) { //curr_indent < last_indent) {
                        //printf("do %d pops: %d\n", abs(delta_levels), stacker.size());
                        for (int i = 0; i < abs(delta_levels) && stacker.size() > 0; i++) {
                            std::string popper = stacker.top();
                            stacker.pop();
                            //printf("pop: %s\n", popper.c_str());
                        }
                        stacker.push(IdentifierStr);
                        //printf("push: %s\n", IdentifierStr.c_str());
                    }
                }
                in_field = true;
                // workarounds
                if (strstr(TypeStr.c_str(), "ENUM")) {
                    TypeStr = "U32";
                } else if (is_array){
                } else {
                    if (delta_levels >= 0) {
                        stacker.push(IdentifierStr);
                        //printf("push: %s\n", IdentifierStr.c_str());
                    }
                }
            } else {
                got_leaf = true;
                std::string Path = std::string("");
                Path = extract_path(stacker);
                if (is_array) {
                    printf("  %04d %s.%s [%d] : %s\n", OffsetVal, Path.c_str(), IdentifierStr.c_str(), ArraySize, TypeStr.c_str());
                    is_array = false;
                } else {
                    printf("  %04d %s.%s : %s\n", OffsetVal, Path.c_str(), IdentifierStr.c_str(), TypeStr.c_str());
                }
            }
            last_indent = curr_indent;
            break;
        case tok_attributes:
            printf("got attribs: %s\n", AttribsStr.c_str());
            in_struct = false;
            break;
        case tok_comment:
            break;
        default:
            break;
        }
        getNextToken();
    }
}

int main()
{
    getNextToken();
    MainLoop();
    return 0;
}

