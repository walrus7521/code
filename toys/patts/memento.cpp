#include <iostream>
#include <string>
#include <vector>

using namespace std;
 
class Memento
{
private:
    string _state;
public: 
    // Constructor
    Memento(string state) {
        _state = state;
    }
    string GetState() { return _state; }
};
 
class Originator
{
private:
    string _state;
public: 
    // Property
    string GetState() { return _state; }
    void SetState(string state) { _state = state; 
        cout << "State = " << _state << endl;
    }
    // Creates memento 
    Memento *CreateMemento() {
        return (new Memento(_state));
    }
    // Restores original state
    void SetMemento(Memento *memento) {
      cout << "Restoring state..." << endl;
      SetState(memento->GetState());
    }
};
 
 
class Caretaker
{
private:
    Memento *_memento;
public: 
    Memento *GetMemento() {
        return _memento;
    }
    void SetMemento(Memento *memento) {
        _memento = memento;
    }
};
 
int main()
{
    Originator *o = new Originator();
    o->SetState("On");
 
    // Store internal state
    Caretaker *c = new Caretaker();
    c->SetMemento(o->CreateMemento());
 
    // Continue changing originator
    o->SetState("Off");
 
    // Restore saved state
    o->SetMemento(c->GetMemento());
 
}

