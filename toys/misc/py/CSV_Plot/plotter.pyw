#!/usr/bin/env python3

import sys
import os
import subprocess
import string
import tkinter as tk
import configparser
from tkinter import Tk, BOTH, ttk
from tkinter.ttk import Frame, Label, Style
import fieldnames

# ref: https://anzeljg.github.io/rin2/book2/2405/docs/tkinter

BACKGROUND = "light gray"

process = None

class MainWindow(Frame):

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent

        self.master.title("Plot config")
        self.pack(fill=BOTH, expand=1)
        Style().configure("TFrame", background=BACKGROUND) ##333")

        fields = fieldnames.fieldnames # read in fieldnames

        self.T_ProcessVar   = tk.StringVar()
        self.T_Trigger      = tk.StringVar()
        self.T_Plots        = tk.StringVar()
        self.T_Plots2       = tk.StringVar()
        self.CsvFile_Config = tk.StringVar()

        self.T_dx_per_click_horz = tk.IntVar()
        self.T_dx_per_click_horz.set(1)
        self.T_dy_per_click_vert = tk.IntVar()
        self.T_dy_per_click_vert.set(1)

        # ListBox of field names
        # https://www.dreamincode.net/forums/topic/336637-problems-with-tkinter-scrollbar-placing/
        #self.yScroll = tkinter.Scrollbar(self, orient=tkinter.VERTICAL)
        #self.yScroll.configure(width=100)
        #self.yScroll.place(x=320,y=1)
        
        self.fieldNames = tk.StringVar()
        self.fieldNames.set(fields)
        self.fieldNamesBox = tk.Listbox(self, listvariable=self.fieldNames, 
                selectmode=tk.MULTIPLE)

        # Buttons
        self.btnProcessVar  = tk.Button(self, command=self.selectProcessVar, text="ProcVar", width=8, highlightthickness=2)
        self.btnTrigger     = tk.Button(self, command=self.selectTrigger,    text="Trigger", width=8, highlightthickness=2)
        self.btnPlots       = tk.Button(self, command=self.selectPlots,      text="Plots  ", width=8, highlightthickness=2)
        self.btnPlots2      = tk.Button(self, command=self.selectPlots2,     text="Plots2 ", width=8, highlightthickness=2)
        self.btnConfig      = tk.Button(self, command=self.selectConfig,     text="Config ", width=8, highlightthickness=2)
        self.btnCsv         = tk.Button(self, command=self.selectCsv,        text="Csv    ", width=8, highlightthickness=2)
        self.btnArm         = tk.Button(self, command=self.selectArm,        text="Arm    ", width=8, highlightthickness=2)
        self.btnKill        = tk.Button(self, command=self.selectKill,       text="Kill   ", width=8, highlightthickness=2)

        self.btnProcessVar.place(x=8,  y=200, height=20)
        self.btnTrigger.place   (x=8,  y=225, height=20)
        self.btnPlots.place     (x=8,  y=250, height=20)
        self.btnPlots2.place    (x=8,  y=275, height=20)
        self.btnConfig.place    (x=8,  y=300, height=20)
        self.btnCsv.place       (x=80, y=300, height=20)
        self.btnArm.place       (x=160,y=300, height=20)
        self.btnKill.place      (x=240,y=300, height=20)

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
        self.T_PreTrigger = tk.Text(self, height=1, width=12, highlightthickness=2)
        self.T_PreTrigger.place(x=80,y=1)
    
        self.T_PostTrigger = tk.Text(self, height=1, width=12, highlightthickness=2)
        self.T_PostTrigger.place(x=80, y=25)

        self.T_StepInput = tk.Text(self, height=1, width=12, highlightthickness=2)
        self.T_StepInput.place(x=80,y=50)

        self.T_TriggerLevel = tk.Text(self, height=1, width=12, highlightthickness=2)
        self.T_TriggerLevel.place(x=80,y=75)

        # sliders
        dx_per_click_horz_Scale = tk.Scale(self, variable=self.T_dx_per_click_horz,
                command=self.updateUI, from_=1, to=10,bg=BACKGROUND,highlightthickness=2,
                resolution=1, orient=tk.HORIZONTAL)
        dx_per_click_horz_Scale.place(x=80,y=100)

        dy_per_click_vert_Scale = tk.Scale(self, variable=self.T_dy_per_click_vert,
                command=self.updateUI, from_=1, to=10,bg=BACKGROUND,highlightthickness=2,
                resolution=1, orient=tk.HORIZONTAL)
        dy_per_click_vert_Scale.place(x=80,y=150)

        self.fieldNamesBox.place(x=200,y=1)

        ### read in existing capture.ini
        self.readConfig()

        ### scan directory path for csv files
        # add each file into the Menu
        self.cpu = "C"
        self.mypath = "."
        self.file_filter = "_flt_data_" + self.cpu + "_All.csv"
        self.CsvSelect = tk.StringVar()
        csv_files = []
        for (dirpath, dirnames, filenames) in os.walk(self.mypath):
            for f in filenames:
                if self.file_filter in f:
                    f = f.replace(self.file_filter,"")
                    print('"'+f+'"')
                    csv_files.append(f)
            break
        w = tk.OptionMenu(self, self.CsvSelect, *csv_files)
        w.config(width=12)
        w.place(x=4,y=330)
        self.CsvSelect.set(csv_files[0]) # set a default
        ### end of CSV file enumeration


        self.T_PreTrigger.focus_set()
        self.T_Trigger.set("None")
        self.T_Plots.set("None")
        self.T_Plots2.set("None")

        """ 
        parent.bind("<Alt-p>",     lambda *ignore: T_PreTrigger_Scale.focus_set())
        parent.bind("<Alt-r>",     lambda *ignore: T_stopScale.focus_set())
        parent.bind("<Alt-y>",     lambda *ignore: T_degreesScale.focus_set())
        """
        parent.bind("<Control-q>", lambda *ignore: self.quit())
        parent.bind("<Escape>",    lambda *ignore: self.quit())
        parent.bind("<Tab>",       self.MyCallback)


    def readConfig(self):
        config = configparser.ConfigParser()
        try:
            config.read("capture.ini")
            print("got file - populate controls")
        except:
            print("no file")
        pass

    def selectKill(self):
        global process
        print("kill: ", process.pid)
        subprocess.call(['taskkill', '/F', '/T', '/PID',  str(process.pid)])        
        process = None

    def selectArm(self):
        global process
        cmd = "plot.cmd" # note pipe is any executable
        process = subprocess.Popen(cmd, shell=False, stdin=None, stdout=None, stderr=None)
        print("arming")

    def selectCsv(self):
        f = self.CsvSelect.get()
        self.CsvFile_Config.set(f + self.file_filter)
        print("csv: ", self.CsvFile_Config.get())

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
        config['trigger_spec']['del_x']      = str(int(step_horz))
        config['trigger_spec']['del_y']      = str(int(step_vert))
        config['trigger_spec']['csv_file']   = str(self.CsvFile_Config.get())
        with open('capture.ini', 'w') as configfile:
            config.write(configfile)

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
        print(self.CsvFile_Config.get())

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
        #print("focus: ", str(widget))

    def updateUI(self, number):
        pass
#       print("sup: ", self, number)

    def quit(self, event=None):
        self.parent.destroy()

app = Tk()
app.geometry("420x380") # W x H
path = os.path.join(os.path.dirname(__file__), "images/")
app.title("Plotter")
window = MainWindow(app)
app.mainloop()

