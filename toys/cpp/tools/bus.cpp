#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <exception>
#include <thread>
#include <chrono>

using namespace std;


typedef void (*notification)(int);
typedef void (*runnable)(int);

class Bus;

class Context
{
public:
    Bus *bus;
};

typedef void (*runnable2)(Context*);

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
    runnable run;
    runnable2 run2;
};

class Bus
{
public:
    enum Type {
        Pci, Ohci, I2C, CAN, Ahci, Usb, Firewire, Bluetooth
    };
    static string TypeDescriptor[];
        
public:
    Bus(bool throws_excpt, Type typ) : throws(throws_excpt), type(typ) { 
        ident = id++;
    }
    Bus(bool throws_excpt, Type typ, const Interface ilink) : throws(throws_excpt), type(typ), link(ilink) { 
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
    Class(Type typ) : Bus(true, typ), cancel(false) {}
    Class(Type typ, const Interface& ilink) : Bus(true, typ, ilink), cancel(false) {}
    ~Class(){}
    void show();
    void start();
    void stop();
    bool cancel;
};

void Class::start()
{
    cout << "starting " << what() << endl;
    // need pthreads maybe .. c++ threads are non-interruptible
    //std::thread start(link.run, ident);
    //start.join();
    Context ctx;
    ctx.bus = this;
    std::thread start(link.run2, &ctx);
    start.join();
}

void Class::stop()
{
    cout << "stopping " << what() << endl;
    cancel = true;
}

void Class::show()
{
    cout << "Class::show() - type: " << what() << endl;
}

void notify(int event)
{
    cout << "got notify: " << event << endl;
}

//void run(Bus *bus)
void run2(Context *ctx)
{
    std::cout << "thread started\n";
    try {
        while (true) {
            //std::sleep(2); //cpoint_.wait(std::chrono::seconds(1));
            std::this_thread::sleep_for (std::chrono::seconds(1));
            //std::this_thread::yield();
            if (ctx->bus->cancel) {
                cout << "got cancel" << endl;
                return;
            }
            cout << "no got cancel" << endl;
        }
    } catch (exception& ex) { //const cancelled_error&) {
        std::cout << "thread cancelled\n";
    }
    cout << "and we're done" << endl;
}

void run(int tid)
{
    cout << "run called: " << tid << endl;
    std::cout << "thread started\n";
    try {
        while (true) {
            //std::sleep(2); //cpoint_.wait(std::chrono::seconds(1));
            std::this_thread::sleep_for (std::chrono::seconds(1));
            //if (cancel) {
            //    return;
            //}
        }
    } catch (exception& ex) { //const cancelled_error&) {
        std::cout << "thread cancelled\n";
    }
    //while (true) ;
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
    link.run    = run;
    link.run2   = run2;

    Class ahci(Bus::Ahci, link);
    Class usb(Bus::Usb, link);
    Class pci(Bus::Pci, link);
    
    Bus::subscribe(&ahci);
    Bus::subscribe(&usb);
    Bus::subscribe(&pci);

    pci.start();
    usb.start();
    ahci.start();

    Bus::list();

    pci.stop();
    usb.stop();
    ahci.stop();

    Bus::signal();
    Bus::eject(&pci);
    Bus::list();
    Bus::eject(&usb);
    Bus::list();

}
