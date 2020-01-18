#!/usr/bin/python

import platform
import time
import sys
import re

class sfiles:
    def __init__(self, filename):
        self.nfiles = 0
        self.filename = filename
        self.sys_sfiles = {}
        class_name = self.__class__.__name__
        print class_name, "created"
    def __del__(self):
        class_name = self.__class__.__name__
        print class_name, "destroyed"

    def scan_system_files(self):
        try:
            scanfile = open(self.filename, 'rU');
        except IOError:
            print "Error: can\'t find file or read data"            
        if not scanfile:
            print "error opening file"
            sys.exit()
        while (1):
            line = scanfile.readline()        
            if line:
                line = line.rstrip()
                #print line
                #cap = re.match(r'lba: \((.*)\) extents.*start_lba \(([\da-f]{3,16})\) end_lba \(([\da-f]{3,16})\)', line, re.I | re.S)
                cap = re.match(r'lba: \((.*)\), ([\da-f]{3,16}), ([\da-f]{1,16})', line, re.I | re.S)
                if (cap):
                    #if sys_files.has_key(cap.group(1).lower()):
                    #if cap.group(1).lower() in sys_files:
                    #    print "dup file"
                    #    sys_files[cap.group(1).lower()] += 1;
                    #else:
                    file_rec = {}
                    filename = cap.group(1).lower() # File name
                    file_rec['NAME'] = filename
                    file_rec['SLBA'] = int(cap.group(2), 16) # Start LBA
                    file_rec['NLBAS'] = int(cap.group(3), 16) # End LBA
                    file_rec['NUM']  = 1                     # Number of occurences - process in dedup
                    self.sys_sfiles[filename] = file_rec;
                    self.nfiles += 1
                continue
            else:
                scanfile.close()
                break

    def dedup(self):
    # bogus routine - just playing with sets
        seen = set(self.sys_sfiles.keys())
        dups = 0
        for fkey in self.sys_sfiles.keys():
            fval = self.sys_sfiles[fkey]
            fname = fval['NAME']
            #print "checking if %s is in set" % fname
            if fname in seen:
                dups += 1
                #print "duplicates exist..."
                #return True
            #print "adding %s to set" % fname
            seen.add(fname)
        #print "no duplicates exist..."
        print "=============================="
        print "duplicates: %d" % dups
        print "==============================\n"   
        return False

    def show(self):
        count = 0
        vitem = {}
        print "NUM   SLBA       NLBAS     FILE"
        print "====  ========   ========  ============"
        for file_key in self.sys_sfiles.keys():
            file_val = self.sys_sfiles[file_key]
            count += 1
            print "(%02d) [%08x - %08x] : %s" % (file_val['NUM'], file_val['SLBA'], file_val['NLBAS'], file_val['NAME'])
        print "file count: %d" % count



class lba_class:
    def __init__(self, filename, page_start, page_end):
        self.nlbas = 0
        self.lba_recs  = []  # array of all lbas captured by filter driver   #
        self.filename = filename
        self.pagefile_start = page_start
        self.pagefile_end   = page_end
        class_name = self.__class__.__name__
        print class_name, "created"
    def __del__(self):
        class_name = self.__class__.__name__
        print class_name, "destroyed"
    def scan_file(self):
        try:
            lbafile = open(self.filename, 'rU');
        except IOError:
            print "Error: can\'t find file or read data"            
        if not lbafile:
            print "error opening file"
            sys.exit()
        #else:
            #print "success opening file"
            #lines = file.readlines()
        while (1):
            line = lbafile.readline()        
            if line:
                line = line.rstrip()
                cap = re.match(r'.*(READ|WRITE) \[(.*)', line, re.I | re.S)
                #if cap:
                    #print cap.group(2)
                #else:
                    #print "nothing matched cap"
                lba = re.match(r'([\da-f]{3,16}) - ([\da-f]{3,16})', cap.group(2), re.I | re.S)
                #if lba:
                    #print "group(1) " + lba.group(1)
                    #print "group(2) " + lba.group(2)
                #else:
                    #print "nothing matched lba"
        # Format of capture data
        #00000001	0.00000000	READ [15a1570 - 15a15f0] LEN 80	
        #00000002	0.00026835	READ [15a15f0 - 15a1670] LEN 80	
                lba_rec = {}
                lba_rec['OP']   = cap.group(1)          # READ/WRITE
                lba_rec['SLBA'] = int(lba.group(1), 16) # Start LBA
                lba_rec['ELBA'] = int(lba.group(2), 16) # End LBA
                lba_rec['NUM']  = 1                     # Number of occurences - process in dedup
                self.lba_recs.append(lba_rec)
                self.nlbas += 1
                continue
            else:
                lbafile.close()
                break

    def show(self):
        count = 0
        print "SLBA      ELBA      OP      NUM"
        print "========  ========   =====   ==="
        for item in self.lba_recs:
            count += 1
            #print "%08x  %08x  %6s   %02d" % (item['SLBA'], item['ELBA'], item['OP'], item['NUM'])
        print "LBA count: %d" % count\

    def dedup(self):
        lba_dups = 0
        for item1 in self.lba_recs:
            for item2 in self.lba_recs:
                if ((item1['SLBA'] == item2['SLBA']) and \
                    (item1['ELBA'] == item2['ELBA']) and \
                    (item1['OP']   == item2['OP'])):
                    lba_dups += 1
                    item1['NUM'] += 1
                    self.lba_recs.remove(item2)
        print "=============================="
        print "dedup'ed LBAs: %d" % lba_dups
        print "==============================\n"

    def pagefile_hits(self):
        hit_count = 0
        print "=============================="
        for item in self.lba_recs:
            slba = item['SLBA']
            elba = item['ELBA']
            if (self.pagefile_start <= slba and slba <= self.pagefile_end and \
                self.pagefile_start <= elba and elba <= self.pagefile_end):
                op = item['OP']
                hit_count += 1
                print "pagefile hit: op %s " % op
        print "pagefile hits: %d" % hit_count
        print "==============================\n"

def get_system_info():
    print time.ctime()
    print platform.uname()
    print

def find_files_accessed(files_hash, lbas_array):
    for file_key in files_hash.keys():
        file_val = files_hash[file_key]
        for item in lbas_array:
            file_slba = file_val['SLBA']
            file_elba = file_slba + file_val['NLBAS']
            slba = item['SLBA']
            elba = item['ELBA']
            file_name = file_val['NAME']
            hits      = item['NUM']
            op        = item['OP']
            if (file_slba >= slba and file_slba <= elba):
                print "(%d) %6s's to FILE:%s" % (hits, op, file_name)
                #print "FILE %s HITS(%d) %x is in [%x - %x] - %s\n" % (file_name, hits, file_slba, slba, elba, op)

def main():
    pagefile_start = 0xfc1f68
    pagefile_end   = 0x14f4568
    lba_file = "idle1.cap"
    get_system_info()
    lbas = lba_class(lba_file, pagefile_start, pagefile_end);
    lbas.scan_file()
    lbas.dedup()
    #lbas.show()
    lbas.pagefile_hits()
    file_scan_file = "files.out"
    fsys = sfiles(file_scan_file);
    fsys.scan_system_files()
    #fsys.dedup() # bogus routine
    fsys.show()
    find_files_accessed(fsys.sys_sfiles, lbas.lba_recs)
    sys.exit()

main()

