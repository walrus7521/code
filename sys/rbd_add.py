#!/usr/bin/python
import os

path = "/sys/bus/rbd/add"
cmd = "echo 1 >" + path
retvalue = os.system(cmd)
print retvalue


