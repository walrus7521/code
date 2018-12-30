#include <iostream>

using namespace std;

class Receiver;

class Command { // abstract 
protected:
    Receiver *_receiver;
public:
    Command(Receiver *receiver) {
      _receiver = receiver;
    }
    virtual void Execute() = 0; // abstract
};

class Receiver { // concrete receiver
public:
    void Action() { cout << "Called Receiver.Action()" << endl; }
};

class ConcreteCommand : public Command {
public:
    ConcreteCommand(Receiver *receiver) :
      ::Command(receiver) {}
    void Execute() { _receiver->Action(); } // override
};
 
class Invoker {
private:
    Command* _command;
public:
    void SetCommand(Command *command) { _command = command; }
    void ExecuteCommand() { _command->Execute(); }
};

int main()
{
  // Create receiver, command, and invoker
  Receiver *receiver = new Receiver();
  Command *command = new ConcreteCommand(receiver);
  Invoker *invoker = new Invoker();
 
  // Set and execute command
  invoker->SetCommand(command);
  invoker->ExecuteCommand();
}

