#include <iostream>
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

class DriverFramework
{
protected:
    virtual int open()   = 0;
    virtual int close()  = 0;
    virtual int read()   = 0;
    virtual int write()  = 0;
    virtual int ioctl()  = 0;
    virtual int status() = 0;
};

class Driver : public DriverFramework
{
public:
    Driver(ParameterBlock *parm) : p(parm), rd(0), wr(0) {}
    ~Driver() { delete p; }
    int open()  { p->open();   return 0; }
    int close() { p->close();  return 0; }
    int read()  { p->read();   return 0; }
    int write() { p->write();  return 0; }
    int ioctl() { p->ioctl();  return 0; }
    int status(){ p->status(); return 0; }
private:
    ParameterBlock *p;
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

int main()
{
    ParameterBlock *p = new ParameterBlock();
    p->name   = "bfs";
    p->open   = my_open;
    p->close  = my_close;
    p->read   = my_read;
    p->write  = my_write;
    p->ioctl  = my_ioctl;
    p->status = my_status;
    Driver *d = new Driver(p);
    d->open();
    d->close();
    d->read();
    d->write();
    d->ioctl();
    d->status();
}

