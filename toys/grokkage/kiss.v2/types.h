#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

typedef enum { OK, ERROR } status;

typedef struct {
    double real;
    double imaginary;
} complex;

typedef void * generic_ptr;


#endif // TYPES_H
