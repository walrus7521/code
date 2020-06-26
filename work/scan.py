import re
import sys

for line in sys.stdin:
    #print line

    # FAA39550sinfreq = 7.000000
    matchObj = re.search( r'FAA(\d+)sinfreq = (\d+\.\d+)', line)
    if matchObj:
        print matchObj.group(1), " => ", matchObj.group(2)
    #else:
        #print "No match!!"


