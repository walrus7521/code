#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <exception>
#include <thread>
#include <chrono>
#include <atomic>         // std::atomic


using namespace std;

atomic<bool> bus_ready (false);

class Bus;

class Context
{
public:
    Bus *bus;
};

typedef void (*notification)(int);
typedef void (*runnable)(Context*);

class Interface
{
public:
    int (*init)(void);
    int (*open)(void);
    int (*close)(void);
    int (*read)(void);
    int (*write)(void);
    int (*ioctl)(void);
    notification notify;
    runnable run;
};

class Bus
{
public:
    enum Type {
        Pci, Ohci, I2C, CAN, Ahci, Usb, Firewire, Bluetooth
    };
    static string TypeDescriptor[];
        
public:
    Bus(bool throws_excpt, Type typ) : throws(throws_excpt), type(typ), cancel(false), ready(false) { 
        ident = id++;
    }
    Bus(bool throws_excpt, Type typ, const Interface ilink) : throws(throws_excpt), type(typ), link(ilink), cancel(false), ready(false) { 
        ident = id++; 
        runner = ilink.run;
    }
    ~Bus(){}
    virtual void show() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    static void eject(Bus*);
    string what() { return TypeDescriptor[type]; }
    static int subscribe(Bus*);
    static void list();
    static void signal();
    Interface link;
    runnable runner;
    int ident;
    bool cancel;
    bool ready;

protected:
    bool throws;
    void error(const string& message);
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

void Bus::error(const string& message)
{
    if (throws) {
        throw message.c_str();
    } else {
        cout << message << endl;
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
    void start();
    void stop();
    thread run_thrd;
};

void Class::start()
{
    cout << "starting " << what() << endl;
    cancel = false;
    ready = false;
    Context *ctx = new Context();
    ctx->bus = this;
    this->run_thrd = thread(link.run, ctx);
}

void Class::stop()
{
    cout << "stopping " << what() << endl;
    cancel = true;
    this->run_thrd.join();
}

void Class::show()
{
    cout << "Class::show() - type: " << what() << endl;
}

void notify(int event)
{
    cout << "got notify: " << event << endl;
}

void run(Context *ctx)
{
    cout << "thread started\n";
    try {
        while (!bus_ready) {
            this_thread::yield();
        }
    } catch (exception& ex) { //const cancelled_error&) {
        cout << "thread cancelled\n";
    }
    //cout << "cancelled? " << ctx->bus->cancel << endl;
    while (!ctx->bus->cancel) {
        //cout << "got cancel" << endl;
    }
    cout << "exiting run..." << endl;
}

int dummy() 
{ 
    return 0; 
}

int main()
{
    try {
        Interface link;

        link.init   = dummy;
        link.open   = dummy;
        link.close  = dummy;
        link.read   = dummy;
        link.write  = dummy;
        link.ioctl  = dummy;
        link.notify = notify;
        link.run    = run;

        Class ahci(Bus::Ahci, link);
        Class usb(Bus::Usb, link);
        Class pci(Bus::Pci, link);
    
        Bus::subscribe(&ahci);
        Bus::subscribe(&usb);
        Bus::subscribe(&pci);

        pci.start();
        usb.start();
        ahci.start();
    
        this_thread::sleep_for (chrono::seconds(3));
        cout << "setting bus_ready" << endl;
        bus_ready = true;
    
        Bus::list();

        this_thread::sleep_for (chrono::seconds(3));

        cout << "stopping buses" << endl;
        pci.stop();
        usb.stop();
        ahci.stop();

        Bus::signal();
        Bus::eject(&pci);
        Bus::list();
        Bus::eject(&usb);
        Bus::list();

    } catch (exception& ex) {
        cout << "dude..." << endl;
        cout << ex.what() << endl;
    }


}
