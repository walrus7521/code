#include <stdio.h>
#include <stdlib.h>

typedef enum {
    DISK_TYPE,
    TAPE_TYPE,
    DVD_TYPE,
    STORAGE_TYPES_NUM_OF
} STORAGE_TYPES;

typedef struct _storage {
   struct _storage *(*clone) (struct _storage * stor);
   void (*backup) (void);
   STORAGE_TYPES type;
} Storage;

typedef struct _factory {
   Storage* (*make_storage) ();
   Storage* s_prototypes[STORAGE_TYPES_NUM_OF];
} Factory;

void disk_backup() { printf("disk backup\n"); }
void tape_backup() { printf("tape backup\n"); }
void dvd_backup() { printf("dvd backup\n"); }

Storage *disk_maker() {
    Storage *stor = malloc(sizeof(Storage));
    stor->backup = disk_backup;
    return stor;
}

Storage *tape_maker() {
    Storage *stor = malloc(sizeof(Storage));
    stor->backup = tape_backup;
    return stor;
}

Storage *cloner(Storage *stor) {
    Storage *clone = malloc(sizeof(Storage));
    *clone = *stor;
    return clone;
}

Storage *dvd_maker() {
    Storage *stor = malloc(sizeof(Storage));
    stor->backup = dvd_backup;
    return stor;
}

int main() {
    Factory fac[3];
    fac[DISK_TYPE].make_storage = disk_maker;
    fac[TAPE_TYPE].make_storage = tape_maker;
    fac[DVD_TYPE].make_storage  = dvd_maker;

    Storage* roles[3];
    roles[DISK_TYPE] = fac[DISK_TYPE].make_storage();
    roles[TAPE_TYPE] = fac[TAPE_TYPE].make_storage();
    roles[DVD_TYPE]  = fac[DVD_TYPE].make_storage();

    Storage *clone = cloner(roles[TAPE_TYPE]);
    clone->backup();

    int i;
    for (i=0; i < 3; ++i) roles[i]->backup();
}

