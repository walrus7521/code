import numpy as np
import matplotlib.pyplot as plt
import csv
import sys

# http://stackoverflow.com/questions/16503560/read-specific-columns-from-a-csv-file-with-csv-module

ADP_ALT_RAW_0 = 8
MCP_BARO_ALT  = 22

MPL3115A2_PRESSURE_SAMPLE_MASK = 0x00FFFFF0
MPL3115A2_PRESSURE_FIXED_POINT_TO_FLOATING_POINT_MULTIPLIER = (1.0 / 64.0)

x = []
y = []
f = open("MCPC_Std_All.csv", 'rt')
try:
    reader = csv.reader(f)
    headers = reader.next()
    #print("headers: %s" % headers)
    print headers
    for row in reader:
        baro_alt = 3.28*float(row[22])

        print("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20},{21},{22},{23},{24},{25},{26}".format(
            row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12], row[13], row[14], row[15],
            row[16], row[17], row[18], row[19], row[20], row[21], baro_alt, row[23], row[24], row[25], row[26]))

        y.append(baro_alt)
        x.append(row[0])

    #plt.plot(x, y)
    #plt.xlabel('time')
    #plt.ylabel('alt (ft)')
    #plt.show()

finally:
    f.close()

