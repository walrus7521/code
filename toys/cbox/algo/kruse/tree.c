#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int nodes = 0;
void tree_inorder(tree_t *root)
{
    if (root) {
        tree_inorder(root->left);
        printf("%d\n", root->key);
        tree_inorder(root->right);
    }
}

void tree_postorder(tree_t *root)
{
    if (root) {
        tree_postorder(root->left);
        tree_postorder(root->right);
        printf("%d\n", root->key);
    }
}

#define MAX_DEPTH 6
int _print_t(tree_t *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
{
    char b[MAX_DEPTH];
    int width = 5;
    int left, right, i;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->key);
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

int print_t(tree_t *tree)
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


void bfs(tree_t *root)
{
    tree_t *queue[16];
    int head=0, tail=0;
    queue[tail++] = root;
    root->level = 0;
    while (head != tail) {
        tree_t *t = queue[head++];
        printf("%02d %02d\n", t->key, t->level);
        if (t->left) {
            queue[tail++] = t->left;
            t->left->level = t->level+1;
        }
        if (t->right) {
            queue[tail++] = t->right;
            t->right->level = t->level+1;
        }
    }
}

void dfs(tree_t *root)
{
    tree_t *stack[16];
    int head=0;
    root->level = 0;
    tree_t *t = root;
    nodes--;
    stack[head++] = root;
    while (nodes > 0) {
        if (t->left) {
            stack[head++] = t->left;
            t->left->level = t->level+1;
            nodes--;
        }
        if (t->right) {
            stack[head++] = t->right;
            t->right->level = t->level+1;
            nodes--;
        }
    }
    while (head >= 0) {
        tree_t *t = stack[--head];
        printf("%02d\n", t->key);

    }
}

int tree_insert(tree_t **root, tree_t *newnode)
{
    if (*root == NULL) {
        *root = newnode;
    } else {
        tree_t *tmpnode = *root, *prevnode;
        while (tmpnode) {
            prevnode = tmpnode;
            if (newnode->key < tmpnode->key) {
                tmpnode = tmpnode->left;
            } else {
                tmpnode = tmpnode->right;
            }
        }
        if (prevnode && prevnode->key == newnode->key) {
            return -1;
        }
        if (newnode->key < prevnode->key) {
            prevnode->left = newnode;
        } else {
            prevnode->right = newnode;
        }
        
     }
    return 0;
}

int delmax(tree_t *root) 
{
    tree_t *t = root, *prev;
    if (t == NULL) return -1;
    while (t->right) {
        prev = t;
        t = t->right;
    }
    printf("delmax: %d\n", t->key);
    prev->right = NULL;
    return t->key;
}

int delmin(tree_t *root) 
{
    tree_t *t = root, *prev;
    if (t == NULL) return -1;
    while (t->left) {
        prev = t;
        t = t->left;
    }
    printf("delmin: %d\n", t->key);
    prev->left = NULL;
    return t->key;
}

int *tree_delete(tree_t **root, int key)
{
    key_t *delkey;
    tree_t *tmpnode = NULL, *parent;
    if (*root == NULL) {
        printf("null root del\n");
        return NULL;
    } else if ((*root)->key == key) {
        tmpnode = *root;
        delkey = &tmpnode->key;
        if (tmpnode->left && tmpnode->right) {
            int max = delmax(tmpnode->left);
            printf("root key del go max left: %d\n", max);
            tree_t *newroot = tree_create(max);
            newroot->right = tmpnode->right;
            newroot->left = tmpnode->left;
            *root = newroot;
        } else
        if (tmpnode->left) {
            printf("root key del go left: %d\n", tmpnode->key);
            *root = tmpnode->left;
        } else
        if (tmpnode->right) {
            printf("root key del go right: %d\n", tmpnode->key);
            *root = tmpnode->right;
        }
        return delkey;
    }
    tmpnode = *root;        
    parent = tmpnode;
    while (tmpnode) {
        printf("chk del: %d => %d\n", tmpnode->key, key);
        if (key < tmpnode->key) {
            parent = tmpnode;
            tmpnode = tmpnode->left;
        } else
        if (key > tmpnode->key) {
            parent = tmpnode;
            tmpnode = tmpnode->right;
        } else
        if (tmpnode->key == key) {
            printf("del found: %d, parent: %d\n", tmpnode->key, parent->key);
            delkey = &tmpnode->key;
            if (tmpnode->left && tmpnode->right) {
                if (key < parent->key) {
                    // left
                    printf("get max\n");
                    int max = delmax(tmpnode->left);
                    printf("max: %d\n", max);
                    tree_t *newroot = tree_create(max);
                    newroot->right = tmpnode->right;
                    newroot->left = tmpnode->left;
                    parent->left = newroot;
                    printf("non null root key del go max left: %d\n", max);
                } else {
                    // right
                    printf("get min\n");
                    int min = delmin(tmpnode->left);
                    printf("min: %d\n", min);
                    tree_t *newroot = tree_create(min);
                    newroot->right = tmpnode->right;
                    newroot->left = tmpnode->left;
                    parent->right = newroot;
                    printf("non null root key del go min right: %d\n", min);
                }
            } else
            if (tmpnode->left) {
                printf("non null root key del go left: %d\n", tmpnode->key);
                parent->left = tmpnode->left;
            } else
            if (tmpnode->right) {
                printf("non null root key del go right: %d\n", tmpnode->key);
                parent->right = tmpnode->right;
            } else {
                // no kids
                if (key < parent->key) {
                    // left
                    parent->left = NULL;
                } else {
                    // right
                    parent->right = NULL;
                }
            }

            return delkey;
        }
    }
    return NULL;
}


int *tree_find(tree_t *root, int key)
{
    if (root == NULL) {
        return NULL;
    } else {
        tree_t *tmpnode = root;
        while (tmpnode) {
            if (tmpnode->key == key) {
                return &tmpnode->key;
            }
            if (key < tmpnode->key) {
                tmpnode = tmpnode->left;
            } else {
                tmpnode = tmpnode->right;
            }
        }
    }
    return NULL;
}



tree_t *tree_create(key_t key)
{
    tree_t *newnode = (tree_t *) malloc(sizeof(tree_t));
    newnode->key = key;
    newnode->left = newnode->right = NULL;
    return newnode;
}

int main()
{
    //int a[] = {3,4,5,2,1};
    int a[] = {10, 5, 4, 3, 7, 16, 13, 11, 20, 18, 17, 19, 30};
    int len = sizeof(a) / sizeof(a[0]);
    int i;
    tree_t *root = NULL;
    for (i = 0; i < len; i++) {
        tree_t *newnode = tree_create(a[i]);
        tree_insert(&root, newnode);
    }
#if 0
    //tree_inorder(root);
    //tree_postorder(root);
    bfs(root);
    //dfs(root);
    //print_t(root);
    for (i = 0; i < len; i++) {
        int *key = tree_find(root, a[i]);
        if (key) {
            printf("found %d\n", *key);
        } else {
            printf("%d not found\n", a[i]);
        }
    }
#endif
#if 0
    i = 0;
    print_t(root);
    printf("delete: %d\n", 16);
    int *key = tree_delete(&root, 16);
    if (key) {
        printf("deleted %d\n", *key);
    } else {
        printf("%d not deleted\n", 16);
    }
    print_t(root);
#endif
#if 1
    for (i = 0; i < len; i++) {
        print_t(root);
        printf("delete: %d\n", a[i]);
        int *key = tree_delete(&root, a[i]);
        if (key) {
            printf("deleted %d\n", *key);
        } else {
            printf("%d not deleted\n", a[i]);
        }
    }
    print_t(root);
#endif
}




