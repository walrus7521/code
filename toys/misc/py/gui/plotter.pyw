#!/usr/bin/env python3

import sys
import os
import tkinter
from tkinter import Tk, BOTH
from tkinter.ttk import Frame, Label, Style
import fieldnames

# ref: https://anzeljg.github.io/rin2/book2/2405/docs/tkinter

class MainWindow(Frame):

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent

        self.master.title("Absolute positioning")
        self.pack(fill=BOTH, expand=1)
        Style().configure("TFrame", background="#333")

        fields = fieldnames.fieldnames # read in fieldnames

        self.T_start   = tkinter.DoubleVar()
        self.T_start.set(0.0)
        self.T_stop    = tkinter.DoubleVar()
        self.T_stop.set(10.0)
        self.T_degrees = tkinter.DoubleVar()
        self.T_degrees.set(10.0)
        self.T_IC      = tkinter.DoubleVar()
        self.T_IC.set(4.0)

        self.T_Trigger = tkinter.StringVar()
        self.T_Plots   = tkinter.StringVar()
        self.T_Plots2  = tkinter.StringVar()

        self.NO_FRAMES_PER_CLICK_HORZ = tkinter.IntVar()
        self.NO_FRAMES_PER_CLICK_HORZ.set(1)
        self.NO_DEG_PER_CLICK_VERT = tkinter.IntVar()
        self.NO_DEG_PER_CLICK_VERT.set(1)

        # ListBox of field names
        self.fieldNames = tkinter.StringVar()
        self.fieldNames.set(fields)
        self.fieldNamesBox = tkinter.Listbox(self, listvariable=self.fieldNames, 
                selectmode=tkinter.MULTIPLE)

        # Buttons
        self.btnTrigger = tkinter.Button(self, command=self.selectTrigger, text="Trigger.")
        self.btnPlots   = tkinter.Button(self, command=self.selectPlots,   text="Plots  .")
        self.btnPlots2  = tkinter.Button(self, command=self.selectPlots2,  text="Plots2 .")
        self.btnConfig  = tkinter.Button(self, command=self.selectConfig,  text="Config .")
        self.btnArm     = tkinter.Button(self, command=self.selectArm   ,  text="Arm    .")

        tkinter.Label(self, text="T_start:",
                anchor=tkinter.W, underline=0).place(x=1,y=1)
        T_StartScale = tkinter.Scale(self, variable=self.T_start, 
                command=self.updateUI, from_=0, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)
        T_StartScale.place(x=80,y=1)

        parent.bind("<Tab>", self.MyCallback)
    
        tkinter.Label(self, text="T_stop:",
                anchor=tkinter.W, underline=0).place(x=1, y=40)
        tkinter.Scale(self, variable=self.T_stop,
                command=self.updateUI, from_=10, to=100,
                resolution=1, orient=tkinter.HORIZONTAL).place(x=80, y=40)

        tkinter.Label(self, text="T_degrees:",
                anchor=tkinter.W, underline=0).place(x=1, y=80)
        tkinter.Scale(self, variable=self.T_degrees,
                command=self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL).place(x=80,y=80)

        tkinter.Label(self, text="T_IC:",
                anchor=tkinter.W, underline=0).place(x=1,y=120)
        tkinter.Scale(self, variable=self.T_IC,
                command=self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL).place(x=80,y=120)

        NO_FRAMES_PER_CLICK_HORZLabel = tkinter.Label(self, text="fr/clk:",
                anchor=tkinter.W, underline=0).place(x=1,y=160)
        NO_FRAMES_PER_CLICK_HORZScale = tkinter.Scale(self, variable=self.NO_FRAMES_PER_CLICK_HORZ,
                command=self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL).place(x=80,y=160)

        NO_DEG_PER_CLICK_VERTLabel = tkinter.Label(self, text="deg/clk:",
                anchor=tkinter.W, underline=0).place(x=1,y=200)
        NO_DEG_PER_CLICK_VERTScale = tkinter.Scale(self, variable=self.NO_DEG_PER_CLICK_VERT,
                command=self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL).place(x=80,y=200)

        self.btnTrigger.place(x=1,y=240)
        tkinter.Label(self, textvariable=self.T_Trigger,
                relief=tkinter.SUNKEN, anchor=tkinter.E).place(x=80,y=240)

        self.btnPlots.place(x=1, y=270)
        T_PlotsValues = tkinter.Label(self, textvariable=self.T_Plots,
                relief=tkinter.SUNKEN, anchor=tkinter.E).place(x=80,y=270)

        self.btnPlots2.place(x=  1, y=300)
        T_Plots2Values = tkinter.Label(self, textvariable=self.T_Plots2,
                relief=tkinter.SUNKEN, anchor=tkinter.E).place(x=80,y=300)

        self.btnConfig.place(x=1,y=330)
        self.btnArm.place(x=80,y=330)
        self.fieldNamesBox.place(x=200,y=1)


#       parent.update()
        T_StartScale.focus_set()
        self.T_Trigger.set("None")
        self.T_Plots.set("None")
        self.T_Plots2.set("None")

        """ 
        parent.bind("<Alt-p>",     lambda *ignore: T_startScale.focus_set())
        parent.bind("<Alt-r>",     lambda *ignore: T_stopScale.focus_set())
        parent.bind("<Alt-y>",     lambda *ignore: T_degreesScale.focus_set())
        """
        parent.bind("<Control-q>", lambda *ignore: self.quit())
        parent.bind("<Escape>",    lambda *ignore: self.quit())


    def selectArm(self):
        print("arming")

    def selectConfig(self):
        trigs       = self.T_Trigger.get()
        plots       = self.T_Plots.get()
        plots2      = self.T_Plots2.get()
        start       = self.T_start.get()
        stop        = self.T_stop.get()
        deg         = self.T_degrees.get()
        ic          = self.T_IC.get()
        step_horz   = self.NO_FRAMES_PER_CLICK_HORZ.get()
        step_vert   = self.NO_DEG_PER_CLICK_VERT.get()
        print(trigs)
        print(plots)
        print(plots2)
        print(start)
        print(stop)
        print(deg)
        print(ic)
        print(step_horz)
        print(step_vert)

    def selectTrigger(self):
        trig = self.fieldNamesBox.curselection()
        trigstr = self.fieldNamesBox.get(trig[0]) # only 1 so 1st tuple
        self.T_Trigger.set(trigstr)

    def selectPlots(self):
        plots = self.fieldNamesBox.curselection()
        plots_str = ""
        for p in plots:
            plots_str += self.fieldNamesBox.get(p)
            plots_str += ", "
        self.T_Plots.set(plots_str)

    def selectPlots2(self):
        plots = self.fieldNamesBox.curselection()
        plots_str = ""
        for p in plots:
            plots_str += self.fieldNamesBox.get(p)
            plots_str += ", "
        self.T_Plots2.set(plots_str)

    def MyCallback(self, event):
        widget = self.focus_get()
        print("focus: ", str(widget))
        pass

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

