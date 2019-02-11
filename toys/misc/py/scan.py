#!/usr/bin/env python3

import re
import sys
import colorama
from colorama import Fore

regexp = "(import)"

try:
    for line in sys.stdin:
        if line:
            line = line.rstrip()
            cap = re.search(regexp, line)
            if (cap):
                n = len(cap.groups())
                print(Fore.BLUE, n)
    #           str = "c:/www/" + cap.group(1)
    #           print("from was: " + str + ":> " + line)
    raise Exception
except Exception:
    print(Fore.RED, "you're fucked")
finally:
    print(Fore.RESET)
