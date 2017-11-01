
// nodevalue is defined in the schema
// it is the data layout structure
#include "schema.h"

/* T defines minimum number of children in non-root nodes
 * 2*T is maximum number of children in all nodes
 * 2*T-1 is maximum number of keys in all nodes */
#define T 3

typedef char * nodekey;


/* B-tree node structure */
typedef struct s_tnode {
	nodekey keys[2*T-1]; /* keys */
	nodevalue * values[2*T-1]; /* values */
	unsigned int nkeys; /* number of keys, < 2*T */

	struct s_tnode * parent; /* pointer to parent */
	struct s_tnode * children[2*T]; /* pointers to children */
} * p_tnode;


