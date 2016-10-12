#ifndef CUST_H
#define CUST_H

typedef struct Customer* CustomerPtr;

typedef struct Address
{
    int number;
    char street[16];
    char city[16];
    char state[2];
} Address;

CustomerPtr createCustomer(const char *name, const Address* address);
void destroyCustomer(CustomerPtr customer);
void addOrder(CustomerPtr cust, int order);
void show(CustomerPtr customer);

#endif // CUST_H

