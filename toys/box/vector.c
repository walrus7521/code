#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <errno.h>

#define VECTOR_OK            0
#define VECTOR_NULL_ERROR    1
#define VECTOR_SIZE_ERROR    2
#define VECTOR_ALLOC_ERROR   3

struct vector {
    int *data;
    size_t size;
};

int create_vector(struct vector *vc, size_t num) {

    if (vc == NULL) {
        return VECTOR_NULL_ERROR;
    }

    vc->data = 0;
    vc->size = 0;

    /* check for integer and SIZE_MAX overflow */
    if (num == 0 || SIZE_MAX / num < sizeof(int)) {
        errno = ENOMEM;
        return VECTOR_SIZE_ERROR;
    }

    vc->data = calloc(num, sizeof(int));

    /* calloc faild */
    if (vc->data == NULL) {
        return VECTOR_ALLOC_ERROR;
    }

    vc->size = num * sizeof(int);
    return VECTOR_OK;
}

int grow_vector(struct vector *vc) {

    void *newptr = 0;
    size_t newsize;

    if (vc == NULL) {
        return VECTOR_NULL_ERROR;
    }


    /* check for integer and SIZE_MAX overflow */
    if (vc->size == 0 || SIZE_MAX / 2 < vc->size) {
        errno = ENOMEM;
        return VECTOR_SIZE_ERROR;
    }

    newsize = vc->size * 2;

    newptr = realloc(vc->data, newsize);

    /* realloc faild; vector stays intact size was not changed */
    if (newptr == NULL) {
        return VECTOR_ALLOC_ERROR;
    }

    /* upon success; update new address and size */
    vc->data = newptr;
    vc->size = newsize;
    return VECTOR_OK;
}

void show_vector(struct vector *vc) {
    int i;
    for (i = 0; i < vc->size/sizeof(int); i++) {
        printf("vc[%d] = %d\n", i, vc->data[i]);
    }
}

int main(int argc, char *argv[])
{
    struct vector vec;
    int rc = create_vector(&vec, 16);
    int i;
    if (rc != VECTOR_OK) {
        perror("bad vector");
        return -1;
    }
    for (i = 0; i < 16; i++) {
        vec.data[i] = i;
    }
    show_vector(&vec);
    grow_vector(&vec);
    for (i = 16; i < 32; i++) {
        vec.data[i] = i;
    }
    show_vector(&vec);
    return 0;
}
