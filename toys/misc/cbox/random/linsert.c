#include <stdio.h>
#include <stdlib.h>

#define LE(a,b) (a <= b)
#define LT(a,b) (a < b)
#define GE(a,b) (a >= b)
#define GT(a,b) (a > b)
#define EQ(a,b) (a == b)

struct _link {
    struct _link *next;
    int val;
};

void payload_swap(struct _link *a, struct _link *b) {
    int tmp;
    tmp = a->val;
    a->val = b->val;
    b->val = tmp;
}

void show(struct _link *head) {
    int i;
    struct _link *n = head->next;
    while (n) {
        printf("a: %d\n", n->val);
        n = n->next;
    }
    printf("\n");
}

void insert_sort(struct _link *head) {
/*
 * insertion into ordered list
 * part is the partition between the ordered
 * upper portion and the unordered lower
 * portion of the list. as new items are 
 * encountered, a forward scan is performed 
 * from the beginning of the list to the postion
 * where the new item exists in the list, ie
 * part.
 */
    struct _link *part, *iter, *scan;
    int tmp;
    
    iter = head->next;
    part = iter->next;
    while (iter->next) {
        part = iter->next;
        scan = head->next; /* of the sorted space where to do the insert */
        show(head);       /* scan is the forward itertor, pre lags one  */
        while (scan != part) {
            printf("iter %d, part %d, scan %d\n", iter->val, part->val, scan->val);
            if (LT(part->val, scan->val)) {
                printf("insert: (part %d) before (scan %d)\n", part->val, scan->val);
                payload_swap(part, scan);
            }
            scan = scan->next;
        }
        iter = iter->next;
    }
    show(head);
}

void insert_sort_swaplinks(struct _link *head) {
/*
 * insertion into ordered list
 * part is the partition between the ordered
 * upper portion and the unordered lower
 * portion of the list. as new items are 
 * encountered, a forward scan is performed 
 * from the beginning of the list to the postion
 * where the new item exists in the list, ie
 * part.
 */
    struct _link *part, *iter, *scan, *prescan, *prepart;
    int tmp;
    
    iter = head->next;
    part = iter->next;
    while (iter->next) {
        prepart = iter;
        part = iter->next;
        prescan = head;       /* these variables are for the linear scan    */
        scan = prescan->next; /* of the sorted space where to do the insert */
        show(head);       /* scan is the forward itertor, pre lags one  */
        while (scan != part) {
            printf("iter %d, prescan %d, part %d, scan %d\n", iter->val, prescan->val, part->val, scan->val);
            if (LT(part->val, scan->val)) {
                printf("insert: (part %d) before (scan %d)\n", part->val, scan->val);
                /* first extract part from its location */
                prepart->next = part->next;
                /* next insert part into its new location */
                part->next = scan;
                prescan->next = part;
                /* fixup iterator */
                iter = prepart;
                goto next_i;
            }
            scan = scan->next;
            prescan = prescan->next;
        }
        iter = iter->next;
next_i: ;
    }
    show(head);
}

void insert(struct _link *head, int x) {
    struct _link *n = (struct _link *) malloc(sizeof(struct _link));
    n->val = x;
    n->next = NULL;
    n->next = head->next;
    head->next = n;
}

int main() {
    struct _link *head = (struct _link *) malloc(sizeof(struct _link));
    insert(head, 8);
    insert(head, 9);
    insert(head, 2);
    insert(head, 4);
    insert(head, 7);
    insert(head, 1);
    insert(head, 3);
    //insert_sort(head);
    insert_sort_swaplinks(head);
    return 0;
}
