#!/usr/bin/env python3

import sys
import os
import subprocess
import string
import tkinter as tk
import configparser
from tkinter import Tk, BOTH, ttk
from tkinter.ttk import Frame, Label, Style
#import fieldnames

# ref: https://anzeljg.github.io/rin2/book2/2405/docs/tkinter

BACKGROUND = "light gray"
CAPTURE_FILE = "capture.ini"

class MainWindow(Frame):

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent

        self.master.title("Baby monitor")
        self.pack(fill=BOTH, expand=1)
        Style().configure("TFrame", background=BACKGROUND)

        self.cpu_filter     = "A"               # cpu : A, B, C
        self.mypath         = "."               # path to CSV directory
        self.file_filter    = "_flt_data_" + self.cpu_filter + "_All.csv"  # display only prefixes of CSV files
        self.csv_files      = [""]              # CSV list for CsvSelect control
        self.cpus           = ["MCPA", "MCPB", "MCPC", "ADP"] #
        self.cpu            = self.cpus[0]      # cpu : A, B, C
        self.process        = None # pipe process

        self.T_ProcessVar   = tk.StringVar()    # process variable to measure
        self.T_Trigger      = tk.StringVar()    # CSV field to trigger on
        self.T_Plots        = tk.StringVar()    # list of CSV fields for plot1
        self.T_Plots2       = tk.StringVar()    # list of CSV fields for plot2
        self.CpuSelect      = tk.StringVar()    # string for CPU selection control
        self.CsvSelect      = tk.StringVar()    # string for CSV file selection control

        # Buttons
        self.btnProcessVar  = tk.Button(self, command=self.selectProcessVar, text="ProcVar", width=8, highlightthickness=2).place(x=8,  y=200, height=20)
        self.btnTrigger     = tk.Button(self, command=self.selectTrigger,    text="Trigger", width=8, highlightthickness=2).place(x=8,  y=225, height=20)
        self.btnPlots       = tk.Button(self, command=self.selectPlots,      text="Plots  ", width=8, highlightthickness=2).place(x=8,  y=250, height=20)
        self.btnPlots2      = tk.Button(self, command=self.selectPlots2,     text="Plots2 ", width=8, highlightthickness=2).place(x=8,  y=275, height=20)
        self.btnConfig      = tk.Button(self, command=self.selectConfig,     text="Config ", width=8, highlightthickness=2).place(x=8,  y=300, height=20)
        self.btnArm         = tk.Button(self, command=self.selectArm,        text="Arm    ", width=8, highlightthickness=2).place(x=80, y=300, height=20)
        self.btnKill        = tk.Button(self, command=self.selectKill,       text="Kill   ", width=8, highlightthickness=2).place(x=160,y=300, height=20)

        # Labels
        tk.Label(self, text="Pre trigger:",bg=BACKGROUND, anchor=tk.W, underline=0).place(x=1,y=0)
        tk.Label(self, text="Post trigger:", anchor=tk.W, underline=0, bg=BACKGROUND).place(x=1, y=25)
        tk.Label(self, text="Step input:",bg=BACKGROUND, anchor=tk.W, underline=0).place(x=1, y=50)
        tk.Label(self, text="Trigger level:",bg=BACKGROUND, anchor=tk.W, underline=0).place(x=1,y=75)
        tk.Label(self, text="Dx clk:",bg=BACKGROUND, anchor=tk.W, underline=0).place(x=1,y=100)
        tk.Label(self, text="Dy clk:",bg=BACKGROUND, anchor=tk.W, underline=0).place(x=1,y=150)
        tk.Label(self, textvariable=self.T_ProcessVar,bg=BACKGROUND,width=24, relief=tk.SUNKEN, anchor=tk.E).place(x=80,y=200)
        tk.Label(self, textvariable=self.T_Trigger,bg=BACKGROUND, width=24, relief=tk.SUNKEN, anchor=tk.E).place(x=80,y=225)
        tk.Label(self, textvariable=self.T_Plots,bg=BACKGROUND,width=24, relief=tk.SUNKEN, anchor=tk.E).place(x=80,y=250)
        tk.Label(self, textvariable=self.T_Plots2,bg=BACKGROUND,width=24, relief=tk.SUNKEN, anchor=tk.E).place(x=80,y=275)

        # Text
        self.T_PreTrigger = tk.Text(self, height=1, width=12, highlightthickness=2); self.T_PreTrigger.place(x=80,y=1)
        self.T_PostTrigger = tk.Text(self, height=1, width=12, highlightthickness=2); self.T_PostTrigger.place(x=80, y=25)
        self.T_StepInput = tk.Text(self, height=1, width=12, highlightthickness=2); self.T_StepInput.place(x=80,y=50)
        self.T_TriggerLevel = tk.Text(self, height=1, width=12, highlightthickness=2); self.T_TriggerLevel.place(x=80,y=75)

        # sliders
        self.T_dx_per_click_horz = tk.StringVar(); self.T_dx_per_click_horz.set(0.2)
        dx_per_click_horz_Scale = tk.Scale(self, variable=self.T_dx_per_click_horz,
                command=self.updateUI, from_=0.01, to=1.0,bg=BACKGROUND,highlightthickness=2,
                resolution=0.01, orient=tk.HORIZONTAL)
        dx_per_click_horz_Scale.place(x=80,y=100)

        self.T_dy_per_click_vert = tk.StringVar(); self.T_dy_per_click_vert.set(0.4)
        dy_per_click_vert_Scale = tk.Scale(self, variable=self.T_dy_per_click_vert,
                command=self.updateUI, from_=0.01, to=1.0,bg=BACKGROUND,highlightthickness=2,
                resolution=0.01, orient=tk.HORIZONTAL)
        dy_per_click_vert_Scale.place(x=80,y=150)

        # CSV column names
        #self.fieldNames = tk.StringVar(); self.fieldNames.set(fieldnames.fieldnames)
        #self.fieldNamesBox = tk.Listbox(self, listvariable=self.fieldNames, selectmode=tk.MULTIPLE)
        #self.fieldNamesBox.place(x=200,y=1)

        ### read in existing capture.ini
        self.readConfig()

        # filter the CSV files available to monitor
        self.file_filter = "_flt_data_" + self.cpu_filter + "_All.csv"
        print("filter: ", self.file_filter)
        #print(self.file_filter)
        self.csv_files = []
        for (dirpath, dirnames, filenames) in os.walk(self.mypath):
            for f in filenames:
                if self.file_filter in f:
                    f = f.replace(self.file_filter,"")
                    print('"'+f+'"')
                    self.csv_files.append(f)
            break

        # create drop down boxes for CSVs and CPUs
        #self.Csv_Menu = tk.OptionMenu(self, self.CsvSelect, *self.csv_files, command=self.selectCsv)
        #self.Csv_Menu.config(width=16)
        #self.Csv_Menu.place(x=4,y=330)
        #self.CsvSelect.set(self.csv_files[0])

        #self.Cpu_Menu = tk.OptionMenu(self, self.CpuSelect, *self.cpus, command=self.selectCpu)
        #self.Cpu_Menu.config(width=5)
        #self.Cpu_Menu.place(x=200,y=330)

        #self.T_PreTrigger.focus_set()

        """ 
        parent.bind("<Alt-p>",     lambda *ignore: T_PreTrigger_Scale.focus_set())
        parent.bind("<Alt-r>",     lambda *ignore: T_stopScale.focus_set())
        parent.bind("<Alt-y>",     lambda *ignore: T_degreesScale.focus_set())
        """
        parent.bind("<q>",         lambda *ignore: self.quit())
        parent.bind("<Control-q>", lambda *ignore: self.quit())
        parent.bind("<Escape>",    lambda *ignore: self.quit())
        parent.bind("<Tab>",       self.MyCallback)

    def UpdateCsvList(self):
        menu = self.Csv_Menu["menu"]
        menu.delete(0, "end")
        self.file_filter = "_flt_data_" + self.cpu_filter + "_All.csv"
        self.csv_files = []
        #print("new filt: ", self.file_filter)
        for (dirpath, dirnames, filenames) in os.walk(self.mypath):
            for f in filenames:
                if self.file_filter in f:
                    f = f.replace(self.file_filter,"")
                    print('"'+f+'"')
                    self.csv_files.append(f)
            break
        for string in self.csv_files:
            print('add: ', string)
