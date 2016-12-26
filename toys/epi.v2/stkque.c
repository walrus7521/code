#include "pch.h"

/*
 * Fix push/put (breaks pointer chain) & max
 *
 */

struct list {
    struct list *next;
    struct list *last;
    int val;
};

enum {
    INVALID = -1
};

struct list *create(int val)
{
    struct list *l = (struct list *) malloc(sizeof(struct list));
    l->val = val;
    l->next = NULL;
    l->last = NULL;
    return l;
}

void put(struct list *head, int val)
{
    struct list *n = create(val);
    if (head->next == NULL) {
        head->next = head->last = n;
    } else {
        head->last->next = n;
        head->last = n;
    }
}

int get(struct list *head)
{
    if (head->next == NULL) {
        return INVALID;
    } else
    if (head->next->next == NULL) {
        struct list *n = head->next;
        int val = n->val;
        printf("now last node (%p): %d\n", n, n->val);
        free(n);
        printf("post free\n");
        head->next = head->last = NULL;
        return val;
    } else { 
        // find 2nd to last node
        struct list *n = head->next;
        while (n->next->next != NULL) {
            n = n->next;
        }
        //printf("got 2nd to last node: %d\n", n->val);
        struct list *r = head->last;
        //printf("last node: %d\n", r->val);
        head->last = n;
        n->next = NULL;
        int val = r->val;
        free(n);
        return val;
    }
}

void push(struct list *head, int val)
{
    struct list *n = create(val);
    if (head->next == NULL) {
        head->next = head->last = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
}

int pop(struct list *head)
{
    if (head->next == NULL) {
        return INVALID;
    } else {
        struct list *n = head->next;
        head->next = n->next;
        int val = n->val;
        free(n);
        return val;
    }
}

int empty(struct list *head)
{
    if (head->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void show(struct list *head)
{
    struct list *n = head->next;
    while (n) {
        printf("n: %d\n", n->val);
        n = n->next;
    }
}

int main()
{
    struct list *head = create(0);
    //push(head, 42);
    push(head, 67);
    put(head, 43);
    //put(head, 68);
    show(head);
    while (!empty(head)) {
        //printf("pop: %d\n", pop(head));
        printf("get: %d\n", get(head));
    }
}
