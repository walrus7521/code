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
    processCount = 0
    errorCount = 0

    logging.info('Root Path: ' + gl_args.rootPath)
    #oCVS = _CVSWriter(gl_args.reportPath+'fileSysemReport.csv', gl_hashType)
    oCVS = 1
    
    # loop over files
    for root,dirs,files in os.walk(gl_args.rootPath):
        for file in files:
            fname = os.path.join(root, file)
            result = HashFile(fname, file, oCVS)
            if result == True:
                processCount += 1
            else:
                errorCount += 1

    #oCVS.writerClose()

    return (processCount)

# theFile is full path, simple is just name
def HashFile(theFile, simpleName, o_result):
    print theFile
    return True

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


