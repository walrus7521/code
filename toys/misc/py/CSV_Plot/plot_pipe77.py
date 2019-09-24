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
import numpy as np

# @todo:
#   [x] multiple plots
#   [ ] multiple trigger expressions
#   [ ] read in multiple CSV's
#   [ ] get rid of tail
#   [ ] parse binary?
#   [ ] write CSV

# https://github.com/matplotlib/matplotlib/issues/12692/
# https://stackoverflow.com/questions/4151320/efficient-circular-buffer
# https://matplotlib.org/3.1.1/users/event_handling.html

# globals are evil ;/
tim   = []
frm   = []
capture = dict()
capture2 = dict()
rows = []
plots = dict()
plots2 = dict()
pre_trigger_full = False
trigger_value = 0.0

my_plot = None
my_figure = None

red_cross   = {} #"x":t_zero+1.0, "y":(step_input+start_offset)}
green_cross = {} #"x":t_zero, "y":start_offset}
blue_cross  = {} #"x":knee_time, "y":knee_value}

#def draw_crosshairs(plt, t_zero, start_offset, step_input, knee_time, knee_value):
#    # zero crosshair
#    cross_hair(t_zero, start_offset, plt, color='green')
#    # step_input crosshair
#    cross_hair(t_zero+1.0, (step_input+start_offset), plt, color='red')
#    # 63% crosshair
#    cross_hair(knee_time, knee_value, plt, color='blue', linestyle='--')
#    red_cross['x'] =t_zero+1.0; red_cross['y'] = step_input+start_offset
#    green_cross['x'] = t_zero; green_cross['y'] = start_offset
#    blue_cross['x'] = knee_time; blue_cross['y'] = knee_value

CrossHair_Select = 'g'
CrossHairAxis_Select = 'h'
X_Axis = 2
Y_Axis = 3

def key_press(event):
    global CrossHair_Select, CrossHairAxis_Select
    global X_Axis, Y_Axis
    global my_plot, my_figure
    global red_cross, green_cross, blue_cross
    print('press', event.key)
    return
    if event.key == 'r':
        print('cross red')
        CrossHair_Select = 'r'
    if event.key == 'g':
        print('cross green')
        CrossHair_Select = 'g'
    if event.key == 'b':
        print('cross blue')
        CrossHair_Select = 'b'
    if event.key == 'h':
        print('axis h')
        CrossHairAxis_Select = 'h'
    if event.key == 'v':
        print('axis v')
        CrossHairAxis_Select = 'v'
    if event.key == '?':
        print('selected: ', CrossHair_Select, CrossHairAxis_Select)
    if event.key == 'left':
        print('go left')
        X_Axis += 1
    if event.key == 'right':
        print('go right')
        X_Axis -= 1
    if event.key == 'up':
        print('go up')
        Y_Axis += 1
    if event.key == 'down':
        print('go down')
        Y_Axis -= 1
    print("axes: ", X_Axis, Y_Axis)
    cross_hair(green_cross['x'], green_cross['y'], plt, color='black', linestyle='--')
    #my_plot.remove() # need a list of lines
    #my_plot.set_ydata(Y_Axis)
    #my_plot.set_xdata(X_Axis)
    cross_hair(X_Axis, Y_Axis, plt, color='red')
    my_figure.canvas.draw()

#def key_press(event):
#    print('press', event.key)
#   sys.stdout.flush()
#   if event.key == 'x':
#       visible = xl.get_visible()
#       xl.set_visible(not visible)
#       fig.canvas.draw()

def onclick(event):
    print('%s click: button=%d, x=%d, y=%d, xdata=%f, ydata=%f' %
          ('double' if event.dblclick else 'single', event.button,
           event.x, event.y, event.xdata, event.ydata))

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

