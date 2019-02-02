#include "common.h"
#include "thread.h"


static MUTEX_TYPE *mutex_buf = NULL;

// static locking callbacks
static void locking_function(int mode, int n, const char *file, int line)
{
    if (mode & CRYPTO_LOCK) {
        MUTEX_LOCK(mutex_buf[n]);
    } else {
        MUTEX_UNLOCK(mutex_buf[n]);
    }
}

static unsigned long id_function(void)
{
    return ((unsigned long) THREAD_ID);
}

// dynamic locking callbacks
struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{
    struct CRYPTO_dynlock_value *value;
    value = (struct CRYPTO_dynlock_value *) malloc(sizeof(
                                        struct CRYPTO_dynlock_value));
    if (!value) return NULL;
    MUTEX_SETUP(value->mutex);
    return value;
}

void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l,
                            const char *file, int line)
{
    if (mode & CRYPTO_LOCK) MUTEX_LOCK(l->mutex);
    else                    MUTEX_UNLOCK(l->mutex);
}

void dyn_destroy_function(struct CRYPTO_dynlock_value *l,
                            const char *file, int line)
{
    MUTEX_CLEANUP(l->mutex);
    free(l);
}

int THREAD_setup(void)
{
    int i;

    mutex_buf = (MUTEX_TYPE *) malloc(CRYPTO_num_locks() * sizeof(MUTEX_TYPE));
    if (!mutex_buf) {
        return 0;
    }

    for (i = 0; i < CRYPTO_num_locks(); i++) {
        MUTEX_SETUP(mutex_buf[i]);
    }

    // static setup
    CRYPTO_set_id_callback(id_function);
    CRYPTO_set_locking_callback(locking_function);
    // dynamic setup
    CRYPTO_set_dynlock_create_callback(dyn_create_function);
    CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
    CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);

    return 1;
}

int THREAD_cleanup(void)
{
    int i;

    if (!mutex_buf) return 0;

    // static setup
    CRYPTO_set_id_callback(NULL);
    CRYPTO_set_locking_callback(NULL);
    // dynamic setup
    CRYPTO_set_dynlock_create_callback(NULL);
    CRYPTO_set_dynlock_lock_callback(NULL);
    CRYPTO_set_dynlock_destroy_callback(NULL);

    for (i = 0; i < CRYPTO_num_locks(); i++) {
        MUTEX_CLEANUP(mutex_buf[i]);
    }

    free(mutex_buf);
    mutex_buf = NULL;

    return 1;

}

void print_errors(void)
{
    int flags, line;
    const char *data, *file;
    unsigned long code;

    code = ERR_get_error_line_data(&file, &line, &data, &flags);
    while (code) {
        if (data && (flags & ERR_TXT_STRING)) {
            printf("error data: %s\n", data);
        }
        code = ERR_get_error_line_data(&file, &line, &data, &flags);
    }
}

