#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <stdint.h>
#include <errno.h>

#define VECTOR_OK            0
#define VECTOR_NULL_ERROR    1
#define VECTOR_SIZE_ERROR    2
#define VECTOR_ALLOC_ERROR   3

#define LINE_SIZE 256
struct vector {
    char **data;
    size_t size;
};

int create_vector(struct vector *vc, size_t num) {

    if (vc == NULL) {
        return VECTOR_NULL_ERROR;
    }

    vc->data = NULL;
    vc->size = 0;

    /* check for integer and SIZE_MAX overflow */
    if (num == 0 || SIZE_MAX / num < sizeof(int)) {
        errno = ENOMEM;
        return VECTOR_SIZE_ERROR;
    }

    vc->data = calloc(num, LINE_SIZE);

    /* calloc faild */
    if (vc->data == NULL) {
        return VECTOR_ALLOC_ERROR;
    }

    vc->size = num * LINE_SIZE;
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
    for (i = 0; i < vc->size/LINE_SIZE; i++) {
        printf("vc[%d] = %s\n", i, vc->data[i]);
    }
}

static unsigned int get_current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(int argc, char** argv)
{
    struct vector vec;
    int i, j;
    unsigned int elapsed_time = get_current_time();
    int rc = create_vector(&vec, 16);
    elapsed_time = get_current_time() - elapsed_time;
    printf("elapsed time %dms\n", elapsed_time);
    FILE* r = fopen(argv[1], "rt");
    if(r) {
        int nr_lines = 0, nr_bytes = 0;
        size_t len = 1024;
        char* file = (char*)malloc(len);
        ssize_t read;
        nr_lines = 0;
        while((read = getline(&vec.data[nr_lines], &len, r)) != -1)
        {
            nr_lines++;
            nr_bytes += read;
            printf("%d: line: %s", nr_bytes, file);
        }
        printf("\nnr lines: %d, nr_bytes %d\n", nr_lines, nr_bytes);
        show_vector(&vec);
        free(file);
        fclose(r);
    }
    return 0;
}


