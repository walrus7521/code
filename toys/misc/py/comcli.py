#!/usr/bin/python
# usage: comcli.py -p COM11 -b 115200

import sys
import serial
import argparse

def arg_auto_int(x):
    return int(x, 0)

class fatal(RuntimeError):
    def __init__(self, message):
        RuntimeError.__init__(self, message)

def main():
    parser = argparse.ArgumentParser(description = 'COM interface', prog = 'client')
    parser.add_argument( '--port', '-p', help = 'port', default = 'COM42')
    parser.add_argument( '--baud', '-b', help = 'baud', type = arg_auto_int, default = 9600)
    args = parser.parse_args()

    print '\nTrying port: ', args.port, ' at baud: ', args.baud

    try:
        port = serial.Serial(args.port, args.baud, timeout=0.1)
    except Exception as e:
        print 'I/O error({0}): {1}'.format(e.errno, e.strerror)
        print 'Port cannot be opened'
    else:
        print 'Ready!\n'

    while True:
        sys.stdout.write("Enter command: ")
        sys.stdout.flush()
        cmd = raw_input()
        print "cmd: {}".format(cmd)
        port.write(cmd)
    port.close()


if __name__ == '__main__':
    try:
        main()
    except fatal as e:
        print '\nA fatal error occurred: %s' % e
        sys.exit(2)
