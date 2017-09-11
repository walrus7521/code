#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool less(int a, int b)
{
    //printf("less(%d, %d)\n", a, b);
    if (a < b) return true;
    //if (a > b) return  1;
    return false;
}

  
struct node {
    struct node *parent, *left, *right;
    int key;
};

unsigned long p_size = 0;
struct node *root = NULL;

#define MAX_DEPTH 16
int _print_t(struct node *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
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

int print_t(struct node *tree)
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

void left_rotate( struct node *x ) {
    struct node *y = x->right;
    if(y) {
      x->right = y->left;
      if( y->left ) y->left->parent = x;
      y->parent = x->parent;
    }
    
    if( !x->parent ) root = y;
    else if( x == x->parent->left ) x->parent->left = y;
    else x->parent->right = y;
    if(y) y->left = x;
    x->parent = y;
}
  
void right_rotate( struct node *x ) {
    struct node *y = x->left;
    if(y) {
      x->left = y->right;
      if( y->right ) y->right->parent = x;
      y->parent = x->parent;
    }
    if( !x->parent ) root = y;
    else if( x == x->parent->left ) x->parent->left = y;
    else x->parent->right = y;
    if(y) y->right = x;
    x->parent = y;
}
  
void splay( struct node *x ) {
    while( x->parent ) {
      if( !x->parent->parent ) {
        if( x->parent->left == x ) right_rotate( x->parent );
        else left_rotate( x->parent );
      } else if( x->parent->left == x && x->parent->parent->left == x->parent ) {
        right_rotate( x->parent->parent );
        right_rotate( x->parent );
      } else if( x->parent->right == x && x->parent->parent->right == x->parent ) {
        left_rotate( x->parent->parent );
        left_rotate( x->parent );
      } else if( x->parent->left == x && x->parent->parent->right == x->parent ) {
        right_rotate( x->parent );
        left_rotate( x->parent );
      } else {
        left_rotate( x->parent );
        right_rotate( x->parent );
      }
    }
}
  
void replace( struct node *u, struct node *v ) {
    if( !u->parent ) root = v;
    else if( u == u->parent->left ) u->parent->left = v;
    else u->parent->right = v;
    if( v ) v->parent = u->parent;
}
  
struct node* subtree_minimum( struct node *u ) {
    while( u->left ) u = u->left;
    return u;
}
  
struct node* subtree_maximum( struct node *u ) {
    while( u->right ) u = u->right;
    return u;
}

void insert( const int key ) {
    struct node *z = root;
    struct node *p = NULL;
    
    while( z ) {
      p = z;
      if( less( z->key, key ) ) z = z->right;
      else z = z->left;
    }
    
    z = (struct node *) malloc(sizeof(struct node));
    z->left = z->right = z->parent = NULL;    
    z->key = key;
    z->parent = p;
    
    if( !p ) root = z;
    else if( less( p->key, z->key ) ) p->right = z;
    else p->left = z;
    
    splay( z );
    p_size++;
}
  
struct node* find( const int key ) {
    struct node *z = root;
    while( NULL != z ) {
      if( less( z->key, key ) ) z = z->right;
      else if( less( key, z->key ) ) z = z->left;
      else return z;
    }
    return NULL;
}
        
void erase( const int key ) {
    struct node *z = find( key );
    if( !z ) return;
    
    splay( z );
    
    if( !z->left ) replace( z, z->right );
    else if( !z->right ) replace( z, z->left );
    else {
      struct node *y = subtree_minimum( z->right );
      if( y->parent != z ) {
        replace( y, y->right );
        y->right = z->right;
        y->right->parent = y;
      }
      replace( z, y );
      y->left = z->left;
      y->left->parent = y;
    }
    
    free(z);
    p_size--;
}

/* //the alternative implementation
    void erase( const T &key) {
        node *z = find( key );
        if( !z ) return;
        
        splay( z );
        
        node *s = z->left;
        node *t = z->right;
        delete z;
        
        node *sMax = NULL;
        if(s) {
            s->parent = NULL;
            sMax = subtree_maximum(s);
            splay(sMax);
            root = sMax;
        }
        if(t) {
            if(s)
                sMax->right = t;
            else
                root = t;
            t->parent = sMax;
        }
        
        p_size--;
    }
*/
  
const int minimum() { return subtree_minimum( root )->key; }
const int maximum() { return subtree_maximum( root )->key; }
  
bool empty() { return root == NULL; }
unsigned long size() { return p_size; }

int main()
{
    root = (struct node *) malloc(sizeof(struct node));
    root->key = 999;
    root->left = root->right = root->parent = NULL;
    int a[] = {13, 3, 4, 12, 14, 10, 5, 1, 8, 2, 7, 9, 11, 6, 18};
    int i, sz = sizeof(a) / sizeof(a[0]);
    for (i = 0; i < sz; ++i) {
        insert(a[i]);
    }
    print_t(root);
    while (root) {
        int max = maximum();
        printf("max: %d\n", max);
        erase(max);
    }
}

