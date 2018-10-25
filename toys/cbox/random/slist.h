#include <stdio.h>
#include <stdlib.h>

/*
 *  Add: 
 *      slist_get_median(list);
 *      slist_exchange(list, position1, position2);
 *      slist_copy(list1, list2);
 *      slist_join(list1, list2);
 *      slist_split(list, oddlist, evenlist);
 */

//typedef char e_v;
//typedef void* e_v;
//typedef int e_v;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct _link {
    struct _link *next;
    e_v value, max;
} link;

typedef struct {
    int count;
    link *front, *rear;
} list, queue;
#define slist_empty(head) ((head)->front == NULL)

list *slist_init()
{
    list *h = (list *) malloc(sizeof(list));
    h->front = h->rear = NULL;
    h->count = 0;
    return h;
}

void slist_update_count(list *list)
{
    link *node;
    int count = 0;
    if (!list->front) printf("head is null..\n");       
    node = list->front;
    while (node) {
        count++;
        node = node->next;
    }
    list->count = count;
}

link *slist_max(list *head)
{
    link *t;
    if (slist_empty(head)) return NULL;
    t = head->front;
    return t;
}

void slist_push_front(list *head, e_v value)
{
    link *t = (link *) malloc(sizeof(link));
    link *m;
    t->value = value;    
    t->next = NULL;
    if (slist_empty(head)) {
        head->front = head->rear = t;
        t->max = value;
    } else {
        m = slist_max(head);
        t->max = MAX(m->max, value);
        //printf("push_front max = %d\n", t->max);
        t->next = head->front;
        head->front = t;
    }
    head->count++;
}

void slist_push_back(list *head, e_v value)
{
    link *t = (link *) malloc(sizeof(link));
    link *m;
    t->value = value;    
    t->next = NULL;
    if (slist_empty(head)) {
        head->front = head->rear = t;
        t->max = value;
    } else {
        m = slist_max(head);
        t->max = MAX(m->max, value);
        head->rear->next = t;
        head->rear = t;
    }
    head->count++;
}

link *slist_pop_front(list *head)
{
    link *t;
    if (slist_empty(head)) return NULL;
    t = head->front;
    head->front = head->front->next;
    if (slist_empty(head)) head->rear = NULL;
    head->count--;
    //printf("pop - max = %d\n", t->max);
    return t;
}

void slist_show(list *head, void (dump)(void *))
{
    link *list = head->front;
    if (slist_empty(head)) {
        printf("list is empty\n");
            return;
    }
    while (list) {
        //printf("value => %p\n", list->value);
        dump((void *) list);
        list = list->next;
    }
}

int slist_size(list *head)
{
    if (head) return head->count;
    return 0;
}

list *slist_merge(list *first, list *second)
{
    list *m;
    link *fl, *sl;
    if (slist_empty(first)) return second;
    if (slist_empty(second)) return first;
    m = slist_init();
    fl = first->front;
    sl = second->front;
    while (fl && sl) {
        if (fl->value < sl->value) {
            slist_push_back(m, fl->value);
            fl = fl->next;
        } else
        if (fl->value == sl->value) {
            slist_push_back(m, fl->value);
            slist_push_back(m, sl->value);
            fl = fl->next;
            sl = sl->next;
        } else {
            slist_push_back(m, sl->value);
            sl = sl->next;
        }
    }
    if (fl) {
        while (fl) {
            slist_push_back(m, fl->value);
            fl = fl->next;
        }
    } else
    if (sl) {
        while (sl) {
            slist_push_back(m, sl->value);
            sl = sl->next;
        }
    }
    return m;
}

void slist_reverse(list *head)
{
    list *tmp = slist_init();
    link *plast, *tlnk;
    while (!slist_empty(head)) {
        plast = head->rear;
        while (head->front != plast) {
            tlnk = slist_pop_front(head);
            slist_push_back(head, tlnk->value);
        }
        /* rear is now at front */
        tlnk = slist_pop_front(head);
        slist_push_back(tmp, tlnk->value);
    }
    while(!slist_empty(tmp)) {
        tlnk = slist_pop_front(tmp);
        slist_push_back(head, tlnk->value);
    }
    free(tmp);
}

link *reverse(list *head)
{
    link *r, *p1, *p2;
    r = NULL;
    p1 = head->front;
    while (p1) {
        p2 = p1->next;
        p1->next = r;
        r = p1;
        p1 = p2;
    }
    return r;
}

void linsert_at(list *head, e_v data, int position)
{
    int k;
    link *t = (link *) malloc(sizeof(link));
    link *p, *q;
    t->value = data;
    if (position == 1) {
        t->next = head->front;
        head->front = t;
    } else {
        k = 1;
        p = head->front;
        while (p && k < position) {
            k++;
            q = p;
            p = p->next;
        }
        q->next = t;
        t->next = p;
    }
}

link *lremove_from(link *head, int position)
{
    int k = 1;
    link *p, *q;
    if (position == 1) {
        p = head->next;
        //printf("position %d at %d, data %d\n", position, k, p->value);
    } else {
        k = 1;
        p = head->next;
        while (p && k < position) {
            k++;
            q = p;
            p = p->next;
        }
        if (p) {
            //printf("position %d at %d, data %d\n", position, k, p->value);
            q->next = p->next;
        } else {
            printf("position %d at %d, ???\n", position, k);
        }
    }
    return p;
}

void insort(link *head, e_v data)
{
    link *v, *t;
    t = (link *) malloc(sizeof(link));
    t->value = data;
    for (v = head; v->next != NULL; v = v->next) {
        if (v->next->value > data) break;
    }
    t->next = v->next;
    v->next = t;
}

