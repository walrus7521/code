#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )

typedef struct _tree {
    struct _tree *left, *right;
    int value;
    int height;
} tree;

#define QUEUESIZE 256
tree *queue[QUEUESIZE] = {0};
int qcount, qfirst, qlast;

void qinit()
{
    int i;
    for (i = 0; i < QUEUESIZE; i++)
        queue[i] = NULL;
    qcount = 0;
    qfirst = 0;
    qlast = QUEUESIZE-1;
}

void enqueue(tree *x)
{
    if (qcount < QUEUESIZE) {
        qlast = (qlast+1) % QUEUESIZE;
        queue[qlast] = x;
        qcount++;
    }
}

tree *dequeue()
{
    tree *x;
    if (qcount > 0) {
        x = queue[qfirst];
        qfirst = (qfirst + 1) % QUEUESIZE;
        qcount--;
    }
    return x;
}

int theight(tree *root){
   if(root == NULL)
       return 0;
   return 1+MAX(theight(root->left), theight(root->right));
}

tree *tinsert(tree *root, int data)
{
    if (root == NULL) {
        root = (tree *) malloc(sizeof(tree));
        root->value = data;
        root->left = root->right = NULL;
    } else
    if      (data < root->value) root->left  = tinsert(root->left, data);
    else if (data > root->value) root->right = tinsert(root->right, data);
    else                         printf("got a dup %d\n", data);
    return root;
}

tree *tfindmax(tree *T) {
    tree *t = T;
    while (t->right)
        t = t->right;
    return t;
}

tree *tdelete(tree *root, int value)
{
    tree *temp;
    printf("tdelete - enter (%d)\n", value);
    if (root != NULL) {
        if      (value < root->value) root->left = tdelete(root->left, value);
        else if (value > root->value) root->right = tdelete(root->right, value);            
        else {
            printf("found a match\n");
            if (root->left && root->right) {
                printf("tdelete has 2 children for %d\n", value);
                temp = tfindmax(root->left);
                root->value = temp->value;
                root->left = tdelete(root->left, root->value);
            } else {
                temp = root;
                if (root->left == NULL) {
                    printf("tdelete has 1 right child for %d\n", value);
                    root = root->right;
                }
                if (root->right == NULL) {
                    printf("tdelete has 1 left child for %d\n", value);
                    root = root->left;
                }
                free(temp);
            }
        }
    }
    return root;
}

void tlevel(tree *T) // level traverse
{
    tree *t = NULL;
    qinit();
    enqueue(T);
    while (qcount > 0) {
        t = dequeue();
        if (t) {
            printf("t: %d \n", t->value);
            if (t->left) enqueue(t->left);
            if (t->right) enqueue(t->right);
        }
    }
}

tree *tfind(tree *T, int value)
{
    if (T == NULL) return NULL;
    if      (T->value < value) tfind(T->right, value);
    else if (T->value > value) tfind(T->left, value);
    else {
        printf("found it %d\n", T->value);
        return T;
    }
    return NULL;
}

void tshow(tree *T)
{
    if (T != NULL) {
        tshow(T->left);
        printf("T->value %d\n", T->value);
        tshow(T->right);
    }
}

int main()
{
    tree *T = NULL, *t;
    T = tinsert(T, 4); T = tinsert(T, 2); T = tinsert(T, 8);
    T = tinsert(T, 1); T = tinsert(T, 5); T = tinsert(T, 7);
    //tlevel(T);
    tshow(T);
    //tdelete(T, 4);
    //tshow(T);
    return 0;
}
