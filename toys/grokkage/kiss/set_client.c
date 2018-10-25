#include <stdio.h>

extern void *set_new();
extern int set_add(void *set, int n, char **arr);
extern void set_show(void *set);

int main()
{
    char *bartel[] = {
        "bart",
        "grant",
        "chad",
        "alex",
        "rowdy"
        };
    char *gregory[] = {
        "rowdy",
        "cindy",
        "mackenzie",
        "taylor",
        "claire"
        };
    void *handle = NULL; //set_new();

    int len = 10;
    printf("len: %d\n", len);
    set_add(&handle, 5, bartel);
    printf("handle: %p\n", handle);
    set_add(&handle, 5, gregory);
    printf("handle: %p\n", handle);
    set_show(handle);
    
}

