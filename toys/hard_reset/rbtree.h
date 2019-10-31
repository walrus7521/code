#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#define neg_infinity (-10000)

typedef enum color_type { RED, BLACK } color_type;

typedef int e_type;
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
void rb_print( rbtree *T );

#endif // _RB_TREE_H_

