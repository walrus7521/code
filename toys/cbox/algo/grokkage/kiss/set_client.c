#include <stdio.h>
#include <stdbool.h>

// these need to go into header file
extern void *set_new();
extern int set_add(void *set, int n, char **arr);
extern void set_show(void *set);
extern void *set_union(void *a, void *b);
extern void *set_intersection(void *a, void *b);
extern void *set_difference(void *a, void *b);
extern bool is_member(void *tree, char *key);

int main()
{   
    char *bartel[]  = { "bart", "grant", "chad", "alex", "rowdy" };
    char *gregory[] = { "rowdy", "cindy", "mackenzie", "taylor", "claire" };
    void *h_bartel = NULL;
    void *h_gregory = NULL;

    int len = 10;
    printf("len: %d\n", len);
    set_add(&h_bartel, 5, bartel);
    set_add(&h_gregory, 5, gregory);
    set_show(h_bartel);
    set_show(h_gregory);
    
    void *h_union = set_union(h_bartel, h_gregory);
    printf("union:\n");
    set_show(h_union);
    void *h_intersect = set_intersection(h_bartel, h_gregory);
    printf("intersection:\n");
    set_show(h_intersect);
    void *h_diff = set_difference(h_bartel, h_gregory);
    printf("difference:\n");
    set_show(h_diff);
    char *key = "mackenzie";
    printf("find: %s => %s\n", key, find(h_intersect, key));

}

