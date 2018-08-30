#include "version.h"
#include <stdio.h>
#include <stdlib.h>

// The name of this program.
const char * program_name = "thedude";
// The version of this program.
const char * version = "0.010";

/* Print an ID stamp for the program. */

static void _program_id_stamp (FILE * output)
{
    fprintf (output, "%s / %s / %s / %s\n",
             program_name, version,
             build_date, build_git_sha);
}

int main()
{
    printf("Version: %s\n", VERSION);
    _program_id_stamp(stdout);
}
