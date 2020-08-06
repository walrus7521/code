#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};

Node *getNode(char ch, int freq, Node *left, Node *right)
{
    Node *n = new Node();
    n->ch = ch;
    n->freq = freq;
    n->left = left; n->right = right;
    return n;
}

struct comp {
    bool operator()(Node *l, Node *r) { return (l->freq > r->freq); }
};

void encode(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) return;
    if (!root->left && !root->right) huffmanCode[root->ch] = str;
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void decode(Node *root, int &index, string str)
{
    if (root == nullptr) return;
    if (!root->left && !root->right) {
        cout << root->ch;
        return;
    }
    index++;
    if (str[index] == '0') decode(root->left, index, str);
    else                   decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{
    unordered_map<char, int> freq;
    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto ch: text) freq[ch]++; // create frequency mapping
    for (auto pair: freq) pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
    Node *root = pq.top();
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
    cout << "Huffman Codes:\n"; 
    for (auto pair: huffmanCode) cout << pair.first << " " << pair.second << '\n';
    cout << "Original string  : " << text << '\n';
    string encoded_str = "";
    for (char ch : text) encoded_str += huffmanCode[ch];
    cout << "Encoded string   : " << encoded_str << '\n';
    root = pq.top();
    cout << "Decoded string   : ";
    int index = -1;
    while (index < (int) encoded_str.size() - 2) decode(root, index, encoded_str);
}

int main()
{
    string text = "geeksforgeeks";
    buildHuffmanTree(text);
    cout << '\n';
}

