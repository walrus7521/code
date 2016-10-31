#include <iostream>

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
            printf("ctor: %p\n", pPrototype_);
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

struct ddd {
    int val;
    struct ddd *Clone(){ 
        struct ddd *t = (struct ddd *) std::malloc(sizeof(struct ddd)); 
        printf("cloning ddd (%p)\n", t);
        return t;
    }
};

int main()
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
