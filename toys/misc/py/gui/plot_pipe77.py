#!/usr/bin/env python3

import os
import signal
import psutil
import sys
import csv
import configparser
import matplotlib.pyplot as plt
from optparse import OptionParser
import fieldnames # auto-generated file from parser
from pynput import keyboard

# @todo:
#   [x] multiple plots
#   [ ] multiple trigger expressions
#   [ ] read in multiple CSV's
#   [ ] get rid of tail
#   [ ] parse binary?

# https://github.com/matplotlib/matplotlib/issues/12692/
# https://stackoverflow.com/questions/4151320/efficient-circular-buffer

TRIM_LENGTH = 1

tim   = []
frm   = []
capture = dict()
capture2 = dict()
plots = dict()
plots2 = dict()
pre_trigger_full = False


def on_press(key):
    print("on press")
#   try: k = key.char # single-char keys
#   except: k = key.name # other keys
#   if key == keyboard.Key.esc: return False # stop listener
#   if k in ['1', '2', 'left', 'right']: # keys interested
#       # self.keys.append(k) # store it in global-like variable
#       print('Key pressed: ' + k)
#       return False # remove this if want more keys

def cross_hair(x, y, ax=None, **kwargs):
    if ax is None:
        ax = plt.gca()
    horiz = ax.axhline(y, **kwargs)
    vert = ax.axvline(x, **kwargs)
    return horiz, vert

def debug_dump(columns):
    for c in columns:
        print(c)
        for v in capture[c]: 
            print(v)

# trigger is a dictionary of key = trigger, value = threshold pairs
def start_capture(trigger, columns, columns2, capture_length, pre_trigger_length):
    print("start capture: {0} @ {1} len {2} pre {3}".format(trigger, columns, columns2, capture_length, pre_trigger_length))

    row_num = 0
    pre_trigger_full = False
    pre_trigger_head = 0
    triggers = trigger.keys()
    thresholds = trigger.values()

    # initialize capture list for each column requested
    # note: we are not capturing trigger columns
    for c in columns: 
        capture[c] = list()    
        plots[c] = None
    for c in columns2: 
        capture2[c] = list()    
        plots2[c] = None

    reader = csv.DictReader(sys.stdin, fieldnames.fieldnames)
    
    counter = 0
    transition = 0
    for row in reader:
        row_num = row_num + 1
        if (row_num < 2):
            continue

        #print(row['framenumber'])

        # pre-trigger
        if (transition == 0):
            #print("accum")
            pre_trigger_head = pre_trigger_head + 1
            frame   = float(row['framenumber'])/100.0
            tim.append(frame)
            frm.append(float(row['framenumber']))
			
            for c in columns: 
                val = row[c]
                capture[c].append(float(val))

            for c in columns2: 
                val = row[c]
                capture2[c].append(float(val))

            if (pre_trigger_head >= pre_trigger_length):
                if (pre_trigger_full == False):
                    pre_trigger_full = True
                    #print("ready")
                    print(pre_trigger_head, " ready ", row['framenumber'])
                #print("popping")
                tim.pop(0)
                frm.pop(0)
                for c in columns: 
                    capture[c].pop(0)
                for c in columns2: 
                    capture2[c].pop(0)

            # check for trigger
            is_triggered = list(filter(lambda k : (float(row[k]) != trigger[k]), triggers))
            if (len(is_triggered)): # if any triggers, then they are in the is_triggered list
                print(row['framenumber'] + " trigger")
                transition = 1
                counter = counter + 1

        if (transition == 1 and counter <= capture_length):
            #print("accumulate: " + str(counter))
            counter = counter + 1
            frame   = float(row['framenumber'])/100.0
            tim.append(frame)
            frm.append(float(row['framenumber']))

            for c in columns: 
                val = row[c]
                capture[c].append(float(val))
            for c in columns2: 
                val = row[c]
                capture2[c].append(float(val))
    
        if counter > capture_length:
            break
        
    # multiple columns per plot
    fig, ax = plt.subplots()
    for c in columns:   
        ax.plot(tim, capture[c], label=c)
    ax.grid()
    ax.legend()
    cross_hair(0.3, 0.3, plt, color='red')
    cross_hair(1.3, 0.1, plt, color='green')
    cross_hair(2.3, 0.2, plt, color='blue')
    plt.text(0.1, 0.3, "yo homi", fontsize=12, rotation=90)
    plt.title('columns1')

    fig, ax2 = plt.subplots()
    for c in columns2:   
        ax2.plot(tim, capture2[c], label=c)
    ax2.grid()
    ax2.legend()
    cross_hair(0.2, 0.3, ax2, color='red')
    cross_hair(1.1, 0.1, ax2, color='green')
    cross_hair(2.3, 0.2, ax2, color='blue')
    plt.text(0.3, 0.3, "sup dawg", fontsize=12, rotation=90)
    plt.title('columns2')

    lis = keyboard.Listener(on_press=on_press)
    lis.start() # start to listen on a separate thread


    print("plotting data")
    plt.draw()
    plt.show(block=True)

    lis.join() # no this if main thread is polling self.keys

