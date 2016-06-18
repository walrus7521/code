#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <boost/archive/xml_oarchive.hpp>

using namespace std;
using namespace boost::archive;

class ParameterBlock
{
public:
    int vid;
    int did;
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
// serialize devices to backing file
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
    p->vid = ++UniqueId;
    p->did = ++UniqueId;
    Device *d = new Device(p);
    instances.push_back(d);
    instmap[p->vid] = d;
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
        cout << "id: " << (*d)->p->vid << ": " << (*d)->p->name << endl;
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

#define HELP 1
#define QUIT 2
#define LIST 3

void test()
{
    ofstream fout("devices.xml");
    xml_oarchive oa(fout);
}

int main()
{
    map<string, int> menu; // = new map<string, int>();
    menu["help"] = HELP;
    menu["quit"] = QUIT;
    menu["list"] = LIST;
    create_devs();
    while (1) {
        string cmd;
        int cmdid;
        cout << "$ ";
        cin >> cmd;
        for(int i = 0; i < cmd.length(); ++i) cmd[i] = tolower(cmd[i]);
        cmdid = menu[cmd];
        switch (cmdid) {
            case HELP: 
                cout << "Helping you" << endl;
                break;
            case QUIT:
                return 0;
            case LIST:
                dm.ShowList();
                break;
            default:
                break;
        }
    }
}

