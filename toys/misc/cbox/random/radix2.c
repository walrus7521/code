#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 *  create a linked list of 3 character strings.
 *  create a list of [28] queues:
 *      [0] = blank
 *      [1..26] = upper/lower case chars
 *      [27] = all other chars
 *  
 *  split list into queues by character position:
 *      [0]->[1]->[2] => queues
 *      combine /append queues, keep order, no new list
 *      repeat
 *  
 *  final list is sorted.
 */

typedef struct _link {
    struct _link *next, *tail;
    char val[4];
} link, list, queue;

list *new() {
    list *n = (list *) malloc(sizeof(list));
    n->next = n->tail = NULL;
    return n;
}

void show(list *head) {
    list *link = head->next;
    while (link) {
        printf("%s\n", link->val);
        link = link->next;
    }
    printf("\n");
}

int is_empty(link *head) {
    return (head->next == NULL);
}

void insert_front(list *head, char val[3]) {
    link *n = new();
    strncpy(n->val, val, 3);
    n->val[3] = '\0';
    if (head->tail == NULL) { 
        head->tail = n;
        head->next = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
}

void insert_rear(list *head, char val[3]){
    link *n = new();
    strncpy(n->val, val, 3);
    n->val[3] = '\0';
    if (head->tail == NULL) {
        head->tail = n;
        head->next = n;
    } else {
        head->tail->next = n;
        head->tail = n;
    }
}

void remove_front(list *head, char val[4]) {
    link *v = head->next;
    if (head->next) {
        head->next = head->next->next;
    }
    strncpy(val, v->val, 3);
    val[3] = '\0';
    free(v);
}

void delete(list **head) {
    list *tmp, *link = *head;
    link = link->next;
    while (link) {
        tmp = link;
        link = link->next;
        free(tmp);
    }
    free(*head);
    head = NULL;
}

void append(list *head, list *other) {
    list *prev, *curr;
    curr = head->next;
    while (curr) {
        printf("append: %s\n", curr->val);
        prev = curr;
        curr = curr->next;
    }
    printf("append prev: %s\n", prev->val);
    prev->next = other->next;
}

list *rsort(list *head) {
    queue *q[28];
    list *link, *merge, *tmp;
    int i, c_idx, j;
    char c;
    for (i = 0; i < 28; ++i) {
        q[i] = new();
    }
    merge = new();
    merge->next = head->next;
    for (i = 2; i >= 0; --i) {
        link = merge->next;
        while (link) {
            c = link->val[i];
            c_idx = c - 'a' + 1;
            //printf("%s[%d] = %c idx %d\n", link->val, i, c, c_idx);
            if (isalpha(c)) insert_rear(q[c_idx], link->val);
            else if (c == ' ') insert_rear(q[0], link->val);
            else insert_rear(q[27], link->val);
            link = link->next;
        }
        /* delete the old merge */
        delete(&merge);
        /* combine (aka rethread) the queues into new merge list */
        merge = new();
        for (j = 0; j < 28; ++j) {
            if (!is_empty(q[j])) {
                while (!is_empty(q[j])) {
                    char val[4];
                    remove_front(q[j], val);
                    insert_rear(merge, val);
                }
                q[j]->tail = q[j]->next = NULL;
            }
        }
    }
    return merge;
}

int main()
{
    list *head, *merge;
    head = new();
    insert_front(head, "rap");
    insert_front(head, "tar");
    insert_front(head, "cot");
    insert_front(head, "top");
    insert_front(head, "car");
    insert_front(head, "map");
    insert_front(head, "cat");
    insert_front(head, "mop");
    insert_front(head, "rat");
    show(head);
    merge = rsort(head);
    show(merge);

    return 0;
}
