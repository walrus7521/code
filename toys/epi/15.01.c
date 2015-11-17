#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "../toys/tree.h"

int is_bst_helper(tree *root, int lower, int upper) {
    if (root == NULL) {
        return 1;
    } else
    if (root->value < lower || root->value > upper) {
        return 0;
    }
    return is_bst_helper(root->left, lower, root->value) &&
           is_bst_helper(root->right, root->value, upper);
}

int is_bst(tree *root) {
    return is_bst_helper(root, INT_MIN, INT_MAX);
}

// or do a BFS and check for BST property on each node
#define QUEUESIZE 256
tree *my_queue[QUEUESIZE] = {0};
int qcount, qfirst, qlast;

void qinit()
{
    int i;
    for (i = 0; i < QUEUESIZE; i++)
        my_queue[i] = NULL;
    qcount = 0;
    qfirst = 0;
    qlast = QUEUESIZE-1;
}

void my_enqueue(tree *x)
{
    if (qcount < QUEUESIZE) {
        qlast = (qlast+1) % QUEUESIZE;
        my_queue[qlast] = x;
        qcount++;
    }
}

tree *my_dequeue()
{
    tree *x;
    if (qcount > 0) {
        x = my_queue[qfirst];
        qfirst = (qfirst + 1) % QUEUESIZE;
        qcount--;
    }
    return x;
}

int is_bst2(tree *T) // level traverse
{
    tree *t = NULL;
    qinit();
    my_enqueue(T);
    while (qcount > 0) {
        t = my_dequeue();
        if (t) {
            if ((t->left && t->value < t->left->value) || (t->right && t->value > t->right->value)) {
                return 0;
            }
            if (t->left) my_enqueue(t->left);
            if (t->right) my_enqueue(t->right);
        }
    }
    return 1;
}


void mydump(void *t)
{
    tree *tr = (tree *) t;
    printf("tree->value = %d\n", tr->value);
}

int main()
{
    tree *T = NULL, *t;
    int p;
    T = tinsert(T, 4); T = tinsert(T, 2); T = tinsert(T, 8);
    T = tinsert(T, 1); T = tinsert(T, 5); 
    //T = tinsert(T, 7);
    //tlevel(T);
    //tshow(T);
    //tdelete(T, 4);
    //tshow(T);
    tshow(T, mydump);
    p = is_bst2(T);
    printf("is bst? %d\n", p);
    return 0;
}
