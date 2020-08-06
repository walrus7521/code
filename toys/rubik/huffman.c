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

struct node *new(char c, int freq, struct node *left, struct node *right)
{
    struct node *n = (struct node *) malloc(sizeof(struct node));
    n->c = c;
    n->freq = freq;
    n->left = left;
    n->right = right;
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
    while (k <= g_node_heap_size/2) {
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
    printf("show nodes DDD\n");
    for (i = 1; i <= g_node_heap_size; i++) printf("a[%02d] = (%c,%d)\n", i, g_node_heap[i]->c, g_node_heap[i]->freq);
    //for (i = 1; i <= g_node_heap_size; i++) printf("a[%02d] = %02d\n", i, g_node_heap[i]->freq);
}

void put_n(struct node *n)
{
    g_node_heap[++g_node_heap_size] = n; // insert at bottom
    up_min_n(g_node_heap_size); // bubble up
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

void drain()
{
    printf("drain huff\n");
    while (g_node_heap_size != 0) {
        struct node *min = g_node_heap[1];
        g_node_heap[1] = g_node_heap[g_node_heap_size--]; // copy bottom to top
        down_min_n(1); // sink down
        printf("%d ", min->freq);
    }
}
char *huffmanCode[MAX];

char newstr[3];
void encode(struct node *root, char *str)
{
    printf("encode: %c\n", str[0]);
    if (root == NULL) return;
    if (!root->left && !root->right) {
        //printf("encode: %s\n", str);
        huffmanCode[root->c] = str;
    }
    newstr[0] = str[0]; newstr[1] = '0'; newstr[2] = '\0';
    encode(root->left, &newstr[1]);
    newstr[0] = str[0]; newstr[1] = '1'; newstr[2] = '\0';
    encode(root->right, &newstr[1]);
}

void huffster()
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
        struct node *n = new(str[i], freq[str[i]], NULL, NULL);
        put_n(n);
    }
    show_n();

    printf("now build huffster\n");
    while (g_node_heap_size >= 2) {
        struct node *min1 = get_min_n();
        struct node *min2 = get_min_n();
        int new_freq = min1->freq + min2->freq;
        struct node *n = new('$', new_freq, min1, min2);
        printf("%02d:%1c %02d:%1c => %02d\n", min1->freq, min1->c, min2->freq, min2->c, n->freq);
        put_n(n);
    }
    struct node *root = g_node_heap[1];
    encode(root, "$");
    show_n();
    drain();
}

int main()
{
    huffster();
    //heapster();
    printf("\n");
}

