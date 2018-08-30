#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct {
    char *name;
    double age, height;
} person;

typedef struct keyval {
    char *key;
    void *value;
} keyval;

keyval *keyval_new(char *key, void *value);
keyval *keyval_copy(keyval const *in);
void keyval_free(keyval *in);
int keyval_matches(keyval const *in, char const *key);

typedef struct dictionary {
    keyval **pairs;
    int length;
} dictionary;

dictionary *dictionary_new(void);
dictionary *dictionary_copy(dictionary const *in);
void dictionary_free(dictionary *in);
void dictionary_add(dictionary *in, char *key, void *value);
void dictionary_find(dictionary const *in, char const *key);

int main()
{
    person sinead = {.name="Sinead", .age=28, .height=173};

    printf("name: %s, age %.0f, height %.0f\n", sinead.name, sinead.age, sinead.height);
    return 0;
}

keyval *keyval_new(char *key, void *value) {
    keyval *out = (keyval *) malloc(sizeof(keyval));
    *out = (keyval){.key = key, .value = value};
    return out;
}

keyval *keyval_copy(keyval const *in) {
    keyval *out = (keyval *) malloc(sizeof(keyval));
    *out = *in;
    return out;
}

void keyval_free(keyval *in) {
    free(in);
}

int keyval_matches(keyval const *in, char const *key) {
    return !strcasecmp(in->key, key);
}

dictionary *dictionary_new(void) {
    dictionary *out = (dictionary *) malloc(sizeof(dictionary));
    return out;
}

dictionary *dictionary_copy(dictionary const *in) {
    dictionary *out = (dictionary *) malloc(sizeof(dictionary));
    *out = *in;
    return out;
}

void dictionary_free(dictionary *in) {
    free(in);
}

void dictionary_add(dictionary *in, char *key, void *value) {
}

void dictionary_find(dictionary const *in, char const *key) {
}


