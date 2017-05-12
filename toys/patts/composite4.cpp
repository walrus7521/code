#include <iostream>

using namespace std;

class Composite;

class Component {
public:
    virtual Composite* GetComposite() { return nullptr; }
};

class Composite : public Component
{
public:
    void Add(Component *c) { cout << "adding composite" << endl; }
    virtual Composite* GetComposite() { return this; }
};

class Leaf : public Component
{
};

int main()
{
    Composite* aComposite = new Composite;
    Leaf* aLeaf = new Leaf;

    Component* aComponent;
    Composite* test;

    cout << "add to composite" << endl;
    aComponent = aComposite;
    if ((test = aComponent->GetComposite())) {
        test->Add(new Leaf);
    }

   // Leaves don't add, but they still can be invoked
    cout << "add to leaf" << endl;
    aComponent = aLeaf;
    if ((test = aComponent->GetComposite())) {
        test->Add(new Leaf);
    }
}