# try ption_files['menu'].add_command(label=choice,command = tk._setit(var, choice, Change_selection_OptionMenu))
# see: https://stackoverflow.com/questions/51514209/tkinters-optionmenu-callback-doesnt-work-if-the-list-is-changed
            menu.add_command(label=string, command=self.selectCsv)
        self.CsvSelect.set(self.csv_files[0])
            
    def readConfig(self):
        config = configparser.ConfigParser()
        try:
            pass
            config.read(CAPTURE_FILE)
            val = config['trigger_spec']['trigger']
            z = val.split(':')
            self.T_Trigger.set(z[0])
            self.T_TriggerLevel.insert(tk.END, str(z[1]))
            self.T_Plots.set(                 config['trigger_spec']['columns'])
            self.T_Plots2.set(                config['trigger_spec']['columns2'])
            self.T_PreTrigger.insert(tk.END,  config['trigger_spec']['pre_trig'])
            self.T_PostTrigger.insert(tk.END, config['trigger_spec']['post_trig'])
            self.T_StepInput.insert(tk.END,   config['trigger_spec']['step_input'])
            self.T_ProcessVar.set(            config['trigger_spec']['proc_var'])
            self.T_dx_per_click_horz.set(float( config['trigger_spec']['del_x']))
            self.T_dy_per_click_vert.set(float( config['trigger_spec']['del_y']))
            val = str(config['trigger_spec']['csv_file'])
            val = val.replace(self.file_filter,"")
            self.CsvSelect.set(val)
            val = str(config['trigger_spec']['cpu'])
            print("config cpu: ", val)
            tmp = ""
            if val == "MCPA":
                tmp = "A"
            elif val == "MCPB":
                tmp = "B"
            elif val == "MCPC":
                tmp = "C"
            elif val == "ADP":
                tmp = "D"
            print("config set cpu: ", val)
            self.cpu_filter = tmp
            self.cpu = val
            self.CpuSelect.set(val)
            self.CsvSelect.set(tmp)
        except:
            print("no/bad file")
            self.T_Trigger.set("None")
            self.T_Plots.set("None")
            self.T_Plots2.set("None")
            self.CsvSelect.set("None")
            self.CpuSelect.set("None")

    def selectKill(self):
        if self.process == None:
            return
        print("kill: ", self.process.pid)
        subprocess.call(['taskkill', '/F', '/T', '/PID',  str(self.process.pid)])
        self.process = None

    def selectCpu(self, arg):
        tcpu = self.CpuSelect.get()
        if tcpu == "":
            self.cpu_filter = "A"
        elif tcpu == "MCPA":
            self.cpu_filter = "A"
        elif tcpu == "MCPB":
            self.cpu_filter = "B"
        elif tcpu == "MCPC":
            self.cpu_filter = "C"
        elif tcpu == "ADP":
            self.cpu_filter = "D"
        self.cpu = tcpu
        self.UpdateCsvList()
        print("cpu: ", tcpu)

    def selectCsv(self, *args):
        f = self.CsvSelect.get()
        print("csv select: ", f)
        self.CsvSelect.set(f)
        f += self.file_filter

    def selectConfig(self):
        config = configparser.ConfigParser()
        try:
            trigs  = self.T_Trigger.get()
            plots  = self.T_Plots.get()
            plots2 = self.T_Plots2.get()
            start = int(self.T_PreTrigger.get("1.0",tk.END))
            stop  = int(self.T_PostTrigger.get("1.0",tk.END))
            proc_var = self.T_ProcessVar.get()
            step_input = float(self.T_StepInput.get("1.0",tk.END))
            trigger_level = float(self.T_TriggerLevel.get("1.0",tk.END))
            step_horz   = self.T_dx_per_click_horz.get()
            step_vert   = self.T_dy_per_click_vert.get()
            csv_file = str(self.CsvSelect.get()) + self.file_filter
        except:
            print("got an error")
            return

        trig_str = "{:s}:{:f}".format(trigs, trigger_level)
        print("trig: ", trig_str)

        config['trigger_spec'] = {}
        config['trigger_spec']['proc_var']   = proc_var
        config['trigger_spec']['trigger']    = trig_str
        config['trigger_spec']['columns']    = plots
        config['trigger_spec']['columns2']   = plots2
        config['trigger_spec']['pre_trig']   = str(int(start))
        config['trigger_spec']['post_trig']  = str(int(stop))
        config['trigger_spec']['step_input'] = str(step_input)
        config['trigger_spec']['del_x']      = str(float(step_horz))
        config['trigger_spec']['del_y']      = str(float(step_vert))
        config['trigger_spec']['cpu']        = self.cpu
        config['trigger_spec']['csv_file']   = csv_file
        with open('capture.ini', 'w') as configfile:
            config.write(configfile)
        cmd_str = "tail -f " + csv_file + " | python3 plot_pipe77.py -f capture.ini"
        print("cmd: ", cmd_str)
        with open('plot.cmd', 'w') as cmdfile:
            cmdfile.write(cmd_str)
        cmdfile.close()

        print(self.cpu)
        print(trigs)
        print(plots)
        print(plots2)
        print(start)
        print(stop)
        print(proc_var)
        print(step_input)
        print(trigger_level)
        print(step_horz)
        print(step_vert)
        print(csv_file)

    def selectArm(self):
        cmd = "plot.cmd" # note pipe is any executable
        self.process = subprocess.Popen(cmd, shell=False, stdin=None, stdout=None, stderr=None)
        print("arming")

    def selectTrigger(self):
        trig = self.fieldNamesBox.curselection()
        trigstr = self.fieldNamesBox.get(trig[0]) # only 1 so 1st tuple
        self.T_Trigger.set(trigstr)

    def selectProcessVar(self):
        pv = self.fieldNamesBox.curselection()
        pvstr = self.fieldNamesBox.get(pv[0]) # only 1 so 1st tuple
        self.T_ProcessVar.set(pvstr)

    def selectPlots(self):
        plots = self.fieldNamesBox.curselection()
        plots_str = ""
        num = len(plots)
        for p in plots:
            plots_str += self.fieldNamesBox.get(p)
            plots_str += ","
        plots_str = plots_str[:-1]
        self.T_Plots.set(plots_str)

    def selectPlots2(self):
        plots = self.fieldNamesBox.curselection()
        plots_str = ""
        for p in plots:
            plots_str += self.fieldNamesBox.get(p)
            plots_str += ","
        plots_str = plots_str[:-1]
        self.T_Plots2.set(plots_str)

    def MyCallback(self, event):
        widget = self.focus_get()

    def updateUI(self, number):
        pass

    def quit(self, event=None):
        self.parent.destroy()

app = Tk()
app.geometry("420x380") # W x H
path = os.path.join(os.path.dirname(__file__), "images/")
app.title("Plotter")
window = MainWindow(app)
app.mainloop()

