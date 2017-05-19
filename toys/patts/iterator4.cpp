#include <iostream>
using namespace std;

class Aggregate
{
public:
    Aggregate(long size = 32) {}
    virtual int count() = 0;
    virtual int& get(int index) = 0;
};

class List : public Aggregate
{
public:
    List(int size = 32) :_idx(0), _sz(size), ::Aggregate(size) {}
    int count() { return _idx; }
    int& get(int index) { return items[index]; }
    void add(int x) { items[_idx++] = x; }
    void dump() { for (int i = 0; i < _idx; i++) cout << "[" << i << "] = " << items[i] << endl; }
private:
    int _sz;
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
    virtual void begin() { /*cout << "begin" << endl;*/ _idx = 0; }
    virtual void next() { _idx++; /*cout << "next: " << _idx << endl;*/ if (_idx >= _count) cout << "boom" << endl; }
    virtual bool end() { /*cout << "done: " << _count << endl;*/ return (_idx > _count-1) ? true : false; }
    virtual int currentItem() { return _list->get(_idx); }
private:
    int _count;
    int _idx;
    List *_list;    
};

void test_iter()
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

int main()
{
    test_iter();
}

