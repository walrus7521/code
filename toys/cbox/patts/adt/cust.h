typedef struct Customer* CustomerPtr;
typedef struct Address Address;

CustomerPtr createCustomer(const char *name, const Address* address);
void destroyCustomer(CustomerPtr customer);

typedef struct Address
{
    int number;
    char street[16];
    char city[16];
    char state[2];
} Address;


