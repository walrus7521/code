#!/usr/bin/python

import os
import stat
import time
import hashlib
import argparse
import csv
import logging

class _CSVWriter:
    def __init__(self, fileName, hashType):
        try:
            self.csvFile = open(fileName, 'wb')
            self.writer = csv.writer(self.csvFile,
                    delimiter=',', quoting=csv.QUOTE_ALL)
            self.writer.writerow( ('File', 'Path', 'Size',
                        'Modified Time', 'Access Time', 'Created Time',
                        hashType, 'Owner', 'Group', 'Mode') )
        except:
            logging.error('CSV file failure')

    def writeCSVRow(self, fileName, filePath, fileSize, mTime,
            aTime, cTime, hashVal, own, grp, mod):
        self.writer.writerow( (fileName, filePath,
                    fileSize, mTime, aTime, cTime, hashVal, own,
                    grp, mod))

    def writerClose(self):
        self.csvFile.close()

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
    oCVS = _CSVWriter(gl_args.reportPath+'fileSystemReport.csv', gl_hashType)

    # loop over files
    for root,dirs,files in os.walk(gl_args.rootPath):
        for file in files:
            fname = os.path.join(root, file)
            result = HashFile(fname, file, oCVS)
            if result == True:
                processCount += 1
            else:
                errorCount += 1

    oCVS.writerClose()

    return (processCount)

# theFile is full path, simple is just name
def HashFile(theFile, simpleName, o_result):
    print theFile
    if os.path.exists(theFile):
        #verify not symlink
        if not os.path.islink(theFile):
            # verify path is real
            if os.path.isfile(theFile):
                try:
                    # attempt to open file
                    f = open(theFile, 'rb')
                except IOError:
                        logging.warning('open failed: ' + theFile)
                        return
                else:
                    try:
                        # attempt read
                        rd = f.read()
                    except IOError:
                        f.close()
                        logging.warning('read failed: ' + theFile)
                        return
                    else:
                        # success, now query status
                        theFileStatus = os.stat(theFile)
                        (mode, ino, dev, nlink, uid, gid, size, atime, mtime, ctime) = os.stat(theFile)

                        DisplayMessage("Processing file: " + theFile)

                        fileSize = str(size)
                        # convert MAC times to strings
                        modifiedTime = time.ctime(mtime)
                        accessTime = time.ctime(atime)
                        createdTime = time.ctime(ctime)
    
                        ownerID = str(uid)
                        groupID = str(gid)
                        fileMode = bin(mode)

                        # process file hashes
                        if gl_args.md5:
                            hash = hashlib.md5()
                            hash.update(rd)
                            hexMD5 = hash.hexdigest()
                            hashValue = hexMD5.upper()
                        elif gl_args.sha256:
                            hash = hashlib.sha256()
                            hash.update(rd)
                            hexSHA256 = hash.hexdigest()
                            hashValue = hexSHA256.upper()
                        elif gl_args.sha512:
                            hash = hashlib.sha512()
                            hash.update(rd)
                            hexSHA512 = hash.hexdigest()
                            hashValue = hexSHA512.upper()
                        else:
                            logging.error('hash not selected')

                f.close()
                # write to CSV
                o_result.writeCSVRow(simpleName, 
                   theFile, fileSize, modifiedTime,
                   accessTime, createdTime, hashValue, 
                   ownerID, groupID, mode)

                return True

            else:
                logging.warning('[' + repr(simpleName) + ', skipped NOT a file' + ']')
                return False
        else:
            logging.warning('[' + repr(simpleName) + ', skipped Link NOT a file' + ']')
            return False
    else:
        logging.warning('[' + repr(simpleName) + ', Path does not exist' + ']')
        return False
 
    return False

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


