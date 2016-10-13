#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Customer.h"
#include "CustomerStrategy.h"

/* Other include files omitted... */

struct Customer
{
    //const char* name;
    //Address address;
    //List orders;
    /* Bind the strategy to Customer: */
    CustomerPriceStrategy priceStrategy;
};

void placeOrder(struct Customer* customer, const Order* order)
{
    double totalAmount = customer->priceStrategy(order->amount, order->shipping);
    printf("amount: %lf\n", totalAmount);
/* More code to process the order... */
}

CustomerPtr createCustomer(const char* name, const Address* address, CustomerPriceStrategy priceStrategy)
{
    CustomerPtr customer = malloc(sizeof *customer);

    if(NULL != customer)
    {
        /* Bind the initial strategy supplied by the client. */
        customer->priceStrategy = priceStrategy;
        /* Initialize the other attributes of the customer here. */
    }
    return customer;
}

void changePriceCategory(CustomerPtr customer, CustomerPriceStrategy newPriceStrategy)
{
    assert(NULL != customer);
    customer->priceStrategy = newPriceStrategy;
}


