#include <iostream>
#include <string>
#include <map>

using namespace std;
 
class Flyweight // abstract
{
public:
    virtual void Operation(int extrinsicstate) = 0;
};

class ConcreteFlyweight : public Flyweight
{
public:
    void Operation(int extrinsicstate) // override
    { cout << "ConcreteFlyweight: " << extrinsicstate << endl; }
};

class UnsharedConcreteFlyweight : public Flyweight
{
public:
    void Operation(int extrinsicstate) // override
    { cout << "UnsharedConcreteFlyweight: " << extrinsicstate << endl; }
};

class FlyweightFactory
{
private:
    std::map<std::string,Flyweight*> flyweights;
public:
    FlyweightFactory() {
        flyweights["X"] = new ConcreteFlyweight();
        flyweights["Y"] = new ConcreteFlyweight();
        flyweights["Z"] = new ConcreteFlyweight();
    }
    Flyweight *GetFlyweight(string key) {
        return ((Flyweight*)flyweights[key]);
    }
};
 
int main() {
    int extrinsicstate = 22;
 
    FlyweightFactory *factory = new FlyweightFactory();
 
    // Work with different flyweight instances
    Flyweight *fx = factory->GetFlyweight("X");
    fx->Operation(--extrinsicstate);
 
    Flyweight *fy = factory->GetFlyweight("Y");
    fy->Operation(--extrinsicstate);
 
    Flyweight *fz = factory->GetFlyweight("Z");
    fz->Operation(--extrinsicstate);
 
    UnsharedConcreteFlyweight *fu = new UnsharedConcreteFlyweight();
    fu->Operation(--extrinsicstate);
}

