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
  tok_unknown = -9,
  tok_array = -10
};

static std::string LexStr;        // 
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

void set_indent(int indent)
{
    indentation = indent;
}

int get_indent()
{
    return indentation;
}

typedef enum lexer_state {
    COMMENT_STATE,
    OFFSET_STATE,
    PIPE_STATE,
    TYPE_IDENT_STATE,
    TYPE_STATE,
    IDENT_STATE,
    ATTRIBS_STATE,
    ARRAY_STATE,
    UNKNOWN_STATE

} lexer_state;

lexer_state lex_state;


/// gettok - Return the next token from standard input.
static int gettok()
{
    static int LastChar = ' ';
    static int indent = 0;

    // Skip any whitespace.

    // Get OFFSET
    //printf("last: %c\n", LastChar);
    if (lex_state == OFFSET_STATE) {
        while (isspace(LastChar)) { indent++; LastChar = getchar(); }
        if (isdigit(LastChar)) { // Number: [0-9]+
            printf("offset time\n");
            std::string NumStr;
            do {
                indent++;
                LexStr += LastChar;
                LastChar = getchar();
            } while (isdigit(LastChar));
            //OffsetVal = strtoul(NumStr.c_str(), nullptr, 0);    
            return tok_offset;
        }
    }
  
    if (lex_state == PIPE_STATE) {
        while (isspace(LastChar)) { indent++; LastChar = getchar(); }
        // Get PIPE
        if (LastChar == '|') {
            LexStr = LastChar;
            printf("pipe time\n");
            return tok_pipe;
        }
    }

    // Get TYPE_IDENT? (union, struct, enum)
    if (lex_state == TYPE_IDENT_STATE) {
        while (isspace(LastChar)) LastChar = getchar();
        if (islower(LastChar)) { // identifier: [a-z]+
            printf("struct time\n");
            //printf("start type\n");
            TypeIdentStr = LastChar;
            LexStr = LastChar;
            set_indent(indent);
            indent = 0;
            while (islower((LastChar = getchar()))) {
                TypeIdentStr += LastChar;
                LexStr += LastChar;
            }
            return tok_type_ident;
        }// else 
    }
    
    // Get IDENTIFIER
    if (lex_state == TYPE_STATE) {
        while (isspace(LastChar)) LastChar = getchar();
        if (isalpha(LastChar) || (LastChar == '_')) { // identifier: [a-zA-Z][a-zA-Z0-9_]*
            printf("type time\n");
            //printf("start type\n");
            TypeStr = LastChar;
            LexStr = LastChar;
            set_indent(indent);
            indent = 0;
            while (isalnum((LastChar = getchar())) || (LastChar == '_')) {
                TypeStr += LastChar;
                LexStr += LastChar;
            }
            return tok_type;
        }
    }
    
    if (lex_state == ARRAY_STATE) {
        while (isspace(LastChar)) LastChar = getchar();
        // check for array here
        if (LastChar == '[') { // could be array or attribs -- lookahead for 'sizeof'
#if ARRAY_SUPPORT
            is_array = true;
#endif
            ArraySzStr.clear();
            LexStr.clear();
            //printf("%s in [", TypeStr.c_str());
            do {
                LastChar = getchar();
                ArraySzStr += LastChar;
                LexStr += LastChar;
            } while (LastChar != ']');
            return tok_array;
            //ArraySize = strtoul(ArraySzStr.c_str(), nullptr, 0);    
            //printf("%d%c out\n", ArraySize, LastChar);
            //LastChar = getchar();
        }
    }

    if (lex_state == IDENT_STATE) {
        while (isspace(LastChar)) LastChar = getchar();
        if (isalpha(LastChar) || (LastChar == '_')) { // identifier: [a-zA-Z][a-zA-Z0-9_]*
            printf("ident time\n");
            //printf("start type\n");
            TypeStr = LastChar;
            LexStr = LastChar;
            set_indent(indent);
            indent = 0;
            while (isalnum((LastChar = getchar())) || (LastChar == '_')) {
                TypeStr += LastChar;
                LexStr += LastChar;
            }
            return tok_identifier;
        }
    }

    if (LastChar == '[') { // could be array or attribs -- lookahead for 'sizeof'
        AttribsStr.clear();
        AttribsStr += LastChar;
        LexStr = LastChar;
        // Comment until end of line.
        do {
            LastChar = getchar();
            AttribsStr += LastChar;
            LexStr += LastChar;
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
        if (LastChar != EOF) {
            return tok_attributes; //gettok();
        }
    }

    //if (lex_state == COMMENT_STATE) {
        if (LastChar == '*') {
            CommentStr += LastChar;
            LexStr = LastChar;
            // Comment until end of line.
            do {
                LastChar = getchar();
                CommentStr += LastChar;
                LexStr += LastChar;
            } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

            if (LastChar != EOF) {
                return tok_comment; //gettok();
            }
        }
    //}

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

static void Parser()
{
    printf("%d %s %s\n", OffsetVal, IdentifierStr.c_str(), TypeStr.c_str());
}

/// top ::= definition | external | expression | ';'
static void MainLoop()
{
    static int last_indent = 0;
    static int curr_indent = 0;
    static int delta_levels = 0;

    while (true) {
        switch (CurTok) {
            case tok_comment:
                printf("got comment: ");
                lex_state = OFFSET_STATE;
                break;
            case tok_offset:
                printf("got offset: ");
                lex_state = PIPE_STATE;
                OffsetVal = strtoul(LexStr.c_str(), nullptr, 0);
                break;
            case tok_pipe:
                printf("got pipe: ");
                lex_state = TYPE_IDENT_STATE;
                break;
            case tok_type_ident:
                printf("got type ident: ");
                lex_state = TYPE_STATE;
                break;
            case tok_type:
                printf("got type: ");
                lex_state = IDENT_STATE;
                TypeStr = LexStr;
                //lex_state = ARRAY_STATE;
                break;
            case tok_array:
                printf("got array: ");
                lex_state = IDENT_STATE;
                break;
            case tok_identifier:
                printf("got ident: ");
                lex_state = IDENT_STATE;
                IdentifierStr = LexStr;
                break;
            case tok_attributes:
                printf("got attribs: ");
                Parser();
                lex_state = OFFSET_STATE;
                break;
            case tok_eof:
                printf("got eof: ");
                return;
            case tok_unknown:
                printf("got unknown: ");
                break;
            default:
                printf("got ???: ");
                if (lex_state == TYPE_IDENT_STATE) {
                    lex_state = TYPE_STATE;
                } else if (lex_state == TYPE_STATE) {
                    lex_state = IDENT_STATE;
                }
                break;
        }
        printf("%s\n", LexStr.c_str());
        LexStr.clear();
        getNextToken();
    }
    return;
    
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
    lex_state = OFFSET_STATE;
    getNextToken();
    MainLoop();
    return 0;
}

