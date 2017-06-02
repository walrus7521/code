#include <iostream>
using namespace std;

class Aggregate
{
public:
    Aggregate(long size = 32) {}
    virtual int count() = 0;
    virtual int& get(int index) = 0;
};

// concrete agregate
class List : public Aggregate
{
public:
    List(int size = 32) :_idx(0), ::Aggregate(size) {}
    int count() { return _idx; }
    int& get(int index) { return items[index]; }
    void add(int x) { items[_idx++] = x; }
private:
    int _idx;
    int items[32];
};

class Iterator
{
public:
    virtual void begin() = 0;
    virtual void next() = 0;
    virtual bool end() = 0;
    virtual int currentItem() = 0;
protected:
    Iterator() {};
};

class ListIterator : public Iterator
{
public:
    ListIterator(List *list) : _list(list) { _count = list->count(); }
    virtual void begin() { _idx = 0; }
    virtual void next() { _idx++; if (_idx >= _count) cout << "boom" << endl; }
    virtual bool end() { return (_idx > _count-1) ? true : false; }
    virtual int currentItem() { return _list->get(_idx); }
private:
    int _count;
    int _idx;
    List *_list;    
};

int main()
{
    List *list = new List(32);
    list->add(42);
    list->add(43);
    list->add(44);
    list->add(45);
    list->add(46);
    list->add(47);
    list->add(48);
    int i;
    ListIterator itl(list);
    for (i = 0, itl.begin(); !itl.end(); itl.next(), i++) {
        cout << "[" << i << "] = " << itl.currentItem() << endl;
    }
}

