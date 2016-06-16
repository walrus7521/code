#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ABS(x) ((x)<0 ? -(x) : (x))

typedef struct _tree {
    struct _tree *left, *right;
    int value;
    int height;
} tree;

typedef tree* e_v;
#include "slist.h"

int theight(tree *root){
   if(root == NULL)
       return 0;
   return 1+MAX(theight(root->left), theight(root->right));
}

tree *avl_single_left( tree *root )
/*
 *      d           c
 *     /           / \
 *    c     -->   a   d
 *   / \             /
 *  a   b           b
 */
{
    tree *new_root;
    new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    root->height = MAX(theight(root->left), theight(root->right)) + 1;
    new_root->height = MAX(theight(new_root->left), root->height) + 1;
    return new_root;
}

tree *avl_single_right( tree *root )
/*
 *    c           a
 *   / \           \
 *  a   d   <--     c
 *   \             / \
 *    b           b   d
 */
{
    tree *new_root;
    new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    root->height = MAX(theight(root->left), theight(root->right)) + 1;
    new_root->height = MAX(theight(new_root->right), root->height) + 1;
    return new_root;
}

tree *avl_double_left( tree *root )
/*
 *         c          c -->         b
 *        /          /             / \
 *       a -->      b             a   c
 *        \        /
 *         b      a
 */
{
    root->left = avl_single_right( root->left );
    return avl_single_left( root );
}

tree *avl_double_right( tree *root )
/*
 *     a          a -->            b
 *      \          \              / \
 *       c -->      b            a   c
 *      /            \
 *     b              c
 */
{
    root->right = avl_single_left( root->right );
    return avl_single_right( root );
}

tree *avl_insert( tree *T, int value )
{
    if( T == NULL ) {
        /* Create and return a one-node tree */
        T = malloc( sizeof( tree *) );
        T->value = value; T->height = 0;
        T->left = T->right = NULL;
    } else
    if( value < T->value ) {
        T->left = avl_insert( T->left, value );
        if( theight( T->left ) - theight( T->right ) == 2 ) {
            if( value < T->left->value )
                T = avl_single_left( T );
            else
                T = avl_double_left( T );
        }
    } else
    if( value > T->value ) {
        T->right = avl_insert( T->right, value );
        if( theight( T->right ) - theight( T->left ) == 2 ) {
            if( value > T->right->value )
                T = avl_single_right( T );
            else
                T = avl_double_right( T );
        }
    }
    /* Else value is in the tree already; we'll do nothing */
    T->height = MAX( theight( T->left ), theight( T->right ) ) + 1;
    return T;
}

tree *tinsert(tree *root, int data)
{
    if (root == NULL) {
        root = (tree *) malloc(sizeof(tree));
        root->value = data;
        root->left = root->right = NULL;
    } else
    if (data < root->value) {
        root->left  = tinsert(root->left, data);
        if ((theight(root->left) - theight(root->right)) == 2) {
            printf("out of balance: %d\n", data);
            if (data < root->left->value) {
                printf("avl_single_left\n");
            } else {
                printf("avl_double_left\n");
            }
        }
    } else 
    if (data > root->value) {
        root->right = tinsert(root->right, data);
        if ((theight(root->left) - theight(root->right)) == 2) {
            printf("out of balance: %d\n", data);
            if (data < root->right->value) {
                printf("avl_single_right\n");
            } else {
                printf("avl_double_right\n");
            }
        }
    } else {
        printf("got a dup %d\n", data);
    }
    return root;
}

int deletemin(tree **pT)
{
    int min;
    if ((*pT)->left == NULL) {
        min = (*pT)->value;
        (*pT) = (*pT)->right;
        return min;
    } else {
        return deletemin(&((*pT)->left));
    }
}

tree *tfindmin_nr(tree *root)
{
    if (root == NULL)
        return NULL;
    while (root->left) {
        root = root->left;
    }
    return root;
}

tree *tfindmax_nr(tree *root)
{
    if (root == NULL)
        return NULL;
    while (root->right) {
        root = root->right;
    }
    return root;
}

tree *tfindmax(tree *T) {
    tree *t = T;
    while (t->right) {
        t = t->right;
    }
    printf("tfindmax returning %d\n", t->value);
    return t;
}

tree *tfindmin(tree *T) {
    tree *t = T;
    while (t->left) {
        t = t->left;
    }
    return t;
}

