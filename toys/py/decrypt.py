#!/usr/bin/python

import base64
import sys

def decode(key, enc):
    dec = []
    enc = base64.urlsafe_b64decode(enc)
    for i in range(len(enc)):
        key_c = key[i % len(key)]
        dec_c = chr((256 + ord(enc[i]) - ord(key_c)) % 256)
        dec.append(dec_c)
    return "".join(dec)


str = raw_input("Enter cipher: ")
key = "peanutbutterandjellysandwich"
str2 = decode(key, str)
print("cipher {0} decrypts to: {1}").format(str, str2)

