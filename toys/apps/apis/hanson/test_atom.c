#include <stdio.h>
#include <string.h>
#include "atom.h"

int main()
{
    const char *str = "now is the time for all good men.";
    const char *atom = Atom_new(str, strlen(str));
    printf("str: %s\n", Atom_string(atom));
    printf("int: %s\n", Atom_int(42));
    printf("len: %d\n", Atom_length(atom));

}

