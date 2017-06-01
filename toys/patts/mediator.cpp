#include <iostream>
#include <string>
#include <list>

using namespace std;

class Colleague;

class Mediator // abstract
{
public:
    virtual void Send(string message, Colleague *colleague) = 0;
};
 
class Colleague { // abstract
protected:
    Mediator *_mediator;
public: 
    Colleague(Mediator *mediator) { _mediator = mediator; }
};
 
class ConcreteColleague1 : Colleague
{
public:
    ConcreteColleague1(Mediator *mediator)
      : ::Colleague(mediator) {}
    void Send(string message) { _mediator->Send(message, this); }
    void Notify(string message) {
        cout << "Colleague1 gets message: " << message << endl; }
};
 
class ConcreteColleague2 : Colleague
{
public:
    ConcreteColleague2(Mediator *mediator)
      : ::Colleague(mediator) {}
    void Send(string message) { _mediator->Send(message, this); }
    void Notify(string message) {
        cout << "Colleague2 gets message: " << message << endl; }
};

class ConcreteMediator : public Mediator
{
private:
    ConcreteColleague1 *_colleague1;
    ConcreteColleague2 *_colleague2;
public: 
    void set1(ConcreteColleague1 *colleague1) {
      _colleague1 = colleague1; }
 
    void set2(ConcreteColleague2 *colleague2) {
      _colleague2 = colleague2; }
    void Send(string message, Colleague *colleague) { // override
      if (colleague == (Colleague*) _colleague1) {
        _colleague2->Notify(message);
      } else {
        _colleague1->Notify(message);
      }
    }
};
 
int main()
{
    ConcreteMediator *m = new ConcreteMediator();
 
    ConcreteColleague1 *c1 = new ConcreteColleague1(m);
    ConcreteColleague2 *c2 = new ConcreteColleague2(m);

    m->set1(c1);
    m->set2(c2);

    c1->Send("How are you?");
    c2->Send("Fine, thanks");

}

 
