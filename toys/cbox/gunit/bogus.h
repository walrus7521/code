#ifndef BOGUS_H
#define BOGUS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <limits.h>
#include <string.h>

#define BOGUS_SUCCESS   (0x00)

typedef struct
{
    int dude;       
    char sup;  
} BOGUS_STRUCT;


void BOGUS_Initialize(int size, BOGUS_STRUCT * bogus);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BOGUS_H
