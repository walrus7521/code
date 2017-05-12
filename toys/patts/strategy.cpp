#include <iostream>

using namespace std;
 
class SortBehavior 
{
    public:
        virtual void sort() const = 0;
};
 
class Merge: public SortBehavior 
{
    public:
        virtual void sort() const {
            cout << "Merge sort()\n";
        }
};
 
class Quick: public SortBehavior {
    public:
        virtual void sort() const {
            cout << "Quick sort()\n";
        }
};
 
class Heap: public SortBehavior
{
    public:
        virtual void sort() const {
            cout << "Heap sort()\n";
        }
};
 
class SearchBehavior 
{
    public:
        virtual void search() const = 0;
};
 
class Sequential: public SearchBehavior 
{
    public:
        virtual void search() const {
            cout << "Sequential search()\n";
        }
};

class BinaryTree: public SearchBehavior 
{
    public:
        virtual void search() const {
            cout << "BinaryTree search()\n";
        }
};

class HashTable: public SearchBehavior 
{
    public:
        virtual void search() const {
            cout << "HashTable search()\n";
        }
};

// Context
class Collection 
{
    private:
        SortBehavior* m_sort;
        SearchBehavior* m_search;
    public:
        Collection(){}
        void set_sort(SortBehavior* s){
            m_sort = s;
        }
        void set_search(SearchBehavior* s){
            m_search = s;
        }
        void sort() const {
            m_sort->sort();
        }
        void search() const {
            m_search->search();
        }
};
 
 
int main(int argc, char *argv[])
{
    // instantiate concrete sort algorithm classes
    Merge merge;
    Quick quick;
    Heap heap;

    // create a context class for sorting strategies
    // and assign one of the concrete sort algorithms
    Collection colA;
    colA.set_sort(&merge);
    colA.sort(); // run the concrete sort algorithm via the context

    // instantiate concreate search algorithm classes
    Sequential sequential;
    BinaryTree binaryTree;
    HashTable hashTable;
 

    // create a context class for searching strategies
    // and assign one of the concrete search algorithms
    Collection colB;
    colB.set_search(&binaryTree);
    colB.search();

    return 0;
}
