#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <functional>

class ParameterBlock
{
public:
    int vid;
    int did;
    std::string name;
    std::function<int(void)> open;
    std::function<int(void)> close;
    std::function<int(void)> read;
    std::function<int(void)> write;
    std::function<int(void)> ioctl;
    std::function<int(void)> status;
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
int my_open()   { std::cout << "my_open"   << std::endl; return 0; }
int my_close()  { std::cout << "my_close"  << std::endl; return 0; }
int my_read()   { std::cout << "my_read"   << std::endl; return 0; }
int my_write()  { std::cout << "my_write"  << std::endl; return 0; }
int my_ioctl()  { std::cout << "my_ioctl"  << std::endl; return 0; }
int my_status() { std::cout << "my_status" << std::endl; return 0; }

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

void overload(ParameterBlock *p)
{
    p->open   = my_open;
    p->close  = my_close;
    p->read   = my_read;
    p->write  = my_write;
    p->ioctl  = my_ioctl;
    p->status = my_status;
}

void create_devs()
{
    ParameterBlock *p;
    Device *dev;

    p = new ParameterBlock();
    p->name   = "bfs";
    overload(p);
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "usb";
    overload(p);
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "mouse";
    overload(p);
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "kbd";
    overload(p);
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "disk";
    overload(p);
    dev = dm.Create(p);
}
