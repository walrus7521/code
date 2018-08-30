#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <exception>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>

std::atomic<bool> bus_ready (false);

class Bus;

class Action
{
public:
    enum Type {
        Rescan, Reset
    };
    int action;
};

class Context
{
public:
    Bus *bus;
    Action action;
};

typedef void (*notification)(Context*);
typedef void (*runnable)(Context*);

class ParameterBlock
{
public:
    int vid;
    int did;
    std::string name;
    std::function<int(void)> init;
    std::function<int(void)> open;
    std::function<int(void)> close;
    std::function<int(void)> read;
    std::function<int(void)> write;
    std::function<int(void)> ioctl;
    std::function<int(void)> status;
    notification notify;
    runnable run;
};

class DeviceFramework
{
protected:
    virtual int open()   = 0;
    virtual int close()  = 0;
    virtual int read()   = 0;
    virtual int write()  = 0;
    virtual int ioctl()  = 0;
    virtual int status() = 0;
};

class Device : public DeviceFramework
{
public:
    Device(ParameterBlock *parm) : p(parm), rd(0), wr(0) {}
    ~Device() { delete p; }
    int open()  { p->open();   return 0; }
    int close() { p->close();  return 0; }
    int read()  { p->read();   return 0; }
    int write() { p->write();  return 0; }
    int ioctl() { p->ioctl();  return 0; }
    int status(){ p->status(); return 0; }
    ParameterBlock *p;
private:
    int buff[256*1024];
    int rd;
    int wr;
};

template <typename T> int my_open1(T t)  { std::cout << "my_open" << t << std::endl; return 0; }

class Bus
{
public:
    enum Type {
        Pci, Ohci, I2c, Can, Ahci, Usb, Firewire, Bluetooth
    };
    static std::string TypeDescriptor[];
public:
    Bus(bool throws_excpt, Type typ) : throws(throws_excpt), type(typ), cancel(false), ready(false) {
        ident = id++;
    }
    Bus(bool throws_excpt, Type typ, const ParameterBlock ilink) : throws(throws_excpt), type(typ), link(ilink), cancel(false), ready(false) {
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
    static void signal(Context*);
    ParameterBlock link;
    runnable runner;
    int ident;
    bool cancel;
    bool ready;
protected:
    bool throws;
    void error(const std::string& msg);
    Type type;
    static int id;
private:
    static std::vector<Bus*> members;
};

std::vector<Bus*> Bus::members;
std::string Bus::TypeDescriptor[] = {"Pci", "Ohci", "I2c", "Can", "Ahci", "Usb", "Firewire", "Bluetooth" };
int Bus::id = 1;

void polymorph(Bus *bus)
{
    bus->show();
}

void broadcast(Bus *bus, Context *ctx)
{
    ctx->bus->link.notify(ctx);
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
            std::cout << "found it: " << i << std::endl;
            break;
        }
        //polymorph(*bit);
    }
    members.erase(Bus::members.begin() + i);
}

int Bus::subscribe(Bus *bus) // plug (opposite of eject)
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

void Bus::signal(Context *ctx)
{
    for (std::vector<Bus*>::const_iterator bit = Bus::members.begin();
            bit != Bus::members.end(); ++bit) {
        if (*bit == ctx->bus) {
            broadcast(*bit, ctx);
        }
    }
}

class Class : public Bus
{
public:
    Class(Type typ) : Bus(true, typ) {}
    Class(Type typ, const ParameterBlock& ilink) : Bus(true, typ, ilink) {}
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
    std::cout << " stopping " << what() << std::endl;
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
    } catch (std::exception& ex) { // const cancelled_error&
        std::cout << "thread cancelled\n";
    }
    //std::cout << "cancelled? " << ctx->bus->cancel << std::endl;
    while (!ctx->bus->cancel) {
        // std::cout << "got cancal" << std::endl;
    }
    std::cout << "exiting " << ctx->bus->what() << " thread.." << std::endl;
}

// public 
// serialize devices to backing file
// enumerator
// get handle to device
// register app with device
// do IO
// make device file backed
class DeviceManager {
public:
    static std::list<Device*> instances;
    static std::map<int, Device*> instmap;
    static int count;
    static int UniqueId;
    static void ShowList();
    static void ShowMap();
    int GetCount() { return count; }
    void IncCount() { ++count; }
    Device* Create(ParameterBlock *p);
    void Destroy(); // destroy all Devices
};

// return a pointer to a heap object
Device *DeviceManager::Create(ParameterBlock *p) {
    p->vid = ++UniqueId;
    p->did = ++UniqueId;
    Device *d = new Device(p);
    instances.push_back(d);
    instmap[p->vid] = d;
    IncCount();
    return (d);
}

void DeviceManager::Destroy() {
    for (std::list<Device*>::iterator d = instances.begin();
            d != instances.end(); ++d) {
        std::cout << "erasing: " << (*d)->p->name << std::endl;
        instances.erase(d); //std::cout << (*p)->name << std::endl;
    }
}

void DeviceManager::ShowList()
{
    std::cout << "Number of listed devices: " << count << std::endl;
    for (std::list<Device*>::iterator d = instances.begin();
            d != instances.end(); ++d) {
        std::cout << "id: " << (*d)->p->vid << ": " << (*d)->p->name << std::endl;
    }
}

void DeviceManager::ShowMap()
{
    std::cout << "Number of mapped sessions: " << count << std::endl;
    for (std::map<int, Device*>::iterator mis = instmap.begin();
            mis != instmap.end(); ++mis) {
        std::cout << "id: " << mis->first << ": " << mis->second->p->name << std::endl;
    }
}

static DeviceManager dm; // the one and only factory
std::list<Device*> DeviceManager::instances; // list of Devices
std::map<int, Device*> DeviceManager::instmap; // list of Devices
int DeviceManager::count = 0;
int DeviceManager::UniqueId = 0;




