#include <stdio.h>
#include <string.h>
//http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c
//
#if 0
//
//// Define your enumeration like this (in say numbers.h);
ENUM_BEGIN( Numbers )
    ENUM(ONE),
    ENUM(TWO),
    ENUM(FOUR)
ENUM_END( Numbers )

// The macros are defined in a more fundamental .h file (say defs.h);
#define ENUM_BEGIN(typ) enum typ {
#define ENUM(nam) nam
#define ENUM_END(typ) };

// Now in one and only one .c file, redefine the ENUM macros and reinclude
//  the numbers.h file to build a string table
#undef ENUM_BEGIN
#undef ENUM
#undef ENUM_END
#define ENUM_BEGIN(typ) const char * typ ## _name_table [] = {
#define ENUM(nam) #nam
#define ENUM_END(typ) };
#undef NUMBERS_H_INCLUDED   // whatever you need to do to enable reinclusion
#include "numbers.h"

// Now you can do exactly what you want to do, with no retyping, and for any
//  number of enumerated types defined with the ENUM macro family
//  Your code follows;
char num_str[10];
int process_numbers_str(Numbers num) {
  switch(num) {
    case ONE:
    case TWO:
    case THREE:
    {
      strcpy(num_str, Numbers_name_table[num]); // eg TWO -> "TWO"
    } break;
    default:
      return 0; //no match
  return 1;
}

// Sweet no ? After being frustrated by this for years, I finally came up
//  with this solution for my most recent project and plan to reuse the idea
//  forever

#endif

//#define PRINT_MCP_FAULT(token) printf(#token "[%03x]: %36s level %d\n", token, mcp_fault_2[token].name, mcp_fault_2[token].level)

#define ENUM_BEGIN(typ) enum typ {
#define ENUM(nam) #nam
#define ENUM_END(typ) };

ENUM_BEGIN(MY_ENUM)
    MY_ENUM_ONE,
    MY_ENUM_TWO,
    MY_ENUM_THREE,
ENUM_END(MY_ENUM)

//typedef enum
//{
//    MY_ENUM_ONE,
//    MY_ENUM_TWO,
//    MY_ENUM_THREE,
//} MY_ENUM;

#undef ENUM_BEGIN
#undef ENUM
#undef ENUM_END

#define ENUM_BEGIN(typ) const char * typ ## _name_table [] = {
#define ENUM(nam) #nam
#define ENUM_END(typ) };

ENUM_BEGIN(MY_ENUM)
    ENUM(MY_ENUM_ONE),
    ENUM(MY_ENUM_TWO),
    ENUM(MY_ENUM_THREE),
ENUM_END(MY_ENUM)

char num_str[10];
char *process_numbers_str(int num) {
//    switch(num) {
//    case MY_ENUM_ONE:
//    case MY_ENUM_TWO:
//    case MY_ENUM_THREE:
//    {
      strcpy(num_str, MY_ENUM_name_table[num]); // eg TWO -> "TWO"
//    } break;
//    default:
//      return 0; //no match
  return num_str;
}

//#define SHOW_ENUM_NAME( element ) #element
#define DECL_ENUM_ELEMENT( element ) case element: return #element; break;
#define PRINT_ELEMENT( element ) { printf("-> %s\n", process_numbers_str( element )); }
int main()
{
    //printf("element: %d\n", MY_FAULT_FORCE_CAUTION);
    //printf("element: %s\n", SHOW_ENUM_NAME(MY_FAULT_FORCE_CAUTION));

//    printf("=> %s\n", SHOW_ENUM_NAME(0x124));

    PRINT_ELEMENT(0);
    PRINT_ELEMENT(1);
    PRINT_ELEMENT(2);

}

