#!/usr/bin/python

# scstadmin -list_dgrp

import subprocess
import os
import sys
import getopt
import argparse

# /state
SCST_TG_STATE_OPTIMIZED     = "active"
SCST_TG_STATE_NONOPTIMIZED  = "nonoptimized"
SCST_TG_STATE_STANDBY       = "standby"
SCST_TG_STATE_UNAVAILABLE   = "unavailable"
SCST_TG_STATE_OFFLINE       = "offline"
SCST_TG_STATE_TRANSITIONING = "transitioning"

# /preferred
SCST_TG_PREFERRED           = 1
SCST_TG_NOT_PREFERRED       = 0

def syscall(cmd, path, tfile, val):
    command = cmd + " " + path + "/" + tfile
    print "command: " + command
    return 0
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    for line in p.stdout.readlines():
        print line,
    retval = p.wait()
    return retval

command = "cat"
path = "/sys/kernel/scst_tgt/device_groups/9988e270-ea80-83ec-d0e6-01078f1bb9cd/target_groups/9988e270-ea80-83ec-d0e6-01078f1bb9cd"
tfile1 = "state" # unavailable, active
tfile2 = "preferred" # unavailable, active
# "preferred" 0:1


def main():
    parser = argparse.ArgumentParser(description="""
        alua.py is a script to manually set the path states.
        """)

    parser.add_argument('--state', required=False, help='The state of the ALUA FC target.')
    parser.add_argument('--preferred', required=False, help='The preferred status of the ALUA FC target.')
    parser.add_argument('--get', action='store_true', default=False, required=False, help='get the ALUA FC states.')
    parser.add_argument('--set', action='store_true', default=False, required=False, help='set the ALUA FC states.')

    try:
        args = parser.parse_args()
    except:
        parser.print_help()
        sys.exit(2)

    if len(sys.argv)==1:
        parser.print_help()
        sys.exit(1)

    # validate parameters for set command
    if args.set:
        if (args.state is None):
            print "need to specify state"
            sys.exit(1);
        if (args.preferred is None):
            print "need to specify preferred"
            sys.exit(1);

    if args.get:
        command = "cat"
        tfile = "state"
        syscall(command, path, tfile, 0)
        tfile = "preferred"
        syscall(command, path, tfile, 0)
        sys.exit(1)
        
    if args.set:
        print "set: state=" + args.state + ", pre=" + args.preferred
        command = "echo " + args.state + " >"
        tfile = "state"
        syscall(command, path, tfile, 0)
        command = "echo " + args.preferred + " >"
        tfile = "preferred"
        syscall(command, path, tfile, 0)
        sys.exit(1)

    exit

if __name__ == '__main__':
    main()

