#!/usr/bin/env python3

import re
import sys

INI_HEADER = re.compile(r"^\[[^]]+\]$")
KEY_VALUE_RE = re.compile(r"^(?P<key>\w+)\s*=\s*(?P<value>.*)$")

lowercase_keys = True
file = open("my.pls", "r")
key_values = {}
for lino, line in enumerate(file, start=1):
    line = line.strip()
    if not line or line.startswith("#"):
        continue
    key_value = KEY_VALUE_RE.match(line)
    if key_value:
        key = key_value.group("key")
        if lowercase_keys:
            key = key.lower()
        key_values[key] = key_value.group("value")
    else:
        ini_header = INI_HEADER.match(line)
        if not ini_header:
            print("Failed to parse line {0}: {1}".format(lino, line))
        else:
            print(">"+line)

for k in key_values:
    print("[{0}] = {1}".format(k, key_values[k]))


