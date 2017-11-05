#!/usr/bin/python

import base64
import sys

def encode(key, clear):
    enc = []
    for i in range(len(clear)):
        key_c = key[i % len(key)]
        enc_c = chr((ord(clear[i]) + ord(key_c)) % 256)
        enc.append(enc_c)
    return base64.urlsafe_b64encode("".join(enc))

str = raw_input("Enter name: ")
key = "peanutbutterandjellysandwich"
str1 = encode(key, str)
print("name {0} encrypts to: {1}").format(str, str1)

