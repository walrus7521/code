#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

template <class T>
struct OpNewCreator
{
    static T* Create() {
        cout << "OpNewCreator" << endl;
        return new T;
    }
};

template <class T>
struct MallocCreator
{
    static T* Create() {
        void *buf = std::malloc(sizeof(T));
        if (!buf) return 0;
        cout << "MallocCreator" << endl;
        return new(buf) T;
    }
};

template <class T>
struct PrototypeCreator
{
    PrototypeCreator(T* pObj = nullptr)
        :pPrototype_(pObj) {
            printf("ctor: proto %p\n", pPrototype_);
        }

    T* Create() {
        cout << "PrototypeCreator" << endl;
        return pPrototype_ ? pPrototype_->Clone() : nullptr;
    }
    T* GetPrototype() { return pPrototype_; }
    void SetPrototype(T* pObj) { pPrototype_ = pObj; }
private:
    T* pPrototype_;
};

class ddd {
public:
    ddd() { cout << "ctor: ddd" << endl; }
    int val;
    struct ddd *Clone(){ 
        struct ddd *t = (struct ddd *) std::malloc(sizeof(struct ddd)); 
        printf("cloning ddd (%p)\n", t);
        return t;
    }
};

template <class CreationPolicy>
class WidgetManager : public CreationPolicy
{
};

class Widget {
public:
    Widget() { cout << "ctor: Widget" << endl; }
};

typedef WidgetManager< OpNewCreator<int> > MyIntMgr;
typedef WidgetManager< OpNewCreator<Widget> > MyWidgetMgr;

void test_creator()
{
    OpNewCreator<int> op;
    MallocCreator<int> mp;
    struct ddd d;
    PrototypeCreator<ddd> *pp = new PrototypeCreator<ddd>(&d);
    int *oi = op.Create();
    int *mi = mp.Create();
    struct ddd *pd = pp->Create();
    printf("pd = %p\n", pd);
    pd->val = 77;
    printf("pd: %d\n", pd->val);
}

void test_widgets()
{
    cout << "test widgets" << endl;
    WidgetManager<OpNewCreator <int> > wm;
    int *wi = wm.Create();
    MyIntMgr wm2;
    int *wi2 = wm2.Create();
    MyWidgetMgr wm3;
    Widget *w = wm3.Create();
    printf("w: %p\n", w);

}

int main()
{
    test_creator();
    test_widgets();
}
