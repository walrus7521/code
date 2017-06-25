#!/usr/bin/python

import os
import stat
import time
import hashlib
import argparse
import csv
import logging

def ParseCommandLine():
    parser = argparse.ArgumentParser('Python file system hashing .. pfish')
    parser.add_argument('-v', '--verbose', help='allows progress messages', action='store_true')
    # setup a group of options
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--md5', help='MD5 algorithm', action='store_true')
    group.add_argument('--sha256', help='SHA256 algorithm', action='store_true')
    group.add_argument('--sha512', help='SHA512 algorithm', action='store_true')

    parser.add_argument('-d', '--rootPath', type=ValidateDirectory, required=True,
            help='root path for hashing')
    parser.add_argument('-r', '--reportPath', type=ValidateDirectoryWritable,
            required=True, help='path for report')

    global gl_args
    global gl_hashType

    gl_args = parser.parse_args()

    if gl_args.md5:
        gl_hashType = 'MD5'
    elif gl_args.sha256:
        gl_hashType = 'SHA256'
    elif gl_args.sha512:
        gl_hashType = 'SHA512'
    else:
        gl_hashType = "Unknown"
        logging.error('Unknown hash type')

    DisplayMessage("command line processed successfully")
    return

def DisplayMessage(msg):
    print msg

def WalkPath():
    return ""

def ValidateDirectory(theDir):
    if not os.path.isdir(theDir):
        raise argparse.ArgumentTypeError('directory does not exist')
    if os.access(theDir, os.R_OK):
        return theDir
    else:
        raise argparse.ArgumentTypeError('directory not readable')

def ValidateDirectoryWritable(theDir):
    if not os.path.isdir(theDir):
        raise argparse.ArgumentTypeError('directory does not exist')
    if os.access(theDir, os.W_OK):
        return theDir
    else:
        raise argparse.ArgumentTypeError('directory not writable')


