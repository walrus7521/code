#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512 // make these parameters
#define MAX_ROWS 100

// add find
// struct packing
// more fields to Address and searchable


struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char desc[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};


struct Connection *g_conn = NULL;
char *g_fname = NULL;


void Database_get(struct Connection *conn, int id);
void Database_close(struct Connection *conn);

void header()
{
    printf("id  name    description\n");
    printf("=== ======  ================================\n");
}

void die(struct Connection *conn, const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d) %s %s\n", addr->id, addr->name, addr->desc);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) {
        die(conn, "Failed to load database.");
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    //struct Connection *conn = malloc(sizeof(struct Connection));
    g_conn = malloc(sizeof(struct Connection));
    if (!g_conn) {
        die(g_conn, "Memory error");
    }

    g_conn->db = malloc(sizeof(struct Database));
    if (!g_conn->db) {
        die(g_conn, "Memory error");
    }

    if (mode == 'c') {
        g_conn->file = fopen(filename, "w");
    } else {
        g_conn->file = fopen(filename, "r+");
        if (g_conn->file) {
            Database_load(g_conn);
        }
    }

    if (!g_conn->file) {
        die(g_conn, "Failed to open the file");
    }

    return g_conn;
}

void Database_close(struct Connection *conn)
{
    if (conn) {
        if (conn->file) {
            fclose(conn->file);
        }
        if (conn->db) {
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) {
        die(conn, "Filed to write database.");
    }

    rc = fflush(conn->file);
    if (rc == -1) {
        die(conn, "Can't flush database.");
    }
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0 };
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        printf("id %d is already set to => ", id);
        Database_get(conn, id);
        //die(conn, "Already set, delete it first");
    }

    addr->set = 1;
    // WARNING: bug, read the "How to break it" and ifx this
    name[MAX_DATA-1] = '\0';
    char *res = strncpy(addr->name, name, MAX_DATA);

    // demonstrate the strncpy bug
    if (!res) {
        die(conn, "Name copy failed");
    }

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res) {
        die(conn, "Email copy failed");
    }
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die(conn, "ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = { .id = id, .set = 0 };
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    header();
    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

void help()
{
    printf("usage: l - load <db name>\n");
    printf("       q - quit\n");
}

int load(char *filename)
{
    g_fname = filename;
    printf("try loading: %s\n", g_fname);
    Database_open(g_fname, 'r');
}

int ui(int argc, char *argv[])
{
    while (1) {
        fputs("$ ", stdout);
        char cmd = getchar();
        switch (cmd) {
            case 'a': printf("a\n"); break;
            case 'b': printf("b\n"); break;
            case 'c': printf("c\n"); break;
            case 'd': printf("d\n"); break;
            case 'h': help(); break;
            case 'l': load("work.db"); break;
            case 'q': goto exit;
            default:  break;
        }
    }
exit:
    return 0;
}

int main(int argc, char *argv[])
{
    int rc = ui(argc, argv);
    return rc;

    if (argc < 3) {
        die(NULL, "USAGE: ex17 <dbfile> <action> [action params]");
    }

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;



    if (argc > 3) {
        id = atoi(argv[3]);
    }
    if (id >= MAX_ROWS) {
        die(conn, "There's not that many records.");
    }

    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) {
                die(conn, "Need an id to get");
            }
            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) {
                die(conn, "Need id, name, email to set");
            }
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) {
                die(conn, "Need id to delete");
            }
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die(conn, "Invalid action: c=create, g=get, s=set, d=del, l=list");
            break;
    }

    Database_close(conn);

    return 0;

}


