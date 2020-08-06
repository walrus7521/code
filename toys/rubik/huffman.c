#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX 256

// https://www.geeksforgeeks.org/huffman-decoding/
struct node {
    char c;
    int freq;
    struct node *left, *right;
};

struct node *g_node_heap[MAX];
int g_node_heap_size = 0;

int g_heap[MAX] = {INT_MAX};
int g_size = 0;

void heap_show() {
    int i;
    for (i = 1; i <= g_size; i++) printf("a[%02d] = %02d\n", i, g_heap[i]);
}

void down_min(int k) {
    int child, last = g_heap[k]; /* grab min */
    while (k <= g_size/2) {
        child = 2 * k;
        if (child < g_size && g_heap[child+1] < g_heap[child]) child++;
        if (last <= g_heap[child]) break;
        g_heap[k] = g_heap[child];
        k = child;
    }
    g_heap[k] = last;
}

void up_min(int k) {
    int v = g_heap[k];
    while (g_heap[k/2] > v) {
        g_heap[k] = g_heap[k/2];
        k = k/2;
    }
    g_heap[k] = v;
}

int get_min()
{
    int min = g_heap[1]; // save top
    g_heap[1] = g_heap[g_size--]; // copy bottom to top
    down_min(1); // sink down
    return min;
}

void put(int k)
{
    g_heap[++g_size] = k; // insert at bottom
    up_min(g_size); // bubble up
}

struct node *new(char c, int freq)
{
    struct node *n = (struct node *) malloc(sizeof(struct node));
    n->c = c;
    n->freq = freq;
    return n;
}

void up_min_n(int k)
{
    struct node *v = g_node_heap[k];
    while (g_node_heap[k/2]->freq > v->freq) {
        g_node_heap[k] = g_node_heap[k/2];
        k = k/2;
    }
    g_node_heap[k] = v;
}

void down_min_n(int k) {
    struct node *last = g_node_heap[k]; /* grab min */
    int child;
    while (k <= g_size/2) {
        child = 2 * k;
        if (child < g_node_heap_size && g_node_heap[child+1]->freq < g_node_heap[child]->freq) child++;
        if (last->freq <= g_node_heap[child]->freq) break;
        g_node_heap[k] = g_node_heap[child];
        k = child;
    }
    g_node_heap[k] = last;
}

void show_n() 
{
    int i;
    printf("show nodes\n");
    for (i = 1; i <= g_node_heap_size; i++) printf("a[%02d] = (%c,%d)\n", i, g_node_heap[i]->c, g_node_heap[i]->freq);
}

void put_n(struct node *n)
{
    g_node_heap[++g_node_heap_size] = n; // insert at bottom
    up_min_n(g_size); // bubble up
}

struct node *get_min_n()
{
    struct node *min = g_node_heap[1]; // save top
    g_node_heap[1] = g_node_heap[g_node_heap_size--]; // copy bottom to top
    down_min_n(1); // sink down
    return min;
}

void init()
{
    for (int i = 0; i < MAX; i++) {
        struct node *n = (struct node *) malloc(sizeof(struct node));
        n->c = '\0';
        n->freq = 0;
        g_node_heap[i] = n;
    }
}

int main()
{
    int a[] = { 60, 25, 10, 5 };
    int i, len=sizeof(a) / sizeof(a[0]);
    int freq[MAX];
    char *str = "geeksforgeeks";
    int slen = strlen(str);

    memset(freq, 0, sizeof(freq));
    // calculate frequencies
    for (int i = 0; i < slen; i++) freq[str[i]]++;
    for (char i = 'a'; i <= 'z'; i++) {
        if (freq[i]) printf("freq[%c] = %d\n", i, freq[i]);
    }
    init();
    // create nodes and insert into heap -- need heap of nodes
    for (int i = 0; i < slen; i++) {
        struct node *n = new(str[i], freq[str[i]]);
        put_n(n);
    }
    show_n();
    printf("now build huffster\n");
    while (g_node_heap_size >= 2) {
        struct node *min1 = get_min_n();
        struct node *min2 = get_min_n();
        struct node *new = (struct node *) malloc(sizeof(struct node));
        new->freq = min1->freq + min2->freq;
        new->c = '$';
        printf("%02d:%c %02d:%c => %02d\n", min1->freq, min1->c, min2->freq, min2->c, new->freq);
        put_n(new);
    }
    show_n();

    return 0;

    printf("min heap\n");
    g_size = 0;
    g_heap[0] = -INT_MAX;
    for (i = 0; i < len; i++) {
        put(a[i]);
    }
    heap_show();
    while (g_size >= 2) {
        int min1 = get_min();
        int min2 = get_min();
        int new = min1 + min2;
        printf("%02d %02d => %02d\n", min1, min2, new);
        put(new);
    }
    heap_show();

    printf("\n");
}

