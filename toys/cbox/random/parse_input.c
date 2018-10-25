#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum print_options {
    INSTALL     = 1,
    UPDATE      = 2,
    UNINSTALL   = 4,
    VERBOSE     = 8
};

typedef int (*dude_cb)(void *, int , char **);


int c_install(void *p, int argc, char **argv) { printf("installing\n"); return 0; }
int c_update(void *p, int argc, char **argv) { printf("updating\n"); return 0; }
int c_uninstall(void *p, int argc, char **argv) { printf("uninstalling\n"); return 0; }

struct {
    char *name;
    dude_cb fn;
} commands[] = {
    {"install", c_install},
    {"update", c_update},
    {"uninstall", c_uninstall},
    { NULL, NULL}
};

void print_usage(void)
{
    fprintf(stderr, "usage: add [options] [--] file-spec [file-spec] [...]\n\n");
    fprintf(stderr, "\t-n, --dry-run    dry run\n");
    fprintf(stderr, "\t-v, --verbose    be verbose\n");
    fprintf(stderr, "\t-u, --update     update tracked files\n");
    exit(1);
}

static void parse_opts(int *options, int *count, int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            break;
        }
        else if(!strcmp(argv[i], "--verbose") || !strcmp(argv[i], "-v")) {
            *options |= VERBOSE;
        }
        else if(!strcmp(argv[i], "--install") || !strcmp(argv[i], "-i")) {
            *options |= INSTALL;
        }
        else if(!strcmp(argv[i], "--uninst") || !strcmp(argv[i], "-x")) {
            *options |= UNINSTALL;
        }
        else if(!strcmp(argv[i], "--update") || !strcmp(argv[i], "-u")) {
            *options |= UPDATE;
        }
        else if(!strcmp(argv[i], "-h")) {
            print_usage();
            break;
        }
        else if(!strcmp(argv[i], "--")) {
            i++;
            break;
        }
        else {
            fprintf(stderr, "Unsupported option %s.\n", argv[i]);
            print_usage();
        }
    }

    *count = i;
}

int main(int argc, char *argv[])
{
    int options = 0;
    int count = 0;
    parse_opts(&options, &count, argc, argv);
    printf("options: 0x%x, count: %d\n", options, count);
    if (options & VERBOSE) {
        printf("verbose\n");
    }
    if (options & INSTALL) {
        commands[0].fn(NULL, argc, argv);
    }
    if (options & UPDATE) {
        commands[1].fn(NULL, argc, argv);
    }
    if (options & UNINSTALL) {
        commands[2].fn(NULL, argc, argv);
    }

}

