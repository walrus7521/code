#!/usr/bin/python

import subprocess
from subprocess import call

test_files = [ 
                "ahci_rd_8sectors_2slots_ncq.txt",
                "ahci_rd_8sectors_4slots_ncq.txt",
                "ahci_rd_8sectors_8slots_ncq.txt",
                "ahci_rw_8sectors_8slots_ncq.txt",
                "ahci_rd_8sectors_16slots_ncq.txt",
                "ahci_rd_8sectors_32slots_ncq.txt",
                "ahci_rd_16sectors_2slots_ncq.txt",
                "ahci_rd_16sectors_4slots_ncq.txt",
                "ahci_rd_16sectors_8slots_ncq.txt",
                "ahci_rd_16sectors_16slots_ncq.txt",
                "ahci_rd_16sectors_32slots_ncq.txt",
                "ahci_rw_16sectors_16slots_ncq.txt",
                "ahci_rd_32sectors_2slots_ncq.txt",
                "ahci_rd_32sectors_4slots_ncq.txt",
                "ahci_rd_32sectors_8slots_ncq.txt",
                "ahci_rd_32sectors_16slots_ncq.txt",
                "ahci_rd_32sectors_32slots_ncq.txt",
                "ahci_rw_32sectors_32slots_ncq.txt",
                "ahci_rd_64sectors_2slots_ncq.txt",
                "ahci_rd_64sectors_4slots_ncq.txt",
                "ahci_rd_64sectors_8slots_ncq.txt",
                "ahci_rd_64sectors_16slots_ncq.txt",
                "ahci_rd_64sectors_32slots_ncq.txt",
             ]

def syscall(cmd, file):
    command = cmd + " " + file
    print "testing (" + file + ")"
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    for line in p.stdout.readlines():
        print line,
    retval = p.wait()    
    return retval

command = "dir"
#command = "./puma -j 1 -F"
#command = "./puma -F"
test_file = "ahci_init.txt"
syscall(command, test_file)
for script in test_files:
    if syscall(command, script) != 0:
        print "fail"
    else:
        print "success"

exit

