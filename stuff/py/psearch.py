#!/usr/bin/python

import logging
import time
import argparse
import os


def ParseCommandLine():
    parser = argparse.ArgumentParser('Python search')

    parser.add_argument('-v', '--verbose', help='allows progress messages', action='store_true')

    parser.add_argument('-k', '--keyWords', type=ValidateFileRead, required=True,
            help='file containing search words')

    parser.add_argument('-t', '--srchTarget', type=ValidateFileRead,
            required=True, help='specify file to search')

    global gl_args
    gl_args = parser.parse_args()

    DisplayMessage("command line processed successfully")
    return


def SearchWords():
    searchWords = set() # create empty set
    # read words from file
    try:
        fileWords = open(gl_args.keyWords)
        for line in fileWords:
            searchWords.add(line.strip())
    except:
        log.error('Keyword file failure: ' + gl_args.keyWords)
        sys.exit()
    finally:
        fileWords.close()

    # write entries to log
    log.info('Search Words')
    log.info('Input file: ' + gl_args.keyWords)
    log.info(searchWords)

    # try to open the target file
    try:
        targetFile = open(gl_args.srchTarget, 'rb')
        baTarget = bytearray(targetFile.read())
    except:
        log.error('Target file failure: ' + gl_args.srchTarget)
        sys.exit()
    finally:
        targetFile.close()

    sizeOfTarget = len(baTarget)

    log.info('Target of Search: ' + gl_args.srchTarget)
    log.info('File size: ' + str(sizeOfTarget))

    # modify baTarget by substituting zero for all non-alpha chars
    baTargetCopy = baTarget
    for i in range(0, sizeOfTarget):
        char = chr(baTarget[i])
        if not char.isalpha():
            baTarget[i] = 0
    # extract possible words from bytearray and inspect search list
    notFound = []
    cnt = 0
    for i in range(0, sizeOfTarget):
        char = chr(baTarget[i])
        if char.isalpha():
            cnt += 1
        else:
            if (cnt >= MIN_WORD and cnt <= MAX_WORD):
                newWord = ''
        for z in range(i-cnt, i):
            newWord = newWord + chr(baTarget[z])
            if (newWord in searchWords):
                PrintBuffer(newWord, i-cnt, baTargetCopy, i - PREDECESSOR_SIZE,
                        WINDOW_SIZE)
                print
            else:
                cnt = 0

    PrintNotFound(notFound)

def PrintBuffer(word, directOffset, buf, offset, hexSize):
    pass

    pass

def ValidateFileRead(theFile):
    if not os.path.exists(theFile):
        raise argparse.ArgumentTypeError('file does not exist')
    if os.access(theFile, os.R_OK):
        return theDir
    else:
        raise argparse.ArgumentTypeError('file is not readable')


if __name__=='__main__':
    P_SEARCH_VERSION = '1.0'
    
    logging.basicConfig(filename='pSearchLog.log', level=logging.DEBUG,
            format='%(asctime)s %(message)s')

    ParseCommandLine()

    log = logging.getLogger('main.psearch')
    log.info("psearch started")

    startTime = time.time()
    SearchWords()

    endTime = time.time()
    duration = endTime - startTime

    logging.info('Elapsed Time: ' + str(duration) + 'seconds')
    logging.info('')
    logging.info('Program terminated normally')


