#!/usr/bin/env python3

import re
import sys
import ap_strs

print("#!/usr/bin/python")
print()
print("#Parsed Telemetry Excel column numbers")
print("#these should be detected from the column headers, but here as constants for now")
print("fieldnames = [")

offset = 0

try:
    for line in sys.stdin:
        if line:
            line = line.rstrip()
            pair = line.split(',', 2)
            name = pair[0]
            type = pair[1]
            if ("." in name):
                full_names = name.split('.')
                length = len(full_names)
                print("    '", end='', flush=True)
                for x in full_names[:-1]:
                    print(x + "_", end='', flush=True)
                full_names[-1].rstrip()
                print(full_names[-1], end='\',\n', flush=True)
            else:
                print("    '{0}',".format(name))

except Exception:
    print("error in data")
finally:
    pass


print("]")


