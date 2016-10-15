#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cust.h"


int main()
{
    CustomerPtr cust;
    Address addr;
    addr.number = 7521;
    strcpy(addr.street, "Shaw Lane\0");
    strcpy(addr.city, "Gig Harbor\0");
    strcpy(addr.state, "Wa\0");

    cust = createCustomer("dude\0", &addr);
    addOrder(cust, 42);
    addOrder(cust, 43);
    addOrder(cust, 44);
    addOrder(cust, 45);
    show(cust);
    destroyCustomer(cust);
    return 0;
}
