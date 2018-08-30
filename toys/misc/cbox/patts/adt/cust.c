#include "cust.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer
{
    char name[32];
    Address address;
    int noOfOrders;
    int orders[42];
} Customer;

CustomerPtr createCustomer(const char *name, const Address* address)
{
    CustomerPtr customer = malloc(sizeof(*customer));
    if (customer)
    {
        strcpy(customer->name, name);
        memcpy((char *) &customer->address, (char *) address, sizeof(Address));
    }
    return customer;
}

void addOrder(CustomerPtr cust, int order)
{
    //struct Customer *cust = (struct Customer *) customer;
    cust->orders[cust->noOfOrders++] = order;
}

void show(CustomerPtr customer)
{
    int i;
    printf("name  : %s\n", customer->name);
    printf("addr  : %d\n", customer->address.number);
    printf("      : %s\n", customer->address.street);
    printf("      : %s\n", customer->address.city);
    printf("      : %s\n", customer->address.state);
    printf("orders: %d\n", customer->noOfOrders);
    for (i = 0; i < customer->noOfOrders; i++) {
        printf("order[%d] = %d\n", i, customer->orders[i]);
    }
}

void destroyCustomer(CustomerPtr customer)
{
    free(customer);
    customer = NULL;
}

