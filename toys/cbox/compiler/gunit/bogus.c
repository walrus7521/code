#include "bogus.h"

void BOGUS_Initialize(int size, BOGUS_STRUCT * bogus)
{
    bogus->size = size;
    bogus->head   = 42U;
    bogus->tail   = 0U;
    bogus->data_avail = 0U;
    bogus->status = BOGUS_SUCCESS;
}


