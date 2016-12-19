#include "List.hpp"

int main()
{
    struct Node *list = createList();
    insertList(list, 1);
    insertList(list, 3);
    insertList(list, 5);
    insertList(list, 7);
    showList(list);
}
