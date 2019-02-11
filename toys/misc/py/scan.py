#!/usr/bin/env python3

import re
import sys
import colorama
from colorama import Fore

regexp = "(import)"

for line in sys.stdin:
    if line:
        line = line.rstrip()
        cap = re.search(regexp, line)
        if (cap):
            n = len(cap.groups())
            print(Fore.RED, n)
#           str = "c:/www/" + cap.group(1)
#           print("from was: " + str + ":> " + line)

print(Fore.RESET)