tree *tdelete(tree *root, int value)
{
    tree *temp;
    printf("tdelete - enter (%d)\n", value);
    if (root != NULL) {
        if (value < root->value) {
            root->left = tdelete(root->left, value);
        } else if (value > root->value) {
            root->right = tdelete(root->right, value);            
        } else {
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
    link *l = NULL;
    list *h = slist_init();
    printf("tlevel..\n");
    slist_push_back(h, T);
    while (!slist_empty(h)) {
        l = slist_pop_front(h);
        t = l->value;
        printf("t: %d \n", t->value);
        if (t->left) slist_push_back(h, t->left);
        if (t->right) slist_push_back(h, t->right);
    }
}

tree *tfind(tree *T, int value)
{
    if (T == NULL) {
        return NULL;
    }
    if (T->value < value) {
        tfind(T->right, value);
    } else 
    if (T->value > value) {
        tfind(T->left, value);
    } else {
        printf("found it %d\n", T->value);
        return T;
    }
    return NULL;
}

tree *tfind_nr(tree *T, int value)
{
    if (T == NULL) {
        return NULL;
    }
    while (T) {
        if (value == T->value) 
            return T;
        else if (value > T->value)
            T = T->right;
        else T = T->left;

    }
    return NULL;
}

void tlevel_show(tree *root) 
{
    tree *t = NULL;
    link *l = NULL;
    list *h = slist_init();
    int nodes_in_curr_level = 1;
    int nodes_in_next_level = 0;
    int level_no = 0;
    if (!root) return;
    slist_push_back(h, root);
    while (!slist_empty(h)) {
        l = slist_pop_front(h);
        t = l->value;
        nodes_in_curr_level--;
        if (t) {
            printf(" %d[l=%d][h=%d] ", t->value, level_no, t->height);
            slist_push_back(h, t->left);
            slist_push_back(h, t->right);
            nodes_in_next_level += 2;
        }
        if (nodes_in_curr_level == 0) {
            printf("\n");
            level_no++;
            nodes_in_curr_level = nodes_in_next_level;
            nodes_in_next_level = 0;
        }
    }
}

void tshow(tree *T, void (dump)(void *))
{
    if (T != NULL) {
        tshow(T->left, dump);
        //printf("T->value %d\n", T->value);
        dump((void *) T);
        tshow(T->right, dump);
    }
}

#define MAX_DEPTH 8
int _print_t(tree *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
{
    char b[MAX_DEPTH];
    int width = 5;
    int left, right, i;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->value);
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
    return 0;
}

void tdump(void *t)
{
    tree *tr = (tree *) t;
    printf("tree->value = %d\n", tr->value);
}

int tree_test2()
{
    tree *T = NULL, *t;
#if 1
    T = avl_insert(T, 4);
    T = avl_insert(T, 2);
    T = avl_insert(T, 8);
    T = avl_insert(T, 1);
    T = avl_insert(T, 5);
    T = avl_insert(T, 7);
    T = avl_insert(T, 6);
    T = avl_insert(T, 10);
    T = avl_insert(T, 23);
    T = avl_insert(T, 14);
    T = avl_insert(T, 11);
    T = avl_insert(T, 9);
    T = avl_insert(T, 12);
#endif
#if 0
    //
    T = tinsert(T, 4);
    T = tinsert(T, 2);
    T = tinsert(T, 8);
    T = tinsert(T, 1);
    T = tinsert(T, 5);
    T = tinsert(T, 7);
    T = tinsert(T, 6);
#endif
    tlevel_show(T);
    T->height = theight(T);
    print_t(T);
    printf("tree height %d\n", T->height);
    return 0;
    t = tfindmin(T);
    printf("min = %d\n", t->value);
    t = tfindmax(T);
    printf("max = %d\n", t->value);
    printf("dump tree...\n");
    tshow(T, dump);
    printf("do level traverse...\n");
    tlevel_show(T);
    printf("delete 4\n");
    tdelete(T, 4);
    tlevel_show(T);
    //tshow(T, dump);
    //printf("delete 2\n");
    //tdelete(T, 2);
    //tshow(T, dump);
    //tlevel_show(T);
    //T = tfind_nr(T, 3);
    //T = tfindmin_nr(T);
    T = tfindmax_nr(T);
    if (T) {
        printf("found max tree node: %d\n", T->value);
    } else {
        printf("max tree node not found\n");
    }
    return 0;
}

int tree_test()
{
    tree *T = NULL;
    T = tinsert(T, 4);
    T = tinsert(T, 2);
    T = tinsert(T, 8);
    T = tinsert(T, 1);
    T = tinsert(T, 5);
    T = tinsert(T, 7);
    T = tinsert(T, 6);
    tlevel(T);
    T->height = theight(T);
    tshow(T, tdump);
    print_t(T);
    printf("tree height %d\n", T->height);
    return 0;
}
