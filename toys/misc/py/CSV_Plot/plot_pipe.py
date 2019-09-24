#!/usr/bin/python

import sys
import re
import csv
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from optparse import OptionParser
from datetime import date
from array import *
import fieldnames # auto-generated file from parser

CAPTURE_LENGTH = 200
TRIM_LENGTH = 1

tim   = []
frm   = []
rpos  = []
ppos  = []
rcmd  = []
pcmd  = []

capture = {} #[[]]

# trigger is a string
def start_capture(trigger, value, columns):
    print("capture: {0} @ {1}".format(trigger, value))
    print(len(columns))
    print(columns)
    for c in columns: 
        print(c)
    
    reader = csv.DictReader(sys.stdin, fieldnames)
    counter = 0
    transition = 0
    for row in reader:
        #if (transition == 0 and ((float(row['actuator_commands_roll']) != 0.0) or (float(row['actuator_commands_pitch']) != 0.0 )) ):
        if (transition == 0 and (float(row[trigger]) != 0.0) ):
            print(row['framenumber'] + "trigger")
            transition = 1
            print("trigger")
            counter = counter + 1
            #start_frame = float(row['framenumber'])/100.0

        if (transition == 1 and counter <= CAPTURE_LENGTH):
            print("accumulate: " + str(counter))
            counter = counter + 1
            frame   = float(row['framenumber'])/100.0
            tim.append(frame)
            frm.append(float(row['framenumber']))

            for c in columns: 
                val = row[c]
                capture[c].append(float(val))
    
        if counter > CAPTURE_LENGTH:
            print("plot")
            break

    print("plot the data")

    # trim off the first x data points
    for i in xrange(0,TRIM_LENGTH):
        tim.pop(0)
        frm.pop(0)

        for c in columns: 
            capture[c].pop(0)

    # plot everything
    t = tim #np.arange(tim)
    s = capture(trigger)
    #data = np.array(s)

    data = list(s)
    tt   = list(t)

    fig, ax = plt.subplots()
    fig, bx = plt.subplots()
    fig, roll_phase = plt.subplots()
    fig, pitch_phase = plt.subplots()


    ax.plot(tim, rcmd, label='rcmd')
    ax.plot(tim, rpos, label='rpos')

    bx.plot(tim, pcmd, label='pcmd')
    bx.plot(tim, ppos, label='ppos')

    roll_phase.plot(rcmd, rpos, label='Roll x=cmd, y=pos')
    pitch_phase.plot(pcmd, ppos, label='Pitch x=cmd, y=pos')

    ax.grid()
    bx.grid()
    roll_phase.grid()
    pitch_phase.grid()

    ax.legend()
    bx.legend()
    roll_phase.legend()
    pitch_phase.legend()

    plt.show()

    datename = date.today()
    sd = datename.isoformat()
    Capture_Filename = sd +'_' + str(frame) + '.csv'
    print("Saving " + Capture_Filename)
#    with open(Capture_Filename, 'wb') as csvfile:
#        csvwriter = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
#        csvwriter.writerow(['Frame', 'RollCmd', 'RollPos', 'PitchCmd', 'PitchPos', 'Roll1Cur', 'Roll2Cur', 'RollRateFail', 'RollActPosFail', 'RollServoloopCurrSatLL', 'RollServoloopCurrSatUL', 'RollServoloopPLSat', 'RollServoloopPLInv', 'RollServoloopRLSat'])
#        for i in xrange (0,CAPTURE_LENGTH-TRIM_LENGTH):
#            csvwriter.writerow([str(frm[i]), str(rcmd[i]), str(rpos[i]), str(pcmd[i]), str(ppos[i]), str(r1cur[i]), str(r2cur[i]), str(rmvc[i]), str(rrf[i]), str(rapf[i]), str(rcsll[i]), str(rcsul[i]), str(rspls[i]), str(rsrls[i])])




def my_callback(option, opt, value, parser):
    #print("dude callback {0}".format(value.split(',')))
    setattr(parser.values, option.dest, value.split(','))

def main():
    parser = OptionParser()
    parser.add_option("-t", "--trigger",
                      dest = "trigger",
                      help = "trigger column",
                      type = "string",
                      action = "store"
    )
    parser.add_option("-v", "--value",
                      dest = "value",
                      help = "value to trigger on",
                      type = "int",
                      action = "store"
    )
    parser.add_option("-c", "--columns",
                      dest = "columns",
                      help = "list of columns to display on trigger",
                      type = "string",
                      action = "callback",
                      callback = my_callback
    )
    (options, args) = parser.parse_args()
    if options.trigger and options.value:
        return start_capture(options.trigger, options.value, options.columns)
    else:
        parser.print_help()
        raise SystemExit

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print("Exception occured running main():")
        print(str(e))

