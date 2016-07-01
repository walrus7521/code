#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <exception>

using namespace std;

typedef void (*notification)(int);

class Interface
{
public:
    int (*init)(void);
    int (*open)(void);
    int (*close)(void);
    int (*read)(void);
    int (*write)(void);
    int (*ioctl)(void);
    int (*show)(void);
    notification notify;
};

class Bus
{
public:
    enum Type {
        Pci, Ohci, I2C, CAN, Ahci, Usb, Firewire, Bluetooth
    };
    static string TypeDescriptor[];
        
public:
    Bus(bool throws_excpt, Type typ) : throws(throws_excpt), type(typ) { ident = id++; }
    Bus(bool throws_excpt, Type typ, const Interface ilink) : throws(throws_excpt), type(typ), link(ilink) { ident = id++; }
    ~Bus(){}
    virtual void show() = 0;
    static void eject(Bus*);
    string what() { return TypeDescriptor[type]; }
    static int subscribe(Bus*);
    static void list();
    static void signal();
    Interface link;
    int ident;

protected:
    bool throws;
    void error(const std::string& message);
    Type type;
    static int id;
private:
    static vector<Bus*> members;
};

void polymorph(Bus *bus)
{
    bus->show();
}

void broadcast(Bus *bus)
{
    bus->link.notify(bus->ident);
}

void Bus::error(const std::string& message)
{
    if (throws) {
        throw message.c_str();
    } else {
        std::cout << message << std::endl;
    }
}

void Bus::eject(Bus *bus)
{
    cout << "Bus::ejecting(): " << bus->what() << " id: " << bus->ident << endl;
    int i = 0;
    for (vector<Bus*>::const_iterator bit = Bus::members.begin();
        bit != Bus::members.end(); ++bit, ++i) {
        if (*bit == bus) {
            cout << "found it: " << i << endl;
            break;
        }
        //polymorph(*bit);
    }
    members.erase(Bus::members.begin() + i);
}

int Bus::subscribe(Bus *bus)
{
    members.push_back(bus);
    return 0;
}

void Bus::list()
{
    for (vector<Bus*>::const_iterator bit = Bus::members.begin();
        bit != Bus::members.end(); ++bit) {
        polymorph(*bit);
    }
}

void Bus::signal()
{
    for (vector<Bus*>::const_iterator bit = Bus::members.begin();
        bit != Bus::members.end(); ++bit) {
        broadcast(*bit);
    }
}

vector<Bus*> Bus::members;
string Bus::TypeDescriptor[] = { "Pci", "Ohci", "I2C", "CAN", "Ahci", "Usb", "Firewire", "Bluetooth" };
int Bus::id = 1;


class Class : public Bus
{
public:
    Class(Type typ) : Bus(true, typ) {}
    Class(Type typ, const Interface& ilink) : Bus(true, typ, ilink) {}
    ~Class(){}
    void show();
};

void Class::show()
{
    cout << "Class::show() - type: " << what() << endl;
}

void notify(int event)
{
    cout << "got notify: " << event << endl;
}

int dummy() { return 0; }

int main()
{
    Interface link;
    link.init   = dummy;
    link.open   = dummy;
    link.close  = dummy;
    link.read   = dummy;
    link.write  = dummy;
    link.ioctl  = dummy;
    link.show   = dummy;
    link.notify = notify;

    Class ahci(Bus::Ahci, link);
    Class usb(Bus::Usb, link);
    Class pci(Bus::Pci, link);
    
    Bus::subscribe(&ahci);
    Bus::subscribe(&usb);
    Bus::subscribe(&pci);

    Bus::list();

    Bus::signal();
    Bus::eject(&pci);
    Bus::list();
    Bus::eject(&usb);
    Bus::list();

}