def start_capture(proc_var, trigger, columns, columns2, step_input, pre_trigger_length, post_trigger_length, del_x, del_y):

    print("proc_var  : {0}".format(proc_var))
    print("trigger   : {0}".format(trigger))
    print("columns   : {0}".format(columns))
    print("columns2  : {0}".format(columns2))
    print("step_input: {0}".format(step_input))
    print("pre_trig  : {0}".format(pre_trigger_length))
    print("post_trig : {0}".format(post_trigger_length))
    print("del_x     : {0}".format(del_x))
    print("del_y     : {0}".format(del_y))
   
    pos_trigger = False # based on if the step_input is positive or negative
    if (step_input > 0):
        pos_trigger = True
    print("pos_trig  : {0}".format(pos_trigger))

    row_num = 0
    pre_trigger_full = False
    pre_trigger_head = 0
    triggers = trigger.keys()
    thresholds = trigger.values()
    print("triggers  : {0}".format(triggers))
    print("thresholds: {0}".format(thresholds))

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
        #rows.append(row)

        # pre-trigger
        if (transition == 0):
            #print("accum")
            pre_trigger_head = pre_trigger_head + 1
            frame   = float(row['framenumber'])/100.0
            tim.append(frame)
			
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
                for c in columns: 
                    capture[c].pop(0)
                for c in columns2: 
                    capture2[c].pop(0)

            # check for trigger
            if (pos_trigger):
                is_triggered = list(filter(lambda k : (float(row[k]) > trigger[k]), triggers))
            else:
                is_triggered = list(filter(lambda k : (float(row[k]) < trigger[k]), triggers))

            if (len(is_triggered)): # if any triggers, then they are in the is_triggered list
                for k in triggers:
                    print("is triggered: ", is_triggered, ": ", row[k])
                print(row['framenumber'] + " trigger")
                transition = 1
                counter = counter + 1

        if (transition == 1 and counter <= post_trigger_length):
            #print("accumulate: " + str(counter))
            rows.append(row)
            counter = counter + 1
            frame   = float(row['framenumber'])/100.0
            tim.append(frame)

            for c in columns: 
                val = row[c]
                capture[c].append(float(val))
            for c in columns2: 
                val = row[c]
                capture2[c].append(float(val))
    
        if counter > post_trigger_length:
            break
    #"""        
    # multiple columns per plot
    plot_name1 = "plot1_{:d}.png".format(int(100.0 * tim[0]))
    plot_name2 = "plot2_{:d}.png".format(int(100.0 * tim[0]))

    print("start plots")
    time_zero = tim[0]

    ### 2nd plot first
    fig, ax2 = plt.subplots()
    for c2 in columns2:
        ax2.plot(tim, capture2[c2], label=c2)
    ax2.grid()
    ax2.legend()
    plt.text(0.3, 0.3, "plot2", fontsize=12, rotation=90)
    plt.title(plot_name2)
    fig.savefig(plot_name2)


    ### 1st plot second
    fig, ax = plt.subplots()
    line = None
    for c in columns:   
        line, = ax.plot(tim, capture[c], label=c)
    ax.grid()
    ax.legend()
    global my_plot
    my_plot = line
    global my_figure
    my_figure = fig

    ## find time at 0.63 * step
    search_array = capture[proc_var]
    time_zero = pre_trigger_length
    start_offset = np.average(search_array[:time_zero]) # vertical offset -- make avg of pretrigger
    knee_value = (0.63 * step_input) + start_offset
    knee_time = tim[0]
    for i in range(time_zero, len(search_array)):
        print("array[", i, "] = ", search_array[i])
        if (pos_trigger):
            if (search_array[i] > knee_value):
                knee_time = tim[i]
                print("found knee frame: ", tim[i] * 100.0 , ", time: ", tim[i])
                break;
        else:
            if (search_array[i] < knee_value):
                knee_time = tim[i]
                print("found knee frame: ", tim[i] * 100.0 , ", time: ", tim[i])
                break;

    t_zero = tim[pre_trigger_length];

    print("proc var     :", proc_var)
    print("time zero    :", t_zero)
    print("step input   :", step_input)
    print("start offset :", start_offset)
    print("knee time    :", knee_time)
    print("knee val     :", knee_value)
    print("rise time    :", knee_time - t_zero)

    #draw_crosshairs(plt, t_zero, start_offset, step_input, knee_time, knee_value)
    # zero crosshair
    cross_hair(t_zero, start_offset, plt, color='green')
    # step_input crosshair
    cross_hair(t_zero+1.0, (step_input+start_offset), plt, color='red')
    # 63% crosshair
    cross_hair(knee_time, knee_value, plt, color='blue', linestyle='--')

    plt.text(0.1, 0.3, "plot1", fontsize=12, rotation=90)
    plt.title(plot_name1)
    fig.savefig(plot_name1)


    # handle mouse events
    #cid = fig.canvas.mpl_connect('button_press_event', onclick)
    fig.canvas.mpl_connect('key_press_event', key_press)


    print("plotting data")
    # output csv data captured.
    csv_name = "csv_{:d}.csv".format(int(100.0 * tim[0]))
    with open(csv_name, 'w', newline='') as csvfile:
        #writer = csv.DictWriter(csvfile, fieldnames.fieldnames)
        writer = csv.writer(csvfile)
        #writer.writeheader()
        for r in rows: # got a timestamp in the dict (None, [' 15:12:9:673'])
            writer.writerow(r)

    plt.draw()
    plt.show(block=True)

    """
# one plot per column
    for c in columns:   
        fig, plots[c] = plt.subplots()
        fig.canvas.set_window_title(c) 
        plots[c].title.set_text(c)
        plots[c].plot(tim, capture[c], label=c)
        plots[c].grid()
        plots[c].legend()        
    for c in columns2:   
        fig, plots2[c] = plt.subplots()
        fig.canvas.set_window_title(c) 
        plots2[c].title.set_text(c)
        plots2[c].plot(tim, capture2[c], label=c)
        plots2[c].grid()
        plots2[c].legend()
        #cross_hair(0.2, 0.3, plots[c], color='red')
        #cross_hair(0.1, 0.1, plots[c], color='green')
        #cross_hair(0.3, 0.2, plots[c], color='blue')
        #plots[c].text(0.3, 0.3, c, fontsize=12, rotation=90)
    plt.draw()
    print("plotting data")
    plt.show(block=True)
    """

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
        cols    = config['trigger_spec']['columns']
        cols2   = config['trigger_spec']['columns2']
        pret    = int(config['trigger_spec']['pre_trig'])
        post    = int(config['trigger_spec']['post_trig'])
        stepin  = float(config['trigger_spec']['step_input'])
        procvar = config['trigger_spec']['proc_var']
        delx    = int(config['trigger_spec']['del_x'])
        dely    = int(config['trigger_spec']['del_y'])

        setattr(parser.values, 'proc_var', procvar)
        setattr(parser.values, 'trigger', b)
        setattr(parser.values, 'columns', cols.split(','))
        setattr(parser.values, 'columns2', cols2.split(','))
        setattr(parser.values, 'pre_trig', pret)
        setattr(parser.values, 'post_trig', post)
        setattr(parser.values, 'step_input', stepin)
        setattr(parser.values, 'del_x', delx)
        setattr(parser.values, 'del_y', dely)
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

    """
    print("file      : {0}".format(options.file_spec))
    print("proc_var  : {0}".format(options.proc_var))
    print("trigger   : {0}".format(options.trigger))
    print("columns   : {0}".format(options.columns))
    print("columns2  : {0}".format(options.columns2))
    print("step_input: {0}".format(options.step_input))
    print("pre_trig  : {0}".format(options.pre_trig))
    print("post_trig : {0}".format(options.post_trig))
    print("del_x     : {0}".format(options.del_x))
    print("del_y     : {0}".format(options.del_y))
    """

    if options.proc_var and options.trigger and options.columns and options.columns2 and options.step_input and options.pre_trig and options.post_trig and options.del_x and options.del_y:
        try:
            start_capture(options.proc_var, options.trigger, options.columns, options.columns2, options.step_input, options.pre_trig, options.post_trig, options.del_x, options.del_y)
        except Exception as e:
            print(str(e))
        return
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

