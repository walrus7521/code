#include "types.hpp"

using namespace std;

/*
    sorting
    search
    ring buffer
    strings
 */

template <typename T>
void show(const vector<T> &a)
{
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

// each largest element bubbles down to end
template <typename T>
void bubble(vector<T> &a)
{
    for (int i = 0; i < a.size(); i++) {
        int sorted = 1; // short circuit
        for (int j = 0; j < a.size()-i-1; j++) { // move the bottom
            if (a[j] > a[j+1]) {
                sorted = 0;
                exchg(a[j], a[j+1]);
            }
        }
        if (sorted) { // no swaps
            cout << "jump out: " << i << endl;
            break;
        }
    }
}

// puts item in correct location each iteration
template <typename T>
void insertion(vector<T> &a)
{
    for (int i = 1; i <= a.size()-1; i++) {
        int j = i;
        while (j > 0 && a[j] < a[j-1]) {
            exchg(a[j], a[j-1]);
            j--;
        }
    }
}

// find smallest and exchg with advancing first position
template <typename T>
void selection(vector<T> &a)
{
    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            if (a[i] > a[j]) exchg(a[i], a[j]);
        }
    }
}

template <typename T>
uint64_t bitsort(vector<T> &a)
{
    uint64_t x = 0;
    for (int i = 0; i < a.size(); i++) {
        x |= (1 << a[i]);
    }
    return x;
}

int is_anagram(const string &a, const string &b)
{
    char dict[256];
    int len = a.size();
    if (len != b.size()) return 0;
    for (int i = 0; i < len; i++) dict[i] = 0;
    for (int i = 0; i < len; i++) dict[a[i]]++;
    for (int i = 0; i < len; i++) {
        if (dict[b[i]]-- == 0) return 0;
    }
    return 1;
}

int is_palindrome(const string &a)
{
    int len = a.size();
    for (int i = 0; i < len/2; i++) {
        if (a[i] != a[len-i-1]) return 0;
    }
    return 1;
}

int count_bits(uint32_t x)
{
    int count = 0;
    while (x) {
        count++;
        x &= (x-1);
    }
    return count;
}

int parity(uint32_t x)
{
    int count = count_bits(x);
    //return (count % 2) ? 0 : 1; // even parity
    return (count & 0x01); // odd parity
}

void test_bits()
{
    int x = 0x5a;
    printf("count:  %x => %d\n", x, count_bits(x));
    printf("parity: %x => %d\n", x, parity(x));

    vector<int> a = {4,3,1,2,7,31};
    show(a);
    uint32_t y = bitsort(a);
    printf("y: %08x\n", y);
    for (int i = 0; i < 64; i++) {
        if (y & 1) {
            cout << i << endl;
        }
        y >>= 1;
    }
}

int main()
{
    printf("is_ana: %d\n", is_anagram("dude", "eddu"));
    printf("is_pal: %d\n", is_palindrome("duiud"));
    vector<int> a = {2,17,9,1,42,3,6,4};
    show(a);
    //bubble(a);
    //insertion(a);
    selection(a);
    show(a);

    cout << "test bit stuff\n";
    test_bits();
}

