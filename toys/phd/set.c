/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _tree {
    struct _tree *left, *right;
    int value;
} tree, set;

/* allows us to iterate a tree linearly and in sorted order
 */
typedef struct _iter {
    void *current, *stash;
    int done;
    int top;
    void **stack;
    struct _iter* (*begin)(struct _iter*, void*);
    struct _iter* (*next)(struct _iter*);
    int (*end)(struct _iter*);
    void (*push)(struct _iter*, void *);
    void *(*pop)(struct _iter*);
    int (*empty)(struct _iter*);
} __iter;

__iter *iter(__iter *it)
{
    while (!it->done) {
        if (it->current != NULL) {
            it->push(it, it->current);
            it->current = ((tree *) it->current)->left;
        } else {
            if (!it->empty(it)) {
                it->stash = it->current = it->pop(it);
                it->current = ((tree *) it->current)->right;
                goto done_iter;
            } else {
                it->done = 1;
                it->stash = NULL;
                goto done_iter;
            }
        }
    }
done_iter:
    return it;
}

void push(struct _iter *it, void *s) {
    it->stack[it->top++] = s;
}

void *pop(struct _iter *it) {
    void *T = it->stack[--it->top];
    return T;
}

int empty(struct _iter *it) {
    return (it->top == 0);
}

__iter* begin(__iter *it, void *s) {
    it->stash = it->current = s;
    it->done = 0;
    return iter(it);
}

__iter* next(__iter *it) {
    return iter(it);
}

int end(__iter *it) {
    return it->done;
}

__iter *new_iter(int depth) {
    __iter *iter = malloc(sizeof(__iter));
    iter->stack  = malloc(depth * sizeof(void*));
    iter->begin  = begin;
    iter->next   = next;
    iter->end    = end;
    iter->push   = push;
    iter->pop    = pop;
    iter->empty  = empty;
    return iter;
}

tree *tfindmax(tree *T) {
    tree *t = T;
    while (t->right) t = t->right;
    return t;
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

tree* tfind(tree ** tree, int val) {
    if (!(*tree)) {
        return NULL;
    }
    if (val == (*tree)->value) {
        return *tree;
    } else if (val < (*tree)->value) {
        tfind(&((*tree)->left), val);
    } else if (val > (*tree)->value){
        tfind(&((*tree)->right), val);
    }
    return *tree;
}

void tshow(tree *T)
{
    if (T != NULL) {
        tshow(T->left);
        printf("T->value %d\n", T->value);
        tshow(T->right);
    }
}

void iterate(set *s) {
    __iter *it = new_iter(1024);
    for (it = it->begin(it, s); !it->end(it); it = it->next(it)) {
        set *s = (set *) it->stash;
        printf("s->val: %d\n", s->value);
    }
}

void iterate2(set *s) {
    __iter *it = new_iter(1024);
    it = it->begin(it, s);
    while (!it->end(it)) {
        set *s = (set *) it->stash;
        printf("s->val: %d\n", s->value);
        it = it->next(it);
    }
}

set *set_add(set *s, int v) {
    return tinsert(s, v);
}

int set_is_in(set **s, int v) {
    set *s2 = tfind(s, v);
    if (s2 != NULL) {
        return 1;
    }
    return 0;
}

set *set_intersect(set *s1, set *s2) {
    set *isec = NULL;
    set *st1, *st2;
    __iter *it1 = new_iter(1024);
    __iter *it2 = new_iter(1024);
    it1 = it1->begin(it1, s1);
    it2 = it2->begin(it2, s2);
    while (!it1->end(it1) && !it2->end(it2)) {
        st1 = (set *) it1->stash;
        st2 = (set *) it2->stash;
        if (st1->value < st2->value) {
            it1 = it1->next(it1);
        } else
        if (st1->value > st2->value) {
            it2 = it2->next(it2);
        } else {
            isec = set_add(isec, st1->value);
            it1 = it1->next(it1);
            it2 = it2->next(it2);
        }
    }
    return isec;
}

set *set_union(set *s1, set *s2) {
    set *uni = NULL;
    set *st1, *st2;
    __iter *it1 = new_iter(1024);
    __iter *it2 = new_iter(1024);
    it1 = it1->begin(it1, s1);
    it2 = it2->begin(it2, s2);
    while (!it1->end(it1) && !it2->end(it2)) {
        st1 = (set *) it1->stash;
        st2 = (set *) it2->stash;
        if (st1->value < st2->value) {
            uni = set_add(uni, st1->value);
            it1 = it1->next(it1);
        } else
        if (st1->value > st2->value) {
            uni = set_add(uni, st2->value);
            it2 = it2->next(it2);
        } else {
            uni = set_add(uni, st1->value);
            it1 = it1->next(it1);
            it2 = it2->next(it2);
        }
    }
    if (!it1->end(it1)) {
        while (!it1->end(it1)) {
            st1 = (set *) it1->stash;
            uni = set_add(uni, st1->value);
            it1 = it1->next(it1);
        }
    } else 
    if (!it2->end(it2)) {
        while (!it2->end(it2)) {
            st2 = (set *) it2->stash;
            uni = set_add(uni, st2->value);
            it2 = it2->next(it2);
        }
    }
    return uni;
}

set *set_create(int *v, int n, set *s) {
    int i;
    for (i = 0; i < n; i++) {
        s = set_add(s, v[i]);
    }
    return s;
}

int main()
{
    set *s1 = NULL, *s2 = NULL, *isec = NULL, *uni = NULL;
    int v1[] = {12, 34, 23, 56, 45};
    int v2[] = {34, 56, 12, 78, 66, 101};
    s1 = set_create(v1, sizeof(v1)/sizeof(v1[0]), s1);
    s2 = set_create(v2, sizeof(v2)/sizeof(v2[0]), s2);
    printf("set 1\n");
    iterate(s1);
    printf("set 1\n");
    iterate(s2);
    if (set_is_in(&s1, 5)) printf("5 is in the set\n");
    isec= set_intersect(s1, s2);
    printf("intersection\n");
    iterate(isec);
    uni= set_union(s1, s2);
    printf("union\n");
    iterate(uni);
    return 0;
}

