#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <map>

using namespace std;

#define MAX 256

// https://www.geeksforgeeks.org/huffman-decoding/
struct node {
    char c;
    int freq;
    struct node *left, *right;
};

struct node *g_node_heap[MAX];
int g_node_heap_size = 0;
map<char, string> huffmanCode;

struct node *make_node(char c, int freq, struct node *left, struct node *right)
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
    printf("show nodes\n");
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

char newstr[3];
void encode(struct node *root, string str)
{
    if (root == NULL) return;
    if (!root->left && !root->right) {
        //printf("encode: root->c %c %s\n", root->c, str.c_str());
        huffmanCode[root->c] = str;
    }
    encode(root->left, str + "0");
    encode(root->right, str + "1");
}

void decode(struct node *root, int &index, string str)
{
    if (root == NULL) return;
    if (!root->left && !root->right) {
        printf("%c", root->c);
        return;
    }
    index++;
    if (str[index] == '0') 
        decode(root->left, index, str);
    else 
        decode(root->left, index, str);
}

void huffster()
{
    int a[] = { 60, 25, 10, 5 };
    int i, len=sizeof(a) / sizeof(a[0]);
    int freq[MAX];
    string str = "geeksforgeeks";
    int slen = str.size();

    memset(freq, 0, sizeof(freq));
    // calculate frequencies
    for (int i = 0; i < slen; i++) freq[str[i]]++;
    for (char i = 'a'; i <= 'z'; i++) {
        if (freq[i]) printf("freq[%c] = %d\n", i, freq[i]);
    }
    init();
    // create nodes and insert into heap -- need heap of nodes
    for (int i = 0; i < slen; i++) {
        struct node *n = make_node(str[i], freq[str[i]], NULL, NULL);
        put_n(n);
    }
    show_n();

    printf("now build huffster\n");
    while (g_node_heap_size >= 2) {
        struct node *min1 = get_min_n();
        struct node *min2 = get_min_n();
        int new_freq = min1->freq + min2->freq;
        struct node *n = make_node('\0', new_freq, min1, min2);
        printf("%02d:%1c %02d:%1c => %02d\n", min1->freq, min1->c, min2->freq, min2->c, n->freq);
        put_n(n);
    }

    struct node *root = g_node_heap[1];
    encode(root, "");

    printf("Huffman Codes are :\n");
    for (auto pair: huffmanCode) {
        printf("%c -> %s\n", pair.first, pair.second.c_str());
    }

    printf("original string: %s\n", str.c_str());

    string encoded_str = "";
    for (char ch : str) {
        encoded_str += huffmanCode[ch];
    }
    printf("encoded string: %s\n", encoded_str.c_str());

    // now decode
    root = g_node_heap[1];
    printf("decoded string is:  ");
    int index = -1;
    printf("enc len: %d\n", encoded_str.size());
    while (index < (int) encoded_str.size() - 2) {
        decode(root, index, encoded_str);
    }
    printf("\nDone\n");

}

int main()
{
    huffster();
    //heapster();
    printf("\n");
}

