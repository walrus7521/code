#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

class ParameterBlock
{
public:
    int id;
    string name;
    int (*open)();
    int (*close)();
    int (*read)();
    int (*write)();
    int (*ioctl)();
    int (*status)();
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

int my_open()   { cout << "my_open"   << endl; return 0; }
int my_close()  { cout << "my_close"  << endl; return 0; }
int my_read()   { cout << "my_read"   << endl; return 0; }
int my_write()  { cout << "my_write"  << endl; return 0; }
int my_ioctl()  { cout << "my_ioctl"  << endl; return 0; }
int my_status() { cout << "my_status" << endl; return 0; }

// public 
// enumerator
// get handle to device
// register app with device
// do IO
// make device file backed
class DeviceManager {
public:
    static list<Device*> instances;
    static map<int, Device*> instmap;
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
    p->id = ++UniqueId;
    Device *d = new Device(p);
    instances.push_back(d);
    instmap[p->id] = d;
    IncCount();
    return (d);
}

void DeviceManager::Destroy() {
    for (list<Device*>::iterator d = instances.begin();
            d != instances.end(); ++d) {
        cout << "erasing: " << (*d)->p->name << endl;
        instances.erase(d); //cout << (*p)->name << endl;
    }
}

void DeviceManager::ShowList()
{
    cout << "Number of listed devices: " << count << endl;
    for (list<Device*>::iterator d = instances.begin();
            d != instances.end(); ++d) {
        cout << "id: " << (*d)->p->id << ": " << (*d)->p->name << endl;
    }
}

void DeviceManager::ShowMap()
{
    cout << "Number of mapped sessions: " << count << endl;
    for (map<int, Device*>::iterator mis = instmap.begin();
            mis != instmap.end(); ++mis) {
        cout << "id: " << mis->first << ": " << mis->second->p->name << endl;
    }
}

static DeviceManager dm; // the one and only factory
list<Device*> DeviceManager::instances; // list of Devices
map<int, Device*> DeviceManager::instmap; // list of Devices
int DeviceManager::count = 0;
int DeviceManager::UniqueId = 0;

void create_devs()
{
    ParameterBlock *p;
    Device *dev;

    p = new ParameterBlock();
    p->name   = "bfs";
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "usb";
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "mouse";
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "kbd";
    dev = dm.Create(p);

    p = new ParameterBlock();
    p->name   = "disk";
    dev = dm.Create(p);

    p->open   = my_open;
    p->close  = my_close;
    p->read   = my_read;
    p->write  = my_write;
    p->ioctl  = my_ioctl;
    p->status = my_status;
#if 0
    dev->open();
    dev->close();
    dev->read();
    dev->write();
    dev->ioctl();
    dev->status();
#endif
}

int main()
{
    create_devs();
    dm.ShowList();
}

