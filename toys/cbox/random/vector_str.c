#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#define VECTOR_OK            0
#define VECTOR_NULL_ERROR    1
#define VECTOR_SIZE_ERROR    2
#define VECTOR_ALLOC_ERROR   3

#define LINE_SIZE 256
struct vector {
    char **data;
    int curr;
    size_t size;
};

int create_vector(struct vector *vc, size_t num) {

    if (vc == NULL) {
        return VECTOR_NULL_ERROR;
    }

    vc->data = NULL;
    vc->size = 0;
    vc->curr = 0;

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

int add(struct vector *vc, char *data)
{
    int idx = vc->curr;
    if (idx >= vc->size) grow_vector(vc);
    vc->data[idx] = strdup(data);
    printf("adding vec[%02d] = %s\n", idx, vc->data[idx]);
    vc->curr++;
    return 0;
}

void show_vector(struct vector *vc) {
    int i;
    
    for (i = 0; i < vc->curr; i++) {
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
        char line[256];
        char *pline = line;
        memset(line, 256, '\0');
        nr_lines = 0;
        while((read = getline(&pline, &len, r)) != -1) {
            // strip carriage return
            line[read-1] = '\0';
            //printf("%d: line: %s", (int) read, pline);
            char *token = strtok(line, " ");
            while (token != NULL) {
                add(&vec, token);
                //printf("%s\n", token);
                token = strtok(NULL, " ");
            }
            nr_lines++;
            nr_bytes += read;
        }
        printf("\nnr lines: %d, nr_bytes %d\n", nr_lines, nr_bytes);
        show_vector(&vec);
        free(file);
        fclose(r);
    }
    return 0;
}


