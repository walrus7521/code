#include "dev.h"

using namespace std;

int my_open()   { std::cout << "my_open"   << std::endl; return 0; }
int my_close()  { std::cout << "my_close"  << std::endl; return 0; }
int my_read()   { std::cout << "my_read"   << std::endl; return 0; }
int my_write()  { std::cout << "my_write"  << std::endl; return 0; }
int my_ioctl()  { std::cout << "my_ioctl"  << std::endl; return 0; }
int my_status() { std::cout << "my_status" << std::endl; return 0; }

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

int dummy()
{
    return 0;
}

void test_classes()
{
    try {
        ParameterBlock link;
        link.init = dummy;
        link.open = dummy;
        link.close = dummy;
        link.read = dummy;
        link.write = dummy;
        link.ioctl = dummy;
        link.notify = notify;
        link.run = run;

        Class ahci(Bus::Ahci, link);
        Class usb(Bus::Usb, link);
        Class pci(Bus::Pci, link);

        // should be plug
        Bus::subscribe(&ahci);
        Bus::subscribe(&usb);
        Bus::subscribe(&pci);

        Bus::list();

        pci.start();
        usb.start();
        ahci.start();

        this_thread::sleep_for (chrono::seconds(3));
        cout << "setting bus_ready" << endl;
        bus_ready = true;

        this_thread::sleep_for (chrono::seconds(3));

        pci.stop();
        usb.stop();
        ahci.stop();

        Bus::signal();
        Bus::eject(&pci);
        Bus::list();
        Bus::eject(&usb);
        Bus::list();

    } catch (exception& ex) {
        cout << ex.what() << endl;
    }
}

int main()
{
    test_classes();
    return 0;

    map<string, int> menu; // = new map<string, int>();
#define HELP 1
#define QUIT 2
#define LIST 3
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

