#include <stdio.h>
#include <stdlib.h>

#define LT(a,b) ((a) <  (b))
#define LE(a,b) ((a) <= (b))
#define MAXLIST 16
typedef struct _list {
    int count;
    int entry[MAXLIST];
} list;

void show(list *list)
{
    int i;
    for (i = 0; i < list->count; i++) {
        printf("x: %d\n", list->entry[i]);
    }
}

void add(int x, list *list)
{
    if (list->count < MAXLIST) {
        list->entry[list->count++] = x;
    }
}

void isort(list *list)
{
    int fu, place, current;
    for (fu = 1; fu < list->count; fu++) {
        if (LT(list->entry[fu], list->entry[fu-1])) {
            current = list->entry[fu];
            for (place = fu-1; place >= 0; place--) {
                list->entry[place+1] = list->entry[place];
                if (place == 0 || LE(list->entry[place-1], current)) {
                    break;
                }
            }
            list->entry[place] = current;
        }
    }
}

void isort_test() 
{
    list list;
    list.count = 0; // creates empty array
    add(4, &list);
    add(6, &list);
    add(2, &list);
    add(8, &list);
    add(3, &list);
    add(9, &list);
    show(&list);
    printf("now sort the list...\n\n");
    isort(&list);
    show(&list);
}
