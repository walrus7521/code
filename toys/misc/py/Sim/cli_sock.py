import socket

# tail -f flt_data_All.csv | cli_sock.py

HOST = 'localhost'
PORT = 9876
ADDR = (HOST,PORT)
BUFSIZE = 4096
client = 0

import fileinput

while True:
    for line in fileinput.input():
        try:
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.settimeout(5)
            client.connect(ADDR)
            client.send(line)
        except socket.error, msg:
            continue

client.close()


