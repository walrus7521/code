#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct _tree {
    struct _tree *left, *right;
    int val;
    int height;
} tree;

tree *new(int val) {
    tree *t = (tree *) malloc(sizeof(tree));
    t->left = t->right = NULL;
    t->val = val;
    t->height = 0;
    printf("creating new node..%d\n", t->val);
    return t;
}

int theight(tree *root){
   if(root == NULL)
       return 0;
   return 1+MAX(theight(root->left), theight(root->right));
}

tree *max_node(tree *root) {
    tree *t = root;
    if (t == NULL) return NULL;
    while (t->right) t = t->right;
    return t;
}

tree *min_node(tree *root) {
    tree *t = root;
    if (t == NULL) return NULL;
    while (t->left) t = t->left;
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
    }
    else if (val > t->val) {
        t->right = insert(t->right, val);
    }
    t->height = MAX( theight( t->left ), theight( t->right ) ) + 1;
    return t;
}

tree *delete(tree *root, int val)
{
    tree *t = root;
    if (t == NULL) {
        return t;
    }
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
            if (t->right == NULL) t = t->left;
            else if (t->left == NULL) t = t->right;
            free(tmp);
        }
    }
    return t;
}

tree *find(tree *root, int val)
{
    if (root == NULL) return NULL;
    if      (root->val < val) find(root->right, val);
    else if (root->val > val) find(root->left, val);
    else {
        printf("found it %d\n", root->val);
        return root;
    }
    return NULL;
}

void pre_order(tree *root) {
    if (root) {
        printf("v: %d\n", root->val);
        pre_order(root->left);
        pre_order(root->right);
    }       
}

void in_order(tree *root) {
    if (root) {
        in_order(root->left);
        printf("v: %d\n", root->val);
        in_order(root->right);
    }       
}

void post_order(tree *root) {
    if (root) {
        post_order(root->left);
        post_order(root->right);
        printf("v: %d\n", root->val);
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

int main()
{
    tree *root = NULL, *t;
    //int a[] = {13, 3, 4, 12, 14, 10, 5, 1, 8, 2, 7, 9, 11, 6, 18};
    int a[] = {64,31,92,15,36,68,104,14,16,34,38,66,70,96,110}; // perfect balanced 2^3
    int i, sz = sizeof(a) / sizeof(a[0]);
    for (i = 0; i < sz; ++i) {
        root = insert(root, a[i]);
    }
    print_t(root);
    //in_order(root);
    printf("\npre-order...\n");
    pre_order(root);
    printf("\nin-order...\n");
    in_order(root);
    printf("\npost-order...\n");
    post_order(root);
    //bfs(root);
    //dfs(root);
    return 0;
    //test_list();
    //return 0;

    root = insert(root, a[0]);
    root = insert(root, a[1]);
    root = insert(root, a[2]);
    //root = insert(root, a[3]);
    print_t(root);
    return 0;
    printf("height = %d\n", theight(root));
    //return 0;
    //printf("\n");
    //for (i = 0; i < sz; ++i) {
    //    root = delete(root, a[i]);
    //    printf("in_order..\n");
    //    in_order(root);
    //    printf("\n");
    //}
    for (i = 0; i < sz; ++i) {
        t = find(root, a[i]);
        if (t) printf("found (%d)\n", t->val);
    }
    //in_order(root);
    return 0;
}
