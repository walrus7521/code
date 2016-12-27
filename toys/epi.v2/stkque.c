#include "pch.h"

/*
 * fix max --> heap
 *
 */

struct list {
    struct list *next;
    struct list *last;
    int val;
    int max;
};

enum {
    INVALID = -1
};

struct list *create(int val)
{
    struct list *l = (struct list *) malloc(sizeof(struct list));
    l->val = val;
    l->max = INT_MIN;
    l->next = NULL;
    l->last = NULL;
    return l;
}

void set_max(struct list *head, int val)
{
    if (val > head->max) head->max = val;
}

int get_max(struct list *head)
{
    return head->max;
}

int get(struct list *head)
{
    int val = INVALID;
    struct list *n = head->next;
    if (head->next == NULL) {
        return val;
    } else
    if (head->next->next == NULL) {
        val = n->val;
        free(n);
        head->next = head->last = NULL;
        return val;
    } else { 
        // find 2nd to last node
        while (n->next->next != NULL) {
            n = n->next;
        }
        struct list *r = head->last;
        head->last = n;
        n->next = NULL;
        val = r->val;
        free(r);
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
    printf("max: %d\n", head->max);
    while (n) {
        printf("n: %d\n", n->val);
        n = n->next;
    }
}

int main()
{
    struct list *head = create(0);
    push(head, 42);
    push(head, 67);
    put(head, 43);
    put(head, 68);
    show(head);
    while (!empty(head)) {
        printf("pop: %d\n", pop(head));
        //printf("get: %d\n", get(head));
    }
}
