#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )

typedef struct _tree {
    struct _tree *left, *right;
    int x, y;
    int height;
} tree;

int theight(tree *root){
   if(root == NULL)
       return 0;
   return 1+MAX(theight(root->left), theight(root->right));
}

tree *tinsert(tree *root, int sdata, int edata)
{
    if (root == NULL) {
        root = (tree *) malloc(sizeof(tree));
        root->x = sdata;
        root->y = edata;
        root->left = root->right = NULL;
    } else
    if (sdata < root->x) {
        root->left  = tinsert(root->left, sdata, edata);
        if ((theight(root->left) - theight(root->right)) == 2) {
            printf("out of balance: %d\n", sdata);
            if (sdata < root->left->x) {
                printf("avl_single_left\n");
            } else {
                printf("avl_double_left\n");
            }
        }
    } else 
    if (sdata > root->x) {
        root->right = tinsert(root->right, sdata, edata);
        if ((theight(root->left) - theight(root->right)) == 2) {
            printf("out of balance: %d\n", sdata);
            if (sdata < root->right->x) {
                printf("avl_single_right\n");
            } else {
                printf("avl_double_right\n");
            }
        }
    } else {
        printf("got a dup %d\n", sdata);
    }
    return root;
}

tree *tfindmax(tree *T) {
    tree *t = T;
    while (t->right) {
        t = t->right;
    }
    printf("tfindmax returning %d\n", t->x);
    return t;
}

tree *tfindmin(tree *T) {
    tree *t = T;
    while (t->left) {
        t = t->left;
    }
    return t;
}

tree *tdelete(tree *root, int x)
{
    tree *temp;
    printf("tdelete - enter (%d)\n", x);
    if (root != NULL) {
        if (x < root->x) {
            root->left = tdelete(root->left, x);
        } else if (x > root->x) {
            root->right = tdelete(root->right, x);            
        } else {
            printf("found a match\n");
            if (root->left && root->right) {
                printf("tdelete has 2 children for %d\n", x);
                temp = tfindmax(root->left);
                root->x = temp->x;
                root->left = tdelete(root->left, root->x);
            } else {
                temp = root;
                if (root->left == NULL) {
                    printf("tdelete has 1 right child for %d\n", x);
                    root = root->right;
                }
                if (root->right == NULL) {
                    printf("tdelete has 1 left child for %d\n", x);
                    root = root->left;
                }
                free(temp);
            }
        }
    }
    return root;
}

tree *tfind(tree *T, int x)
{
    if (T == NULL) {
        return NULL;
    }
    if (T->x <= x && x <= T->y) {
        return T;
    }
    if (T->x < x) {
        T = tfind(T->right, x);
    } else 
    if (T->x > x) {
        T = tfind(T->left, x);
    }
    return T;
}

void tshow(tree *T)
{
    if (T != NULL) {
        tshow(T->left);
        printf("[%02d - %02d]\n", T->x, T->y);
        tshow(T->right);
    }
}

#define MAX_DEPTH 12
int _print_t(tree *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
{
    char b[MAX_DEPTH];
    int width = 9;
    int left, right, i;
    if (!tree) return 0;
    sprintf(b, "(%03d:%03d)", tree->x, tree->y);
    left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
    if (depth && is_left) {
        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    } else if (depth && !is_left) {
        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    }
    return left + width + right;
}

int print_t(tree *tree)
{
    char s[MAX_DEPTH][255];
    int i;
    for (i = 0; i < MAX_DEPTH; i++)
        sprintf(s[i], "%80s", " ");
    _print_t(tree, 0, 0, 0, s);
    for (i = 0; i < MAX_DEPTH; i++)
        printf("%s\n", s[i]);
    printf("height %d\n", theight(tree));
    return 0;
}

int segtree_test()
{
    int x;
    tree *T = NULL, *t;
    T = tinsert(T, 4, 6);
    T = tinsert(T, 2, 4);
    T = tinsert(T, 8, 10);
    T = tinsert(T, 1, 3);
    tshow(T);
    print_t(T);
    if (t = tfind(T, x=5)) {
        printf("found : %d in [%d-%d]\n", x, t->x, t->y);
    } else {
        printf("%d not found\n", x);
    }
    if (t = tfind(T, x=7)) {
        printf("found : %d in [%d-%d]\n", x, t->x, t->y);
    } else {
        printf("%d not found\n", x);
    }
    return 0;
}
