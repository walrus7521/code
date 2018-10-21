#include "display.h"

static list *p_current_list;
static int edit_mode;
static int translate_x, translate_y;

// error handler
char *display_error(int err_num)
{
    static char *errors[E_CNT+1] = {
        "system error",
        "no object current open",
        "out of memory",
        "deletion failed",
        "invalid edit parameter",
        "mark not found"
    };

    if (err_num < 1 || err_num > E_CNT)
        err_num = 0;
    return errors[err_num];
}

display_node *allocate_display_node(int type, int v1, int v2, int v3, int v4)
{
    return NULL;
}

void free_display_node(display_node *p_node)
{
}

status draw_primitive(display_node *p_node)
{
    return OK;
}

list *newobject(void)
{
    edit_mode = EDIT_APPEND;
    p_current_list = (list *) malloc(sizeof(list));
    if (p_current_list)
        init_list(p_current_list);
    return p_current_list;
}

void endobject(void)
{
    edit_mode = EDIT_APPEND;
    p_current_list = NULL;
}

void display_init()
{
    p_current_list = NULL;
    edit_mode = EDIT_APPEND;
    translate_x = translate_y = 0;
}

status display_append(list *p_current_list, int type, int v1, int v2, int v3, int v4)
{
    return OK;
}

static int _primitive(int type, int v1, int v2, int v3, int v4)
{
    if (p_current_list == NULL) {
        display_node *p_node = allocate_display_node(type,v1,v2,v3,v4);
        if (p_node == NULL) return E_DELETE;
        draw_primitive(p_node);
        free_display_node(p_node);
        return 0;
    }
    switch (edit_mode) {
        case EDIT_REPLACE:
        case EDIT_INSERT:
            break;
        case EDIT_APPEND:
            if (display_append(p_current_list, type, v1, v2, v3, v4) == ERROR)
                return E_NOSPACE;
            p_current_list = &NEXT(*p_current_list);
            break;
    }
    return 0;
}

int line(int x1, int y1, int x2, int y2)
{
    return _primitive(LINE, x1, y1, x2, y2);
}

int rectangle(int x1, int y1, int x2, int y2)
{
    return _primitive(RECTANGLE, x1, y1, x2, y2);
}

int circle(int x, int y, int radius)
{
    return _primitive(CIRCLE, x, y, radius, 0);
}

int mark(int value)
{
    return _primitive(MARK, value, 0, 0, 0);
}

int editobject(list *object, int mark_value, int replaceflag)
{
    static list editlist;
    list mark_node;
    
    if (replaceflag != EDIT_REPLACE && replaceflag != EDIT_INSERT)
        return E_BADPARAM;
    if (find_mark(object, mark_value, &mark_node) == ERROR)
        return E_NOMARK;

    p_current_list = &editlist;
    *p_current_list = mark_node;
    edit_mode = replaceflag;

    return 0;
}

int main()
{
}

