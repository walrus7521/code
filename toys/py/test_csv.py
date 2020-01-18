#!/usr/bin/python

# test.csv file contents:
# A,B,"C D"
# 1,2,"3 4"
# 5,6,7

import csv

### reader
def csv_read():
    ifile  = open('test.csv', "rb")
    reader = csv.reader(ifile)
    rownum = 0
    for row in reader:
        # Save header row.
        if rownum == 0:
            header = row
        else:
            colnum = 0
            for col in row:
                print '%-8s: %s' % (header[colnum], col)
                colnum += 1
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
csv_write()

