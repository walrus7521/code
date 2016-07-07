#include "bus.h"

using namespace std;

int dummy(void)
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
