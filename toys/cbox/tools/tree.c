#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

//#define dprint printf
#define dprint(...)
#define MAX(a,b) (((a)>(b))?(a):(b))


#define SIZE_RING 32
#define SIZE_STAK 32
typedef tree* e_v;
#include "ring.inc"
#include "stak.inc"

tree *new(int val) {
    tree *t = (tree *) malloc(sizeof(tree));
    t->left = t->right = NULL;
    t->val = val;
    t->height = 0;
    dprint("creating new node..%d\n", t->val);
    return t;
}

int theight(tree *root)
{
   if(root == NULL)
       return 0;
   return 1+MAX(theight(root->left), theight(root->right));
}

tree *max_node(tree *root) 
{
    tree *t = root;
    if (t == NULL) return NULL;
    while (t->right) t = t->right;
    dprint("max node..%d\n", t->val);
    return t;
}

tree *min_node(tree *root) 
{
    tree *t = root;
    if (t == NULL) return NULL;
    while (t->left) t = t->left;
    dprint("min node..%d\n", t->val);
    return t;
}

tree *avl_single_left(tree *root)
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

tree *avl_single_right(tree *root)
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

tree *avl_double_left(tree *root)
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

tree *avl_double_right(tree *root)
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

tree *insert_bal(tree *root, int val)
{
    tree *t = root;
    if (t == NULL) {
        t = new(val);
        return t;
    } else
    if (val < t->val) {
        t->left  = insert_bal(t->left, val);
        if( theight(t->left) - theight(t->right) == 2 ) {
            dprint("left: out of balance\n");
            if (val < t->left->val) {
                dprint("avl_single_left (LL): new val %d, left->val %d\n", val, t->left->val);
                t = avl_single_left(t);
            } else {
                dprint("avl_double_left (LR): new val %d, left->val %d\n", val, t->left->val);
                t = avl_double_left(t);
            }
        }
    } else if (val > t->val) {
        t->right = insert_bal(t->right, val);
        if( theight(t->right) - theight(t->left) == 2 ) {
            dprint("right: out of balance\n");
            if (val < t->right->val) {
                dprint("avl_single_right (RR): new val %d, right->val %d\n", val, t->right->val);
                t = avl_single_right(t);
            } else {
                dprint("avl_double_right (RL): new val %d, right->val %d\n", val, t->right->val);
                t = avl_double_right(t);
            }
        }
    }
    t->height = MAX( theight( t->left ), theight( t->right ) ) + 1;
    return t;
}

tree *insert(tree *root, int val)
{
    tree *t = root;
    if (t == NULL) {
        t = new(val);
        return t;
    } else
    if (val < t->val) {
        t->left  = insert(t->left, val);
    } else if (val > t->val) {
        t->right = insert(t->right, val);
    }
    t->height = MAX( theight( t->left ), theight( t->right ) ) + 1;
    return t;
}

tree *delete(tree *root, int val)
{
    tree *t = root;
    if (t == NULL) return t;
    if      (val < t->val) t->left = delete(t->left, val);
    else if (val > t->val) t->right = delete(t->right, val);
    else {
        tree *tmp = t;
        if (t->right && t->left) {
            //tree *min = min_node(t->right);
            //t->val = min->val;
            //t->right = delete(t->right, t->val);

            tree *max = max_node(t->left);
            t->val = max->val;
            t->left = delete(t->left, t->val);
        } else {
            if      (t->right == NULL) t = t->left;
            else if (t->left == NULL)  t = t->right;
            free(tmp);
        }
    }
    return t;
}


int deletemin(tree **pT)
{
    int min;
    if ((*pT)->left == NULL) {
        min = (*pT)->val;
        (*pT) = (*pT)->right;
        return min;
    } else {
        return deletemin(&((*pT)->left));
    }
}

tree *tfind(tree *root, int val)
{
    if (root == NULL) return NULL;
    if      (root->val < val) tfind(root->right, val);
    else if (root->val > val) tfind(root->left, val);
    else {
        printf("found it %d\n", root->val);
        return root;
    }
    return NULL;
}

void bfs(tree *root) 
{
    tree *n = root, *p;
    printf("bfs - enter\n");
    init_ring();
    rngput(n);
    while (!rngempty()) {
        n = rngget();
        printf("tree: %d\n", n->val);
        if (n->left)  rngput(n->left);
        if (n->right) rngput(n->right);
    }
}

void dfs(tree *root) 
{
    tree *n = root, *p;
    printf("dfs - enter\n");
    init_stak();
    stkpush(n);
    while (!stkempty()) {
        n = stkpop();
        printf("tree: %d\n", n->val);
        if (n->left)  stkpush(n->left);
        if (n->right) stkpush(n->right);
    }
}

void pre_order(tree *root)
{
    if (root) {
        printf("root->val: %d\n", root->val);
        pre_order(root->left);
        pre_order(root->right);
    }
}

void in_order(tree *root)
{
    if (root) {
        in_order(root->left);
        printf("root->val: %d\n", root->val);
        in_order(root->right);
    }
}

void post_order(tree *root)
{
    if (root) {
        post_order(root->left);
        post_order(root->right);
        printf("root->val: %d\n", root->val);
    }
}

void tshow(tree *root) 
{
    if (root) {
        tshow(root->left);
        printf("v: %d\n", root->val);
        tshow(root->right);
    }       
}

#define MAX_DEPTH 16
int _print_t(tree *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
{
    char b[MAX_DEPTH];
    int width = 5;
    int left, right, i;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->val);
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

int tree_test()
{
    tree *root = NULL, *t;
    int a[] = {13, 3, 4, 12, 14, 10, 5, 1, 8, 2, 7, 9, 11, 6, 18};
    int i, sz = sizeof(a) / sizeof(a[0]);
    for (i = 0; i < sz; ++i) {
        //root = insert(root, a[i]);
        root = insert_bal(root, a[i]);
    }
    //printf("pre order\n");
    //pre_order(root);
    //printf("in order\n");
    //in_order(root);
    //printf("post order\n");
    //post_order(root);
    //return 0;
    print_t(root);
    printf("height = %d\n", theight(root));
    bfs(root);
    //dfs(root);
    //return 0;

    //root = insert(root, a[0]);
    //root = insert(root, a[1]);
    //root = insert(root, a[2]);
    //root = insert(root, a[3]);
    //print_t(root);
    //return 0;
    //printf("height = %d\n", theight(root));
    //return 0;
    //printf("\n");
    //tshow(root);
    for (i = 0; i < sz; ++i) {
        root = delete(root, a[i]);
        printf("show..\n");
        print_t(root);
        //tshow(root);
        printf("\n");
    }
    for (i = 0; i < sz; ++i) {
        t = tfind(root, a[i]);
        if (t) printf("found (%d)\n", t->val);
    }
    //tshow(root);
    return 0;
}

