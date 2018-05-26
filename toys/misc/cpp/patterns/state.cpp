#include <iostream>
 
using namespace std;

class Context;

class State // abstract State
{
public:
    virtual void Handle(Context *context) = 0;
    virtual string GetName() = 0;
};
 
class Context // Machine
{
private:
    State *_state;
public: 
    Context(State *state) {
        _state = state;
    }
    State *GetState() { return _state; }
    void SetState(State *state) { 
        _state = state; 
        cout << "SetState: " << 
            state->GetName() << endl;
    }
    void Request() { _state->Handle(this); }
};

class ConcreteStateA : public State
{
private:
    string _name;
public:
    ConcreteStateA() { _name = "A"; }
    string GetName() { return _name; }
    void Handle(Context *context);
};
 
class ConcreteStateB : public State
{
private:
    string _name;
public:
    ConcreteStateB() { _name = "B"; }
    string GetName() { return _name; }
    void Handle(Context *context);
};


void ConcreteStateA::Handle(Context *context) {
    context->SetState(new ConcreteStateB());
}

void ConcreteStateB::Handle(Context *context) {
    context->SetState(new ConcreteStateA());
}

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