link *find_nth_from_last(link *head, int nth)
{
    link *p1 = NULL, *p2 = NULL;
    int counter = 0;
    p2 = p1 = head->next;
    while (p1) {
        if (counter > nth) {
            p2 = p2->next;
        }
        counter++;
        p1 = p1->next;
    }
    return p2;
}

void flip_nth(link *head, int nth)
{
    link *p1, *p2, *p3, *t;
    int counter = 0;
    p1 = NULL;
    p2 = head->next;
    while (p2) {
        p3 = p2->next;
        if (nth == 0) {
            p2->next = p1;
        } else
        if (counter == nth) {
            t = p2;
            if (p1) p1->next = p3;
            t->next = p3->next;
            p3->next = p2;
            counter = -1;
        }
        counter++;
        p1 = p2;
        p2 = p3;
    }
}

void enqueue(queue *q, e_v x)
{
    slist_push_back(q, x);
}

e_v dequeue(queue *q)
{
    link *t = slist_pop_front(q);
    return t->value;
}

void init_queue(queue *q)
{
    q = slist_init();
}

void dump(void *l)
{
    link *list = (link *) l;
    printf("list->value = %d\n", list->value);
    //printf("list->value = %s\n", list->value);
}

void make_cycle(list *head)
{
    int i;
    link *save;
    for (i = 0; i < 12; i++) {
        slist_push_back(head, i);
        if (i == 6) {
            save = head->rear;
            printf("saved node: [%d] = %d\n", i, save->value);
        }
    }
    printf("dump before splice...\n");
    slist_show(head, dump);
    /* check last node */
    printf("rear = %d\n", head->rear->value);
    head->rear->next = save;

}

int hasLoop(list *first) {
    int looper = 0;
    link *slow = first->front;
    link *fast = first->front;

    while(slow && slow->next && fast && fast->next && fast->next->next) {
        printf("slow => %d, fast => %d\n", slow->value, fast->value);
        slow = slow->next;          // 1 hop
        fast = fast->next->next;    // 2 hops 
        if(slow == fast) { // fast caught up to slow, so there is a loop
            printf("gotta looper: fast[%p]->%d, slow[%p]->%d\n", fast, fast->value, slow, slow->value);
            looper = 1;
            break;
        }
    }
    return looper;  // fast reached null, so the list terminates
}

int detect_cycle(list *head)
{
    int hit = 0;
    link *slow, *fast;
    slow = fast = head->front;
    while (1) {
        slow = slow->next;
        if (fast->next != NULL) {
            fast = fast->next->next;
        } else {
            printf("done...1\n");
            break;
        }
        if (fast == NULL || slow == NULL) {
            printf("done...2\n");
            break;
        }
        if (slow == fast) {
            printf("hit!!! %p = %p BANG!!!\n", slow, fast);
            hit = 1;
            break;
        }
    }
    return hit;
}

#if 0
int main_old(int argc, char *argv[])
{
    int i, len;
    list *head;

    head = slist_init();
    for (i = 0; i < 8; i++) {
        slist_push_front(head, (e_v) i);
    }
    slist_show(head, dump);
    len = slist_size(head);
    printf("list length = %d\n", len);
    linsert_at(head, 44, (e_v) 3);
    slist_show(head, dump);
    len = slist_size(head);
    printf("list length = %d\n", len);
    //p.next = lreverse(head);
    //show(&p);
    //t = lremove_from(head, 2);
    //if (t) 
    //    printf("removed %d\n", t->value);
    slist_show(head, dump);
    len = slist_size(head);
    printf("list length = %d\n", len);
    return 0;
    //p = find_nth_from_last(head, 3);
    //linsert(head, v);
    //insort(head, v);
    //p = lremove(head, v);
    //head.next = reverse(head);
}
#endif

void loop_test()
{
    list *h = slist_init();
    make_cycle(h);
    printf("has cycle: %d\n", detect_cycle(h));
    printf("has loop: %d\n", hasLoop(h));
}

#if 0
int do_war()
{
    queue *decks[2];
    char value, suit, c;
    int i;
    while (1) {
        for (i = 0; i <= 1; i++) {
            init_queue(&decks[i]);
            
        }
    }
    return 0;
}
#endif

int slist_merge_test()
{
    list *m;

    list *first = slist_init();
    list *second = slist_init();

    slist_push_back(first, 0);
    slist_push_back(first, 2);
    slist_push_back(first, 4);
    slist_push_back(first, 6);
    slist_push_back(first, 8);
    slist_show(first, dump);

    slist_push_back(second, 1);
    slist_push_back(second, 3);
    slist_push_back(second, 5);
    slist_push_back(second, 7);
    slist_push_back(second, 9);
    slist_show(second, dump);

    m = slist_merge(first, second);
    slist_show(m, dump);

    return 0;
}

#if 1
int slist_test()
{
    int i;
    e_v x;
    link *t;
    list *h;

    loop_test();
    return 0;

    //slist_merge_test();
    //return 0;

    h = slist_init();
    for (i = 0; i < 12; i++) {
        x = i;
        slist_push_back(h, x);
        //push_front(h, i);
    }
    slist_show(h, dump);
    //slist_reverse(h);
    h->front = reverse(h);
    slist_show(h, dump);
    return 0;
    while (!slist_empty(h)) {
        t = slist_pop_front(h);
        printf("t->value = %d\n", t->value);
        free(t);
    }
    slist_show(h, dump);
    free(h);
    return 0;
}
#endif

