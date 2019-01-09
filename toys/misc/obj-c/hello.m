/*
 * To compile objective-c on the command line:
 *
 * gcc -framework Foundation objc-gcc.m
 *
 * You may have to link with -lobjc or other libs,
 * as required.
 */

#import <Foundation/Foundation.h>

struct node {
    int id;
    char *key;
    int value;
    struct node *left;
    struct node *right;
} node;

void traverse(struct node *tree)
{
    if (tree == NULL) return;
    if (tree->left) traverse(tree->left);
    printf("%s %d\n", tree->key, tree->value);
    if (tree->right) traverse(tree->right);
}

int main(int argc, char** argv)
{
  NSLog(@"Hello, world");
  struct node *root = (struct node *) malloc(sizeof(struct node));
  root->key = strdup("dude");
  root->value = 42;
  root->left = root->right = NULL;
  traverse(root);
}
