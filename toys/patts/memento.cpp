#include <iostream>
#include <string>
#include <vector>

using namespace std;

// wikibooks: https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns/Behavioral_Patterns#Memento

class Memento;

class Object { // originator
private:
    int state;
public:
    void dblState() { cout << "dbl\n"; state *= 2; }
    void incState() { cout << "inc\n"; state++; }
    Object(int s): state(s) {}
    Memento* createMemento() const; // creates a snapshot
    void setMemento(Memento *mem); // reinstates a snapshot
    void show() { cout << "state: " << state << endl; }
};

class Memento {
private:
    Object object;
public:
    Memento(const Object& obj): object(obj) {}
    Object snapshot() const {return object;}
};

// only the originator accesses the memento's state
Memento* Object::createMemento() const {
    return new Memento(*this);
}

void Object::setMemento(Memento* mem) {
    *this = mem->snapshot();
}

class Command { // caretaker
public:
    typedef void (Object::*Action)();
    Command(Object *obj, Action act) : receiver(obj), action(act) {
        numCommands = 0;
    }
    virtual void execute() {
        mementoList.resize(numCommands+1);
        commandList.resize(numCommands+1);
        mementoList[numCommands] = receiver->createMemento();
        commandList[numCommands] = this;
        numCommands++;
        (receiver->*action)();
    }
    static void undo() {
        commandList[numCommands-1]->receiver->setMemento(
                mementoList[numCommands-1]);
        numCommands--;
    }
    static void redo() {
        Command *redoer = commandList[numCommands];
        (redoer->receiver->*(redoer->action))();
    }
private:
    Object* receiver;
    Action action;
    static std::vector<Command*> commandList;
    static std::vector<Memento*> mementoList;
    static int numCommands;
    static int maxCommands;    
};

std::vector<Command*> Command::commandList;
std::vector<Memento*> Command::mementoList;
int Command::numCommands = 0;
int Command::maxCommands = 0;

int main() {
    Object *object = new Object(42);
    // issue commands on object and undo/redo them
    Command *commands[2];
    commands[0] = new Command(object, &Object::dblState);
    commands[1] = new Command(object, &Object::incState);

    commands[0]->execute();
    object->show();
    Command::undo();
    object->show();
    Command::redo();
    object->show();
    commands[1]->execute();
    object->show();
}
