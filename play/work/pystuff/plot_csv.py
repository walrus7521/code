#!/usr/bin/python

# test.csv file contents:
# A,B,"C D"
# 1,2,"3 4"
# 5,6,7

import csv
import matplotlib
import matplotlib.pyplot as plt
import time

matplotlib.use('TKAgg')
#matplotlib.use('GTKAgg')

plt.ion()

width = 100
### reader
plt.title("dude")
def csv_read():
    ifile  = open('20181116_FreqSweep0_25Hz_no_header.csv', "rb")
    reader = csv.reader(ifile)
    rownum = 0
    for row in reader:
            
        # Save header row.
        #if rownum == 0:
        #    header = row
        #else:
        x = float(row[0])
        y = float(row[3])
        #colnum = 0
        #for col in row:
        #    print '%-8s: %s' % (header[colnum], col)
        #    colnum += 1
        #print x, y
        plt.plot(x, y, 'x')

        #plot(x, y, color='green', marker='o', linestyle='dashed', linewidth=2, markersize=12)
        
        plt.draw()
        plt.pause(0.0001)
        plt.show()
        #time.sleep(0.02)
        rownum += 1
    ifile.close()    


### writer
def csv_write():
    ifile  = open('test.csv', "rb")
    reader = csv.reader(ifile)
    ofile  = open('ttest.csv', "wb")
    writer = csv.writer(ofile, delimiter='	', quotechar='"', quoting=csv.QUOTE_ALL)
    for row in reader:
        writer.writerow(row)
    ifile.close()
    ofile.close()    

print "testing csv read and write"

csv_read()
plt.show(block=True) # block=True lets the window stay open at the end of the animation.
plt.savefig('sinewaves.png')
#csv_write()

