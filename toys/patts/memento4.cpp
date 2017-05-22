#include <iostream>
#include <string>
#include <vector>

using namespace std;

// wikibooks: https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns/Behavioral_Patterns#Memento


class Memento;

class Object {
private:
    int value;
    string name;
public:
    void doubleValue() { value *= 2; }
    void incrementValue() { value++; }
    Object(int v, string nm): value(v), name(nm) {}
    Memento* createMemento() const;
    void reinstateMemento(Memento *mem);
};

class Memento {
private:
    Object object;
public:
    Memento(const Object& obj): object(obj) {}
    Object snapshot() const {return object;}
};

Memento* Object::createMemento() const {
    return new Memento(*this);
}

void Object::reinstateMemento(Memento* mem) {
    *this = mem->snapshot();
}

class Command {
private:
    Object* receiver;
    static std::vector<Command*> commandList;
    static std::vector<Memento*> mementoList;
    static int numCommands;
    static int maxCommands;    
public:
    virtual void execute() {
    }
    static void undo() {
    }
    static void redo() {
    }
    
    
};

std::vector<Command*> Command::commandList;
std::vector<Memento*> Command::mementoList;
int Command::numCommands = 0;
int Command::maxCommands = 0;

int main() {
    Object *object = new Object(42, "dude");
    // issue commands on object
    // and undo/redo them
    Command *commands[2];
    commands[0] = new Command(object, &Object::doubleValue);
    commands[1] = new Command(object, &Object::incrementValue);

}
