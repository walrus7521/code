#!/usr/bin/env python3

import re
import sys
import colorama
from colorama import Fore, Back

regexp = "(import)"

color = Back.BLACK + Fore.BLUE
print(color + "\nhere we go")
try:
    for line in sys.stdin:
        if line:
            line = line.rstrip()
            cap = re.search(regexp, line)
            if (cap):
                n = len(cap.groups())
                color1 = Back.RED  + Fore.YELLOW
                color2 = Back.YELLOW + Fore.BLACK
                print(color1 + "->" + color2 + " " + str(n))
    #           str = "c:/www/" + cap.group(1)
    #           print("from was: " + str + ":> " + line)
    raise Exception
except Exception:
    color = Back.BLACK + Fore.RED
    print(color, "now you're fucked")
finally:
    print(Fore.RESET)
