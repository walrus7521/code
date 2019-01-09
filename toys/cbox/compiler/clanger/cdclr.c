/*
 * https://github.com/shburns/cdecl/blob/master/cdclr.c
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Constants -- mostly arbitrary
#define MAX_DCLR_LEN 512
#define MAX_TOKEN_LEN 8
#define MAX_TOKEN_COUNT 64
#define EXIT_CONDITION -1

//For easy determination of type.
enum type_tag {
    QUALIFIER,
    TYPE,
    IDENTIFIER
};

//Constitutes a lexical token and it's type
typedef struct {
    char type;
    char string[MAX_TOKEN_LEN];
} token;

//Static variables
static token stack[MAX_TOKEN_COUNT];
static char decl[MAX_DCLR_LEN];
static int declPos = 0;
static int stackPos = -1;

//Write the entire declaration to a char* for easier management of character access (for me, at least).
int readNewDeclaration(void) {
    int index = 0;
    printf("Enter a new C declaration to analyze (type 'exit' to quit):\n\n");
    while((decl[index++] = getchar()) != '\n' && (index < MAX_DCLR_LEN)) { }
    decl[--index] = '\0';
    if (!strcmp(decl, "exit")) {
        return -1;
    }
    printf("\n\n");
    return 0;
}

/*
    For a given lexical token, determine if it's a pointer, array bracket, function or
    grouping parenthesis, qualifier, type, or identifier.
*/
char getTokenType(char* str) {
    if (strlen(str) == 1)
        if (!isalpha(str[0]) && !isdigit(str[0]))
            return str[0];

    if (!strcmp(str, "const") || !strcmp(str, "auto") || !strcmp(str, "register") ||
        !strcmp(str, "volatile") || !strcmp(str, "static") || !strcmp(str, "extern")) {
            return QUALIFIER;
    } else if (!strcmp(str, "char") || !strcmp(str, "double") || !strcmp(str, "enum") ||
        !strcmp(str, "float") || !strcmp(str, "int") || !strcmp(str, "long") ||
        !strcmp(str, "short") || !strcmp(str, "signed") || !strcmp(str, "struct") ||
        !strcmp(str, "typedef") || !strcmp(str, "union") || !strcmp(str, "unsigned") ||
        !strcmp(str, "void")) {
            return TYPE;
    } else {
        return IDENTIFIER;
    }
}

/*
    Read from the declaration currently stored in teh "decl" array and create a token object
    to be handled by the declarator printing method, or added to the stack
*/
token getToken(void) {
    char c = decl[declPos++];
    int tokenPos = 0;
    token t;

    //Move through whitespace
    if (iswspace(c))
        while (iswspace(c)) 
            c = decl[declPos++];
    //Get single character token types e.g. - * & ( ) [ ]
    if (!isalpha(c) && !isdigit(c)) {
        t.string[tokenPos++] = c;
        //Account for any enum, typedef, or struct by moving through code blocks enclosed by "{..}"
        if (c == '{') {
            while ((c = decl[declPos++]) != '}') { }
            return getToken();
        }
    } else {
        //Build string value until the character returned is whitespace, or non-alphanumeric
        while (!iswspace(c) && (isalpha(c) || isdigit(c))) {
            t.string[tokenPos++] = c;
            c = decl[declPos++];
        }
        //Move the 'declPos' pointer back by one space to make sure no tokens are lost.
        declPos--;
    }
    //Terminate the string literal, then get the type.
    t.string[tokenPos] = '\0';
    t.type = getTokenType(t.string);
    return t;
}

//Read to first identifier, and put all tokens into a stack to be popped when parsing.
void buildTokenStack(void) {
    while (stack[stackPos].type != IDENTIFIER) {
        stack[++stackPos] = getToken();
    }
}

//Print Identifier and start printing the parsed declaration.
void printIdentifier(void) {
    printf("%s is a ", stack[stackPos--].string);
}

//Read the array and get the size of it for printing, then print.
void dealWithArray(void) {
    int i = 0;
    int arraySize = 0;
    token t;
    while((t = getToken()).type != ']') {
        //Assumes the only thing between square brackets will be a number
        for (i = 0; i < strlen(t.string); i++) {
            arraySize *= 10;
            arraySize += t.string[i] - '0';
        }
        printf("array[0..%d] of ", (arraySize - 1));
    }
}

//Read through function arguments (per the spec in the assignment)
void dealWithFunctionArguments(void) {
    token t;
    while((t = getToken()).type != ')') { }
    printf("function returning ");
}

//Read back through any number of pointers until a non-pointer type or qualifier is arrived at.
void dealWithPointers(void) {
    while(stack[stackPos].type == '*') {
        printf("pointer to ");
        stackPos--;
    }
}

//Recursively process declaration and print to screen.
void printDeclaration(void) {
    token t = getToken();
    if (t.type == '[') {
        dealWithArray();
    } else if (t.type == '(') {
        dealWithFunctionArguments();
    }
    dealWithPointers();
    while(stackPos > -1) {
        t = stack[stackPos--];
        if (t.type == '(') {
            getToken();
            printDeclaration();
        } else {
            printf("%s ", t.string);
        }
    }
}

//main method. starts program loop requesting declarations and parsing accordingly.
void main (void) {
    int i;
    while (readNewDeclaration() != EXIT_CONDITION) {
        stackPos = 0;
        declPos = 0;
        buildTokenStack();
        printIdentifier();
        printDeclaration();
        printf("\n\n");
    }
}
