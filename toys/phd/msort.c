#include <stdio.h>
#include <stdlib.h>

#define LE(x, y) ((x) <= (y))

typedef struct _list {
    struct _list *next, *tail;
    int val;
    int count;
} link, list;

void show(list *head) {
    int i;
    link *n = head->next;
    printf("list count %d\n", head->count);
    while (n) {
        printf("[%d] -> ", n->val);
        n = n->next;
    }
    printf("{{nil}}\n");
}

list *new() {
    link *n = (link *) malloc(sizeof(link));
    n->tail = n->next = NULL;
    n->count = 0;
    return n;
}

void insert(list *head, int x) {
    link *n = (link *) malloc(sizeof(link));
    n->val = x;
    n->next = head->next;
    head->next = n;
    head->count++;
}

void update_count(list *head)
{
    int count = 0;
    list *tmp = head->next;
    while (tmp) {
        ++count;
        tmp = tmp->next;
    }
    head->count = count;
}

void divide(list *l, list *sec) {
    link *current, *midpoint;
    if ((midpoint = l->next) == NULL) {
        sec = NULL;
    } else {
        for (current = midpoint->next; current; ) {
            current = current->next;
            if (current) {
                midpoint = midpoint->next;
                current = current->next;
            }
        }
        sec->next = midpoint->next;
        midpoint->next = NULL;
    }
    update_count(l);
    update_count(sec);
}

void merge(list *first, list *second, list *out)
{
    link *p1, *p2;
    link *lastsorted;
    printf("calling merge...sz1: %d, sz2: %d\n", first->count, second->count);
    if (!first->next) 
        *out = *second;
    else if (!second->next) 
        *out = *first;
    else {
        p1 = first->next;
        p2 = second->next;
        if (LE(p1->val, p2->val)) {
            *out = *first;
            p1 = p1->next;
        } else {
            *out = *second;
            p2 = p2->next;
        }
        lastsorted = out->next;
        while (p1 && p2) {
            if (LE(p1->val, p2->val)) {
                lastsorted->next = p1;
                lastsorted = p1;
                p1 = p1->next;
            } else {
                lastsorted->next = p2;
                lastsorted = p2;
                p2 = p2->next;
            }
        }
        if (p1)
            lastsorted->next = p1;
        else
            lastsorted->next = p2;
    }
    update_count(first);
    update_count(second);
    update_count(out);
}

void merge_sort(list *head) {
    list *sec = new();
    if (head->count > 1) {
        divide(head, sec);
        merge_sort(head);
        merge_sort(sec);
        merge(head, sec, head);
        show(head);
    }
}

int main()
{
    list *h = new();
    insert(h, 8);
    insert(h, 9);
    insert(h, 2);
    insert(h, 4);
    insert(h, 7);
    insert(h, 1);
    insert(h, 3);
    show(h);
    merge_sort(h);
    return 0;

}
