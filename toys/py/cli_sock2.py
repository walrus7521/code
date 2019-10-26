#!/usr/bin/env python3

import socket

HOST = 'localhost'
PORT = 9876
ADDR = (HOST,PORT)
BUFSIZE = 4096
client = 0

while True:
    mystr = input()
    print(mystr)
    b = bytes(mystr, 'utf-8')
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(ADDR)
    client.send(b)

client.close()


