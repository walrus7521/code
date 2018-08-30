#!/usr/bin/python

import logging  # 
import time     # 
import sys      # 
import _pfish   # 

if __name__=='__main__':
    PFISH_VERSION='1.0'
    # turn on logging
    logging.basicConfig(filename='pFishLog.log', level=logging.DEBUG,
            format='%(asctime)s%(message)s')
    _pfish.ParseCommandLine()
    startTime = time.time()

    # Post start message
    logging.info('Welcome to p-fish version 1.0...New Scan Started')
    _pfish.DisplayMessage('Welcome to p-fish...version 1.0')

    # record system info
    logging.info('System: '+sys.platform)
    logging.info('Version: '+sys.version)

    # traverse file system dirs
    filesProcessed = _pfish.WalkPath()

    # record end time, calc duration
    endTime = time.time()
    duration = endTime - startTime

    logging.info('Files processed: ' + str(filesProcessed))
    logging.info('Elapsed time: ' + str(duration) + 'seconds')

    logging.info('Program terminated normally')

    _pfish.DisplayMessage("Program end")

