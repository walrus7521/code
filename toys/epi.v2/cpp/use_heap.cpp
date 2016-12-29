#include "pch.hpp"
#include "Heap.hpp"

using namespace std;

void use_api()
{
    //int ii[] = {2,5,1,33,16,9,22,3,9};
    int ii[] = {67,42,43,68};
    int i;
    int sz = sizeof(ii) / sizeof(ii[0]);
    //shared_ptr<ListNode<int>> head = make_shared<ListNode<int>>();
    shared_ptr<Heap> heap = CreateHeap(32);

    for (int i = 0; i < sz; i++) {
        cout << "insert: " << ii[i] << endl;
        InsertHeap(heap, ii[i]);
    }
    DumpHeap(heap);
    TreeHeap(heap);
    i = TopHeap(heap);
    TreeHeap(heap);
    printf("mx: %d\n", i);

    ExtractHeap(heap, 42);
    TreeHeap(heap);
    ExtractHeap(heap, 68);
    TreeHeap(heap);
    ExtractHeap(heap, 67);
    TreeHeap(heap);
    ExtractHeap(heap, 43);
    TreeHeap(heap);

}

void use_stdlib()
{
}

int main()
{
    use_api();
    //use_stdlib();
}
