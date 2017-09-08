#include <stdlib.h>
#include <stdio.h>

typedef int e_type;
#define neg_infinity (-10000)


/* START: fig12_14.txt */
typedef enum color_type { RED, BLACK } color_type;

typedef struct _rbnode {
    e_type  element;
    struct _rbnode *left;
    struct _rbnode *right;
    color_type    color;
} rbtree, position;

rbtree *make_empty( rbtree *T );
position *rb_find( e_type X, rbtree *T );
position *rb_findmin( rbtree *T );
position *rb_findmax( rbtree *T );
rbtree *rb_new( void );
rbtree *rb_insert( e_type X, rbtree *T );
rbtree *rb_remove( e_type X, rbtree *T );
e_type rb_retrieve( position *P );
void rb_print( rbtree *T );


static position *null_node = NULL;  /* Needs initialization */

/* Initialization procedure */
rbtree *rb_new( void )
{
    rbtree *T;

    if( null_node == NULL ) {
        null_node = malloc( sizeof( rbtree ) );
        if( null_node == NULL ) {
            printf("Out of space!!!\n");
        }
        null_node->left = null_node->right = null_node;
        null_node->color = BLACK;
        null_node->element = 12345;
    }

    /* Create the header node */
    T = malloc( sizeof( rbtree ) );
    if( T == NULL ) {
        printf("Out of space!!!\n");
    }
    T->element = neg_infinity;
    T->left = T->right = null_node;
    T->color = BLACK;

    return T;
}
/* END */

void Output( e_type element )
{
    printf( "%d\n", element );
}

/* START: fig12_13.txt */
/* Print the tree, watch out for null_node, */
/* and skip header */

static void do_print( rbtree *T )
{
    if( T != null_node ) {
        do_print( T->left );
        Output( T->element );
        do_print( T->right );
    }
}

void rb_print( rbtree *T )
{
    do_print( T->right );
}
/* END */

static rbtree *make_empty_rec( rbtree *T )
{
    if( T != null_node ) {
        make_empty_rec( T->left );
        make_empty_rec( T->right );
        free( T );
    }
    return null_node;
}

rbtree *make_empty( rbtree *T )
{
    T->right = make_empty_rec( T->right );
    return T;
}

position *rb_find( e_type X, rbtree *T )
{
    if( T == null_node ) {
        return null_node;
    }
    if( X < T->element ) {
        return rb_find( X, T->left );
    } else 
    if( X > T->element ) {
        return rb_find( X, T->right );
    } else {
        return T;
    }
}

position *rb_findmin( rbtree *T )
{
    T = T->right;
    while( T->left != null_node ) {
        T = T->left;
    }
     return T;
}

position *rb_findmax( rbtree *T )
{
    while( T->right != null_node ) {
        T = T->right;
    }
    return T;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

static position
*SingleRotateWithLeft( position *K2 )
{
    position *K1;
    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;
    return K1;  /* New root */
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

static position *SingleRotateWithRight( position *K1 )
{
    position *K2;
    K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;
    return K2;  /* New root */
}

/* START: fig12_15.txt */
/* Perform a rotation at node X */
/* (whose parent is passed as a parameter) */
/* The child is deduced by examining Item */

static position *Rotate( e_type Item, position *Parent )
{
    if( Item < Parent->element ) {
        return Parent->left = Item < Parent->left->element ?
            SingleRotateWithLeft( Parent->left ) :
            SingleRotateWithRight( Parent->left );
    } else {
        return Parent->right = Item < Parent->right->element ?
            SingleRotateWithLeft( Parent->right ) :
            SingleRotateWithRight( Parent->right );
    }
}
/* END */

/* START: fig12_16.txt */
static position *X, *P, *GP, *GGP;

static void handle_reorient( e_type Item, rbtree *T )
{
    X->color = RED;        /* Do the color flip */
    X->left->color = BLACK;
    X->right->color = BLACK;

    if( P->color == RED ) {  /* Have to rotate */
        GP->color = RED;
        if( (Item < GP->element) != (Item < P->element) ) {
            P = Rotate( Item, GP );  /* Start double rotate */
        }
        X = Rotate( Item, GGP );
        X->color = BLACK;
    }
    T->right->color = BLACK;  /* Make root BLACK */
}

rbtree *rb_insert( e_type Item, rbtree *T )
{
    X = P = GP = T;
    null_node->element = Item;
    while( X->element != Item ) { /* Descend down the tree */
        GGP = GP; GP = P; P = X;
        if( Item < X->element ) {
            X = X->left;
        } else {
            X = X->right;
        }
        if( X->left->color == RED && X->right->color == RED ) {
            handle_reorient( Item, T );
        }
    }
    if( X != null_node ) {
        return null_node;  /* Duplicate */
    }
    X = malloc( sizeof( rbtree ) );
    if( X == NULL ) {
        printf("Out of space!!!\n");
    }
    X->element = Item;
    X->left = X->right = null_node;
    if( Item < P->element ) { /* Attach to its parent */
        P->left = X;
    } else {
        P->right = X;
    }
    handle_reorient( Item, T ); /* Color it red; maybe rotate */
    return T;
}
/* END */

rbtree *rb_remove( e_type Item, rbtree *T )
{
    printf( "Remove is unimplemented\n" );
    if( Item ) {
        return T;
    }
    return T;
}

e_type rb_retrieve( position *P )
{
    return P->element;
}

int rb_depth(rbtree *T)
{
    int dL=0, dR=0, retval=0;
    rbtree *pT = T;

    if (T == NULL) return 0;

    pT = T;
    while (pT->left != null_node) {
        dL++;
        pT = pT->left;
    }
    pT = T;
    while (pT->right != null_node) {
        dR++;
        pT = pT->right;
    }
    
    printf("dL = %d, dR = %d\n", dL, dR);
    retval = (dL >= dR) ? dL : dR;
    return retval;

}

int main(int argc, char *argv[])
{
    int ret = 0, i;
    rbtree *rbtree;

    rbtree = rb_new();
    for (i = 0; i < 16; i++) {
        rbtree = rb_insert(i, rbtree);
    }
    printf("depth = %d\n", rb_depth(rbtree));
    printf("min   = "); Output(rb_findmin(rbtree)->element);
    printf("max   = "); Output(rb_findmax(rbtree)->element);
    rb_print(rbtree);
    
    return ret;
}

