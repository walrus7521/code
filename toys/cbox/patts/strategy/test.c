#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    Order order;
    CustomerPtr bronze  = createBronzeCustomer(NULL, NULL);
    CustomerPtr silver  = createSilverCustomer(NULL, NULL);
    CustomerPtr gold    = createGoldCustomer(NULL, NULL);
    placeOrder(bronze, &order);
    placeOrder(silver, &order);
    placeOrder(gold, &order);
    changePriceCategory(bronze, silverPriceStrategy);
    placeOrder(bronze, &order);
    return 0;
}

