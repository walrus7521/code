#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>

namespace Heap {

#define PARENT(x)       (x/2)
#define LEFT_CHILD(x)   ((2*(x))+1)
#define RIGHT_CHILD(x)  ((2*(x)))

template <typename T>
struct Heap {
    std::vector<T> A; // index 0 is not used
    int length;
    int size;
};

template <typename T>
using HeapPtr = std::shared_ptr<Heap<T>>;

template <typename T>
void Heap_tree(HeapPtr<T> h);

template <typename T>
HeapPtr<T> Heap_create(int max)
{
    HeapPtr<T> h(new Heap<T>);
    h->A.resize(max);
    h->size = max;
    h->length = 1;
    return h;
}


template <typename T>
void Heap_insert(HeapPtr<T> h, T key)
{
    int i;
    T tmp;
    h->A[h->length] = key;
    for (i = h->length; i > 1; --i) {
        if (h->A[i] > h->A[PARENT(i)]) {
            tmp = h->A[i];
            h->A[i] = h->A[PARENT(i)];
            h->A[PARENT(i)] = tmp;
        }
    }
    h->length++;
}

template <typename T>
int Heap_top(HeapPtr<T> h)
{
    T key = h->A[1], tmp;
    int i;
    h->A[1] = h->A[h->length-1];
    h->length--;
    for (i = 1; i < h->length; ++i) {
        if (h->A[i] < h->A[LEFT_CHILD(i)]) {
            tmp = h->A[i];
            h->A[i] = h->A[LEFT_CHILD(i)];
            h->A[LEFT_CHILD(i)] = tmp;
        } 
        if (h->A[i] < h->A[RIGHT_CHILD(i)]) {
            tmp = h->A[i];
            h->A[i] = h->A[RIGHT_CHILD(i)];
            h->A[RIGHT_CHILD(i)] = tmp;
        }
    }
    return key;
}

template <typename T>
void Heap_extract(HeapPtr<T> h, T key)
{
    int i, j;
    T tmp;
    //std::cout << "extracting: " << key << '\n';
    for (i = 1; i < h->length; ++i) {
        if (key == h->A[i]) {
            h->length--;
            if (i == h->length) {
                h->A[i] = 0;
                return;
            }
            h->A[i] = h->A[h->length];
            for (j = i; j < h->length; ++j) {
                if (h->A[j] < h->A[LEFT_CHILD(j)]) {
                    tmp = h->A[j];
                    h->A[j] = h->A[LEFT_CHILD(j)];
                    h->A[LEFT_CHILD(j)] = tmp;
                } 
                if (h->A[j] < h->A[RIGHT_CHILD(j)]) {
                    tmp = h->A[j];
                    h->A[j] = h->A[RIGHT_CHILD(j)];
                    h->A[RIGHT_CHILD(j)] = tmp;
                }
            }
            return;
        }
    }
}

template <typename T>
void Heap_dump(HeapPtr<T> h)
{
    int i;
    for (i = 1; i <= h->length-1; ++i) {
        std::cout << "A[" << i << "] = " << h->A[i] << '\n';
    }
}

template <typename T>
void Heap_tree(HeapPtr<T> h)
{
    int i, level, j, k;
    int lvl[] = {0, 
        1,  
        2,  2,  
        4,  4,  4,  4, \
        8,  8,  8,  8,  8,  8,  8,  8, \
        16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
    std::cout << "tree time" << '\n';
    for (i = 1; i <= h->length-1; ) {
        level = lvl[i];
        switch (level) {
            case 1: std::cout << "        "; break;
            case 2: std::cout << "      "; break;
            case 4: std::cout << "  "; break;
        }
        for (j = i, k = 1; (k <= level) && (i <= h->length-1); ++k, ++j) {
            std::cout << "[" << h->A[j] << "]";
            ++i;
        }
        std::cout << '\n';
    }
}
}

using namespace std;
namespace hp = Heap;

int main()
{
    //int ii[] = {2,5,1,33,16,9,22,3,9};
    int ii[] = {67,42,43,68};

    int i;
    int sz = sizeof(ii) / sizeof(ii[0]);

    hp::HeapPtr<int> h = hp::Heap_create<int>(32);
    
    for (i = 0; i < sz; i++) {
        hp::Heap_insert(h, ii[i]);
    }

    hp::Heap_dump(h);

    hp::Heap_tree(h);
    i = hp::Heap_top(h);
    hp::Heap_tree(h);

    std::cout << "mx: " << i << '\n';

    hp::Heap_extract(h, 42);
    hp::Heap_tree(h);
    hp::Heap_extract(h, 68);
    hp::Heap_tree(h);
    hp::Heap_extract(h, 67);
    hp::Heap_tree(h);
    hp::Heap_extract(h, 43);
    hp::Heap_tree(h);
}

