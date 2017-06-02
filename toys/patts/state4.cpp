#include <iostream>
 
using namespace std;

class Context;

class State // abstract
{
public:
    State(){}
    virtual void Handle(Context *context){}
};
 
class Context
{
private:
    State *_state;
public: 
    Context(State *state) {
        _state = state;
    }
 
    State *GetState() { return _state; }
    void SetState(State *state) { _state = state; 
        cout << "SetState: " << "dude" << endl; //_state.GetType().Name << endl;
    }
 
    void Request() {
        _state->Handle(this);
    }
};

class ConcreteStateB;
class ConcreteStateA : public State
{
public:
    void Handle(Context *context) {
        //context->SetState(new ConcreteStateB());
        context->SetState(this);
    }
};
 
class ConcreteStateB : State
{
public:
    void Handle(Context *context) {
        context->SetState(new ConcreteStateA());
        //context->SetState(this);
    }
};

int main()
{
    // Setup context in a state
    Context *c = new Context(new ConcreteStateA());
 
    // Issue requests, which toggles state
    c->Request();
    c->Request();
    c->Request();
    c->Request();

}

