#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int v;
    struct _node *next;
} Node, List;

List *createList() {
    List *list = (List *) malloc(sizeof(List));
    list->next = NULL;
    return list;
}

void insertList(List *head, int val) {
    if (head->next == NULL) {
        head->next = createList();
        head->next->v = val;
    } else {
        Node *node = createList();
        node->v = val;
        node->next = head->next;
        head->next = node;
    }
}

void showList(List *head) {
    if (head->next == NULL) return;
    Node *node = head->next;
    while (node) {
        printf("Node: %d\n", node->v);
        node = node->next;
    }
}

