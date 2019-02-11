#!/usr/bin/env python3

from colorama import Fore, Back

color = Back.BLACK + Fore.BLUE
print(color + "\nhere we go")
try:
    for n in range(1,5):
        color1 = Back.RED  + Fore.YELLOW
        color2 = Back.YELLOW + Fore.BLACK
        print(color1 + "->" + color2 + " " + str(n))
    raise Exception
except Exception:
    color = Back.BLACK + Fore.RED
    print(color, "now you're fucked")
finally:
    print(Fore.RESET)
