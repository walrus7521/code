#!/usr/bin/env python3
# usage: comsrv.py

import sys
import signal
import serial
import threading
import time
import argparse

com_ports = [ "COM20", "COM21", "COM22", "COM23", "COM24", "COM25", "COM26", "COM27",
              "COM28", "COM29", "COM30", "COM31", "COM32", "COM33", "COM34", "COM35" ];

stop_threads = False

def signal_handler(signal, frame):
    global stop_threads
    stop_threads = True
    print('You pressed Ctrl+C!')

def start_port(com, baud):
    port = None
    try:
        port = serial.Serial(com, baud, timeout=0.1)
    except Exception as e:
#       print('I/O error({0}): {1}').format(e.errno, e.strerror)
        print('Port cannot be opened')
    else:
        print('rdy\n')
    return port

def arg_auto_int(x):
    return int(x, 0)

class fatal(RuntimeError):
    def __init__(self, message):
        RuntimeError.__init__(self, message)


def com_srv_loop(port, stop):
    global stop_threads
    while True:
        time.sleep(1)
        got = port.readline()
        if stop():
            print("  Exiting loop.")
            break        
        if got:
            print(got)
            if got == 'kill':
                stop_threads = True
    port.close()
    
def main():
    global stop_threads
    workers = []

    signal.signal(signal.SIGINT, signal_handler)
        
    for port in com_ports:
        cport = start_port(port, 9600)
        tmp = threading.Thread(target=com_srv_loop, args=(cport, lambda: stop_threads))
        tmp.daemon = True
        workers.append(tmp)
        tmp.start()

    while stop_threads == False:
        time.sleep(1)

    for worker in workers:
        worker.join()

    print('Fini')

if __name__ == '__main__':
    try:
        main()
    except fatal as e:
        print('\nA fatal error occurred: %s' % e)
        sys.exit(2)


