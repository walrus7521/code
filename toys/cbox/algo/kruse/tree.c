#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// add RB tree

#if 0
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
#endif

void tree_left_rotate(tree_t *t, node_t *x)
{
    printf("LeftRotate\n");
    node_t *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NULL) {
        t->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

void tree_right_rotate(tree_t *t, node_t *y)
{
    printf("RightRotate");
    node_t *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == NULL) {
        t->root = x;
    } else if (y == y->p->right) {
        y->p->right = x;
    } else {
        y->p->left = x;
    }
    x->right = y;
    y->p = x;
}

void transplant(tree_t *t, node_t *u, node_t *v)
{
    printf("transplant: %d, %d\n", u->key, v->key);
    if (u->p == NULL) {
        t->root = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    if (v != NULL) {
        v->p = u->p;
    }
}

void tree_rb_fixup(tree_t *t, node_t *x)
{
    /*
    for x != t.root && x.color == BLACK {
        if x == x.p.left {
            w := x.p.right
            if w.color == RED {
                w.color = BLACK
                x.p.color = RED
                t.LeftRotate(x.p)
                w = x.p.right
            }
            if w.left.color == BLACK && w.right.color == BLACK {
                w.color = RED
                x = x.p
            } else if w.right.color == BLACK {
                w.left.color = BLACK
                w.color = RED
                t.RightRotate(w)
                x = x.p.right
            }
            w.color = BLACK
            x.p.color = BLACK
            t.LeftRotate(x.p)
        } else {
            w := x.p.left
            if w.color == RED {
                w.color = BLACK
                x.p.color = RED
                t.RightRotate(x.p)
                w = x.p.left
            }
            if w.right.color == BLACK && w.left.color == BLACK {
                w.color = RED
                x = x.p
            } else if w.left.color == BLACK {
                w.right.color = BLACK
                w.color = RED
                t.LeftRotate(w)
                x = x.p.left
            }
            w.color = BLACK
            x.p.color = BLACK
            t.RightRotate(x.p)
        }
    }
    t.root.color = BLACK
    */
}

void tree_rb_insert(tree_t *t, node_t *z)
{
    /*
    var y *Node = nil
    x := t.root
    for x != nil {
        y = x
        if z.key < x.key {
            x = x.left
        } else {
            x = x.right
        }
    }
    z.p = y
    if y == nil {
        t.root = z
    } else {
        if z.key < y.key {
            y.left = z
        } else {
            y.right = z
        }
    }
    z.left = nil
    z.right = nil
    z.color = RED
    t.RBInsertFixup(z)
    */
}

void tree_insert(tree_t *t, node_t *z)
{
    printf("insert: %d\n", z->key);
    node_t *y = NULL;
    node_t *x = t->root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == NULL) {
        t->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

node_t *tree_min(tree_t *t)
{
    if (t->root == NULL) {
        return NULL;
    }
    node_t *n = t->root;
    node_t *p = NULL;
    while (n != NULL) {
        p = n;
        n = n->left;
    }
    return p;
}

void tree_delete(tree_t *t, node_t *z)
{
    printf("Delete: %d\n", z->key);
    if (z->left == NULL) {
        transplant(t, z, z->right);
    } else if (z->right == NULL) {
        transplant(t, z, z->left);
    } else {
        node_t *y = tree_min(t);
        if (y->p != z) {
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(t, z, y);
        y->left = z->left;
        y->left->p = y;
    }
}


node_t *find(tree_t *t, int key)
{
    node_t *n = t->root;
    while (n != NULL && n->key != key) {
        if (key < n->key) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    return n;
}

node_t *create_node(int key)
{
    node_t *n = (node_t *) malloc(sizeof(node_t));
    n->left = n->right = n->p = NULL;
    n->key = key;
    n->color = RED;
    return n;
}

int main()
{
    //int a[] = {3,4,5,2,1};
    int a[] = {10, 5, 4, 3, 7, 16, 13, 11, 20, 18, 17, 19, 30};
    int len = sizeof(a) / sizeof(a[0]);
    int i;
    tree_t *tree = (tree_t *) malloc(sizeof(tree_t));
    tree->root = NULL;
    for (i = 0; i < len; i++) {
        node_t *newnode = create_node(a[i]);
        tree_insert(tree, newnode);
    }
    print_t(tree);
    int key = 13;
    node_t *n = find(tree, key);
    if (n) {
        printf("found: %d\n", n->key);
        tree_delete(tree, n);
    } else {
        printf("key %d not found\n", key);
    }
    print_t(tree);

}




