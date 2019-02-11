#!/usr/bin/env python3

import sys

if len(sys.argv) < 3:
    print("usage: grepo work infile1 [infile2 [...]]")
    sys.exit(1)

word = sys.argv[1]
for filename in sys.argv[2:]:
    # start=1 means lino will be one-based, and not zero-based
    for lino, line in enumerate(open(filename), start=1):
        if word in line:
            print("{0}:{1}:{2:.40}".format(filename, lino, line.rstrip()))

