#include <iostream>

using namespace std;

class Strategy { // abstract 
public:
    virtual void AlgorithmInterface() = 0;
};
 
class ConcreteStrategyA : public Strategy {
public:
    void AlgorithmInterface() { // override 
        cout << "Called ConcreteStrategyA.AlgorithmInterface()" << endl;
    }
};
 
class ConcreteStrategyB : public Strategy {
public:
    void AlgorithmInterface() { // override 
        cout << "Called ConcreteStrategyB.AlgorithmInterface()" << endl;
    }
};
 
class ConcreteStrategyC : public Strategy {
public:
    void AlgorithmInterface() { // override 
        cout << "Called ConcreteStrategyC.AlgorithmInterface()" << endl;
    }
};
 
class Context {
private:
    Strategy *_strategy;
public: 
    Context(Strategy *strategy) {
        _strategy = strategy;
    }
    void ContextInterface() {
        _strategy->AlgorithmInterface();
    }
};

int main()
{
    Context *context;
    // Three contexts following different strategies
    context = new Context(new ConcreteStrategyA());
    context->ContextInterface();
 
    context = new Context(new ConcreteStrategyB());
    context->ContextInterface();
 
    context = new Context(new ConcreteStrategyC());
    context->ContextInterface();
}

