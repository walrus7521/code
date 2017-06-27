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
    pass

def ValidateFileRead():
    pass

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


