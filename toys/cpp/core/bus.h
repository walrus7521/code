#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <exception>
#include <thread>
#include <chrono>
#include <atomic>


std::atomic<bool> bus_ready (false);

class Bus;

class Context
{
public:
    Bus *bus;
};

typedef void (*notification)(Context*);
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
    static std::string TypeDescriptor[];
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
    std::string what() { return TypeDescriptor[type]; }
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
    void error(const std::string& message);
    Type type;
    static int id;
private:
    static std::vector<Bus*> members;
};

void polymorph(Bus *bus)
{
    bus->show();
}

void broadcast(Bus *bus)
{
    Context *ctx = new Context();
    ctx->bus = bus;
    bus->link.notify(ctx);
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
    std::cout << "Bus::ejecting(): " << bus->what() << " id: " << bus->ident << std::endl;
    int i = 0;
    for (std::vector<Bus*>::const_iterator bit = Bus::members.begin();
        bit != Bus::members.end(); ++bit, ++i) {
        if (*bit == bus) {
            //std::cout << "found it: " << i << std::endl;
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
    for (std::vector<Bus*>::const_iterator bit = Bus::members.begin();
        bit != Bus::members.end(); ++bit) {
        polymorph(*bit);
    }
}

void Bus::signal()
{
    for (std::vector<Bus*>::const_iterator bit = Bus::members.begin();
        bit != Bus::members.end(); ++bit) {
        broadcast(*bit);
    }
}

std::vector<Bus*> Bus::members;
std::string Bus::TypeDescriptor[] = { "Pci", "Ohci", "I2C", "CAN", "Ahci", "Usb", "Firewire", "Bluetooth" };
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
    std::thread run_thrd;
};

void Class::start()
{
    std::cout << "starting " << what() << std::endl;
    cancel = false;
    ready = false;
    Context *ctx = new Context();
    ctx->bus = this;
    this->run_thrd = std::thread(link.run, ctx);
}

void Class::stop()
{
    std::cout << "stopping " << what() << std::endl;
    cancel = true;
    this->run_thrd.join();
}

void Class::show()
{
    std::cout << "Class::show() - type: " << what() << std::endl;
}

void notify(Context *ctx)
{
    std::cout << "got notify: " << ctx->bus->what() << std::endl;
}

void run(Context *ctx)
{
    std::cout << "thread started\n";
    try {
        while (!bus_ready) {
            std::this_thread::yield();
        }
    } catch (std::exception& ex) { //const cancelled_error&) {
        std::cout << "thread cancelled\n";
    }
    //std::cout << "cancelled? " << ctx->bus->cancel << std::endl;
    while (!ctx->bus->cancel) {
        //std::cout << "got cancel" << std::endl;
    }
    std::cout << "exiting " << ctx->bus->what() << " thread.." << std::endl;
}

