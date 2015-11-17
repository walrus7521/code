#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../toys/tree.h"

typedef struct {
    int balanced;
    int height;
} pair;

pair check_balanced(tree *root) {

    pair p, right_result, left_result;
    int is_balanced, height;

    if (root == NULL) {
        p.balanced = 1;
        p.height = -1;
        return p;
    }

    left_result = check_balanced(root->left);
    if (!left_result.balanced) {
        p.balanced = 0;
        p.height = 0;
        return p;
    }

    right_result = check_balanced(root->right);
    if (!right_result.balanced) {
        p.balanced = 0;
        p.height = 0;
        return p;
    }

    is_balanced = ABS(left_result.height - right_result.height) <= 1;
    height = MAX(left_result.height, right_result.height) + 1;
    p.balanced = is_balanced;
    p.height = height;
    return p;
}

pair is_balanced_binary_tree(tree *root) {
    return check_balanced(root);
}

void mydump(void *t)
{
    tree *tr = (tree *) t;
    printf("tree->value = %d\n", tr->value);
}

int main()
{
    tree *T = NULL, *t;
    pair p;
    T = tinsert(T, 4); T = tinsert(T, 2); T = tinsert(T, 8);
    T = tinsert(T, 1); T = tinsert(T, 5); 
    //T = tinsert(T, 7);
    //tlevel(T);
    //tshow(T);
    //tdelete(T, 4);
    //tshow(T);
    tshow(T, mydump);
    p = is_balanced_binary_tree(T);
    printf("check balanced: %d, height: %d\n", p.balanced, p.height);
    return 0;
}
