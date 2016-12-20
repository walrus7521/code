#include <stdio.h>
#include <stdlib.h>

//struct List Node;
struct Node {
    int v;
    struct Node *next;
};

struct Node *createList() {
    struct Node *list = (struct Node *) malloc(sizeof(struct Node));
    list->next = NULL;
    return list;
}

void insertList(struct Node *head, int val) {
    if (head->next == NULL) {
        head->next = createList();
        head->next->v = val;
    } else {
        struct Node *node = createList();
        node->v = val;
        node->next = head->next;
        head->next = node;
    }
}

void showList(struct Node *head) {
    if (head->next == NULL) return;
    struct Node *node = head->next;
    while (node) {
        printf("Node: %d\n", node->v);
        node = node->next;
    }
}
