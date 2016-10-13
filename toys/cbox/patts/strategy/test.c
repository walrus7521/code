#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Customer.h"
#include "CustomerStrategy.h"
#include "CustomerCategories.h"

static CustomerPtr createBronzeCustomer(const char* name, const Address* address)
{
    return createCustomer(name, address, bronzePriceStrategy);
}

static CustomerPtr createSilverCustomer(const char* name, const Address* address)
{
    return createCustomer(name, address, silverPriceStrategy);
}

static CustomerPtr createGoldCustomer(const char* name, const Address* address)
{
    return createCustomer(name, address, goldPriceStrategy);
}

void changePriceCategory(CustomerPtr customer, CustomerPriceStrategy newPriceStrategy)
{
    assert(NULL != customer);
    customer->priceStrategy = newPriceStrategy;
}


int main()
{
    Order order;
    CustomerPtr bronze  = createBronzeCustomer(NULL, NULL);
    CustomerPtr silver  = createSilverCustomer(NULL, NULL);
    CustomerPtr gold    = createGoldCustomer(NULL, NULL);
    placeOrder(bronze, &order);
    placeOrder(silver, &order);
    placeOrder(gold, &order);
    return 0;
}