# one plot per column
#   for c in columns:   
#       fig, plots[c] = plt.subplots()
#       fig.canvas.set_window_title(c) 
#       plots[c].title.set_text(c)
#       plots[c].plot(tim, capture[c], label=c)
#   for c in columns:   
#       plots[c].grid()
#       plots[c].legend()
#       cross_hair(0.2, 0.3, plots[c], color='red')
#       cross_hair(0.1, 0.1, plots[c], color='green')
#       cross_hair(0.3, 0.2, plots[c], color='blue')
#       plots[c].text(0.3, 0.3, "sup dawg", fontsize=12, rotation=90)
#   plt.draw()
#   print("plotting data")
#   plt.show(block=True)


def my_callback(option, opt, value, parser):
    if (opt == '-t'):
        a = value.split(',')
        b = {}
        for x in a:
            z = x.split(':')
            b[z[0]] = int(z[1])
        setattr(parser.values, option.dest, b)
    elif (opt == '-c'):
        setattr(parser.values, option.dest, value.split(','))
    elif (opt == '-2'):
        setattr(parser.values, option.dest, value.split(','))
    elif (opt == '-f'):
        config = configparser.ConfigParser()
        config.read(value)
        trig = config['trigger_spec']['trigger']
        a = trig.split(',')
        b = {}
        for x in a:
            z = x.split(':')
            b[z[0]] = float(z[1])
        cols  = config['trigger_spec']['columns']
        cols2 = config['trigger_spec']['columns2']
        pret  = int(config['trigger_spec']['pretrig'])
        lgth  = int(config['trigger_spec']['length'])
        setattr(parser.values, 'trigger', b)
        setattr(parser.values, 'columns', cols.split(','))
        setattr(parser.values, 'columns2', cols2.split(','))
        setattr(parser.values, 'pretrig', pret)
        setattr(parser.values, 'length', lgth)
        setattr(parser.values, option.dest, value)

def main():
    parser = OptionParser()

    parser.add_option("-f", "--file_spec",
                      dest = "file_spec",
                      help = "file_spec",
                      type = "string",
                      action = "callback",
                      callback = my_callback
    )

    parser.add_option("-t", "--trigger",
                      dest = "trigger",
                      help = "trigger spec",
                      type = "string",
                      action = "callback",
                      callback = my_callback
    )

    parser.add_option("-c", "--columns",
                      dest = "columns",
                      help = "list of columns to display on trigger",
                      type = "string",
                      action = "callback",
                      callback = my_callback
    )
    parser.add_option("-2", "--columns2",
                      dest = "columns2",
                      help = "2nd list of columns to display on trigger",
                      type = "string",
                      action = "callback",
                      callback = my_callback
    )
    parser.add_option("-l", "--length",
                      dest = "length",
                      help = "capture length",
                      type = "int",
                      action = "store"
    )
    parser.add_option("-p", "--pretrig",
                      dest = "pretrig",
                      help = "pre-trigger capture length",
                      type = "int",
                      action = "store"
    )

    (options, args) = parser.parse_args()

    print("file   : {0}".format(options.file_spec))
    print("trigger: {0}".format(options.trigger))
    print("capture: {0}".format(options.columns))
    print("capture2:{0}".format(options.columns2))
    print("pretrig: {0}".format(options.pretrig))
    print("length : {0}".format(options.length))

    if options.trigger and options.columns and options.length and options.pretrig:
        return start_capture(options.trigger, options.columns, options.columns2, options.length, options.pretrig)
    else:
        parser.print_help()
        raise SystemExit

if __name__ == '__main__':
    try:
        pid = os.getpid()
        ppid = psutil.Process(os.getpid()).ppid()
        main()
        print("exiting...{0} {1}".format(ppid, pid))
        # need to send EOF (^D) to parent process
        #os.kill(ppid, signal.CTRL_D_EVENT)
        #os.kill(ppid, signal.CTRL_BREAK_EVENT)
        #os.kill(pid, signal.CTRL_C_EVENT)
        #os.kill(pid, signal.SIGINT)
    except Exception as e:
        print("Exception occured running main():")
        print(str(e))

