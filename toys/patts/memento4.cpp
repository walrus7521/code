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
    // Gets or sets state
    //public string State
    //{
    //  get { return _state; }
    //}
};
 
class Originator
{
private:
    string _state;
public: 
    // Property
    //string State
    //{
    //  get { return _state; }
    //  set
    //  {
    //    _state = value;
    //    Console.WriteLine("State = " + _state);
    //  }
    //}
 
    // Creates memento 
    Memento *CreateMemento()
    {
        return (new Memento(_state));
    }
 
    // Restores original state
    void SetMemento(Memento *memento)
    {
      cout << "Restoring state..." << endl;
      //State = memento.State; // uses setter
    }
};
 
 
class Caretaker
{
private:
    Memento *_memento;
 
    // Gets or sets memento
    //public Memento Memento
    //{
    //  set { _memento = value; }
    //  get { return _memento; }
    //}
};
 
int main()
{
//    Originator o = new Originator();
//    o.State = "On";
 
    // Store internal state
//    Caretaker c = new Caretaker();
//    c.Memento = o.CreateMemento();
 
    // Continue changing originator
//    o.State = "Off";
 
    // Restore saved state
//    o.SetMemento(c.Memento);
 
}

