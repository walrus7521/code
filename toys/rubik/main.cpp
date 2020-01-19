#include "utils.h"

int main()
{
    msi mapper;

    for (auto i : {1,3,5,7,9}) {
        mapper[STR(i)] = i;
    }

    for (auto& kv : mapper) {
        printf("%s => %d\n", CSTR(kv.first), kv.second);
    }    

    return 0;
}

