#ifndef CLIST_H
#define CLIST_H

typedef struct clist {
    int id;
    void *data;
} clist;

clist *clist_create(void *data);
int clist_init(clist *l);
bool clist_empty(clist *l);
int clist_insert(clist *l, void *data);
int clist_append(clist *l, void *data);
int clist_delete(clist *l, void *data);

#endif // CLIST_H
