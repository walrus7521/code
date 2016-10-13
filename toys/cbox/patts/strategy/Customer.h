#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "CustomerStrategy.h"

typedef struct Order Order;
struct Order
{
    double shipping;
    double amount;
};

typedef struct Address Address;
struct Address
{
    int number;
};

typedef struct Customer* CustomerPtr;

CustomerPtr createCustomer(const char* name, const Address* address, CustomerPriceStrategy priceStrategy);

void placeOrder(struct Customer* customer, const Order* order);

#endif // CUSTOMER_H
