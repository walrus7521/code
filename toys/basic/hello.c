// Program Name:
// Author(s):
// Description:

/* Keep these headers */
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Other available headers */
// including stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h

/* Available libraries */
// including lib/ce/graphc.h, lib/ce/fileioc.h, and lib/ce/keypadc.h
// Sample: #include <lib/ce/graphc.h>

/* Put your function prototypes here */

/* Put all your globals here. */

/* Put all your code here */

typedef struct list {
    struct list *next;
    int val;
} list;

void main() {
    // Main program code goes here
    list *head = malloc(sizeof(list));
    head->val = 42;
    //printf("head: %d\n", head->val);

    boot_DebugPrintf("dude\n");

    
}

/* Other functions */

