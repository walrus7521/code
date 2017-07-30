#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )

typedef struct _tree {
    struct _tree *left, *right;
    int val;
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

tree *insert(tree *root, int data)
{
    if (root == NULL) {
        root = (tree *) malloc(sizeof(tree));
        root->val = data;
        root->left = root->right = NULL;
    } else
    if      (data < root->val) root->left  = insert(root->left, data);
    else if (data > root->val) root->right = insert(root->right, data);
    else                         printf("got a dup %d\n", data);
    return root;
}

tree *findmax(tree *T) {
    tree *t = T;
    while (t->right)
        t = t->right;
    return t;
}

tree *delete(tree *root, int val)
{
    tree *temp;
    printf("delete - enter (%d)\n", val);
    if (root != NULL) {
        if      (val < root->val) root->left = delete(root->left, val);
        else if (val > root->val) root->right = delete(root->right, val);            
        else {
            printf("found a match\n");
            if (root->left && root->right) {
                printf("delete has 2 children for %d\n", val);
                temp = findmax(root->left);
                root->val = temp->val;
                root->left = delete(root->left, root->val);
            } else {
                temp = root;
                if (root->left == NULL) {
                    printf("delete has 1 right child for %d\n", val);
                    root = root->right;
                }
                if (root->right == NULL) {
                    printf("delete has 1 left child for %d\n", val);
                    root = root->left;
                }
                free(temp);
            }
        }
    }
    return root;
}

void bfs(tree *T) // level traverse
{
    tree *t = NULL;
    qinit();
    enqueue(T);
    while (qcount > 0) {
        t = dequeue();
        if (t) {
            printf("t: %d \n", t->val);
            if (t->left) enqueue(t->left);
            if (t->right) enqueue(t->right);
        }
    }
}

tree *find(tree *T, int val)
{
    if (T == NULL) return NULL;
    if      (T->val < val) find(T->right, val);
    else if (T->val > val) find(T->left, val);
    else {
        printf("found it %d\n", T->val);
        return T;
    }
    return NULL;
}

void tshow(tree *T)
{
    if (T != NULL) {
        tshow(T->left);
        printf("T->val %d\n", T->val);
        tshow(T->right);
    }
}

int main()
{
    tree *T = NULL, *t;
    T = insert(T, 4); T = insert(T, 2); T = insert(T, 8);
    T = insert(T, 1); T = insert(T, 5); T = insert(T, 7);
    bfs(T);
    //tshow(T);
    //delete(T, 4);
    //tshow(T);
    return 0;
}
