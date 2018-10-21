#ifndef DISPLAY_H
#define DISPLAY_H

#include "list.h"


#define E_NOOBJ 1
#define E_NOSPACE 2
#define E_DELETE 3
#define E_BADPARAM 4
#define E_NOMARK 5
#define E_CNT5

#define LINE 1
#define RECTANGLE 2
#define CIRCLE 3
#define MARK 4

typedef struct display_node {
    int type;
    int value_1, value_2, value_3, value_4;
} display_node;

list *newobject(void);
void endobject(void);
int line(int x1, int y1, int x2, int y2);
int rectangle(int x1, int y1, int x2, int y2);
int circle(int x, int y, int radius);
int mark(int value);
int editobject(list *object, int mark_value, int replaceflag);
char *display_error(int err_num);

#endif // DISPLAY_H
