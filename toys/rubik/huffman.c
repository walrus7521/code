#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

#define MAX 256

// https://www.geeksforgeeks.org/huffman-decoding/
struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

unordered_map<char, string> huffmanCode;

struct comp {
    bool operator()(Node *l, Node *r) {
        return (l->freq > r->freq);
    }
};

Node *getNode(char c, int freq, Node *left, Node *right)
{
    Node *n = (Node *) malloc(sizeof(Node));
    n->ch = c;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

#if 0
Node *g_heap[MAX];
int g_heap_size = 0;

void up_min(int k)
{
    Node *v = g_heap[k];
    while (g_heap[k/2]->freq > v->freq) {
        g_heap[k] = g_heap[k/2];
        k = k/2;
    }
    g_heap[k] = v;
}

void down_min(int k) {
    Node *last = g_heap[k]; /* grab min */
    int child;
    while (k <= g_heap_size/2) {
        child = 2 * k;
        if (child < g_heap_size && g_heap[child+1]->freq < g_heap[child]->freq) child++;
        if (last->freq <= g_heap[child]->freq) break;
        g_heap[k] = g_heap[child];
        k = child;
    }
    g_heap[k] = last;
}

void show() 
{
    int i;
    printf("show nodes\n");
    for (i = 1; i <= g_heap_size; i++) printf("a[%02d] = (%c,%d)\n", i, g_heap[i]->ch, g_heap[i]->freq);
    //for (i = 1; i <= g_heap_size; i++) printf("a[%02d] = %02d\n", i, g_heap[i]->freq);
}

void put_node(Node *n)
{
    g_heap[++g_heap_size] = n; // insert at bottom
    up_min(g_heap_size); // bubble up
}

Node *get_min()
{
    Node *min = g_heap[1]; // save top
    g_heap[1] = g_heap[g_heap_size--]; // copy bottom to top
    down_min(1); // sink down
    return min;
}

void init()
{
    for (int i = 0; i < MAX; i++) {
        Node *n = (Node *) malloc(sizeof(Node));
        n->ch = '\0';
        n->freq = 0;
        g_heap[i] = n;
    }
}

void drain()
{
    printf("drain huff\n");
    while (g_heap_size != 0) {
        Node *min = g_heap[1];
        g_heap[1] = g_heap[g_heap_size--]; // copy bottom to top
        down_min(1); // sink down
        printf("%d ", min->freq);
    }
}
#endif

void encode(Node *root, string str)
{
    if (root == nullptr) return;
    if (!root->left && !root->right) {
        //printf("encode: root->ch %c %s\n", root->ch, str.c_str());
        huffmanCode[root->ch] = str;
    }
    encode(root->left, str + "0");
    encode(root->right, str + "1");
}

void decode(Node *root, int &index, string str)
{
    if (root == nullptr) return;
    if (!root->left && !root->right) {
        printf("%c", root->ch);
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
    int freqs[MAX];
    string text = "geeksforgeeks";
    int slen = text.size();

    unordered_map<char, int> mfreqs;
    priority_queue<Node *, vector<Node*>, comp> pq;

    memset(freqs, 0, sizeof(freqs));
    // calculate frequencies
    for (int i = 0; i < slen; i++) freqs[text[i]]++;
    for (char i = 'a'; i <= 'z'; i++) {
        if (freqs[i]) printf("freqs[%c] = %d\n", i, freqs[i]);
    }

    for (auto ch: text) {
        mfreqs[ch]++;
    }

    //init();

    for (auto pair: mfreqs) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    printf("now build huffster\n");
    while (pq.size() != 1) { //g_heap_size >= 2)
        Node *left = pq.top(); pq.pop(); //get_min();
        Node *right = pq.top(); pq.pop(); //get_min();
        int sum = left->freq + right->freq;
        Node *n = getNode('\0', sum, left, right);
        printf("%02d:%1c %02d:%1c => %02d\n", left->freq, left->ch, right->freq, right->ch, n->freq);
        pq.push(getNode('\0', sum, left, right));
    }

    Node *root = pq.top();
    encode(root, "");

    printf("Huffman Codes are :\n");
    for (auto pair: huffmanCode) {
        printf("%c -> %s\n", pair.first, pair.second.c_str());
    }

    printf("original string: %s\n", text.c_str());

    string encoded_str = "";
    for (char ch : text) {
        encoded_str += huffmanCode[ch];
    }
    printf("encoded string: %s\n", encoded_str.c_str());

    // now decode
    //root = g_heap[1];
    root = pq.top();
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

