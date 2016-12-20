#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
    List *list = createList();
    insertList(list, 1);
    insertList(list, 3);
    insertList(list, 5);
    showList(list);
}
