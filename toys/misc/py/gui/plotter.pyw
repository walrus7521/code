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
#       self.grid(row=0, column=0)

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
        self.btnPlot    = tkinter.Button(self, command=self.selectPlot,    text="Plots  .")
        self.btnConfig  = tkinter.Button(self, command=self.selectConfig,  text="Config .")
        self.btnArm     = tkinter.Button(self, command=self.selectArm   ,  text="Arm    .")

        T_startLabel = tkinter.Label(self, text="T_start:",
                anchor=tkinter.W, underline=0)
        T_startScale = tkinter.Scale(self, variable=self.T_start,
                command= self.updateUI, from_=0, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)
    
        T_stopLabel = tkinter.Label(self, text="T_stop:",
                anchor=tkinter.W, underline=0)
        T_stopScale = tkinter.Scale(self, variable=self.T_stop,
                command= self.updateUI, from_=10, to=100,
                resolution=1, orient=tkinter.HORIZONTAL)

        T_degreesLabel = tkinter.Label(self, text="T_degrees:",
                anchor=tkinter.W, underline=0)
        T_degreesScale = tkinter.Scale(self, variable=self.T_degrees,
                command= self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)

        T_TriggerLabel = tkinter.Label(self, text="Trigger:",
                anchor=tkinter.W, underline=0)
        T_TriggerValue = tkinter.Label(self, textvariable=self.T_Trigger,
                relief=tkinter.SUNKEN, anchor=tkinter.E)

        T_ICLabel = tkinter.Label(self, text="T_IC:",
                anchor=tkinter.W, underline=0)
        T_ICValue = tkinter.Scale(self, variable=self.T_IC,
                command= self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)

        T_PlotsLabel = tkinter.Label(self, text="T_Plots:",
                anchor=tkinter.W, underline=0)
        T_PlotsValues = tkinter.Label(self, textvariable=self.T_Plots,
                relief=tkinter.SUNKEN, anchor=tkinter.E)

        NO_FRAMES_PER_CLICK_HORZLabel = tkinter.Label(self, text="fr/clk:",
                anchor=tkinter.W, underline=0)
        NO_FRAMES_PER_CLICK_HORZScale = tkinter.Scale(self, variable=self.NO_FRAMES_PER_CLICK_HORZ,
                command= self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)

        NO_DEG_PER_CLICK_VERTLabel = tkinter.Label(self, text="deg/clk:",
                anchor=tkinter.W, underline=0)
        NO_DEG_PER_CLICK_VERTScale = tkinter.Scale(self, variable=self.NO_DEG_PER_CLICK_VERT,
                command= self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)

        """
        T_startLabel.grid                 (row=0, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_startScale.grid                 (row=0, column=1, padx=2, pady=2, sticky=tkinter.EW)
        self.fieldNamesBox.grid           (row=0, column=2, padx=2, pady=2, sticky=tkinter.E)
        T_stopLabel.grid                  (row=1, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_stopScale.grid                  (row=1, column=1, padx=2, pady=2, sticky=tkinter.EW)
        T_degreesLabel.grid               (row=2, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_degreesScale.grid               (row=2, column=1, padx=2, pady=2, sticky=tkinter.EW)
        NO_FRAMES_PER_CLICK_HORZLabel.grid(row=3, column=0, padx=2, pady=2, sticky=tkinter.W)
        NO_FRAMES_PER_CLICK_HORZScale.grid(row=3, column=1, padx=2, pady=2, sticky=tkinter.EW)
        NO_DEG_PER_CLICK_VERTLabel.grid   (row=4, column=0, padx=2, pady=2, sticky=tkinter.W)
        NO_DEG_PER_CLICK_VERTScale.grid   (row=4, column=1, padx=2, pady=2, sticky=tkinter.EW)
        self.btnTrigger.grid              (row=5, column=1, padx=2, pady=2, sticky=tkinter.EW)
        self.btnPlot.grid                 (row=5, column=2, padx=2, pady=2, sticky=tkinter.W)
        T_ICLabel.grid                    (row=6, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_ICValue.grid                    (row=6, column=1, padx=2, pady=2, sticky=tkinter.EW)
        T_TriggerLabel.grid               (row=7, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_TriggerValue.grid               (row=7, column=1, padx=2, pady=2, sticky=tkinter.EW)
        T_PlotsLabel.grid                 (row=8, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_PlotsValues.grid                (row=8, column=1, padx=2, pady=2, sticky=tkinter.EW)
        self.btnConfig.grid               (row=9, column=0, padx=2, pady=2, sticky=tkinter.W)
        self.btnArm.grid                  (row=10, column=0, padx=2, pady=2, sticky=tkinter.W)
        """

        T_startLabel.place                  (x=  1, y=1)
        T_startScale.place                  (x= 80, y=1)
        T_stopLabel.place                   (x=  1, y=40)
        T_stopScale.place                   (x= 80, y=40)
        T_degreesLabel.place                (x=  1, y=80)
        T_degreesScale.place                (x= 80, y=80)
        NO_FRAMES_PER_CLICK_HORZLabel.place (x=  1, y=120)
        NO_FRAMES_PER_CLICK_HORZScale.place (x= 80, y=120)
        NO_DEG_PER_CLICK_VERTLabel.place    (x=  1, y=160)
        NO_DEG_PER_CLICK_VERTScale.place    (x= 80, y=160)
        T_ICLabel.place                     (x=  1, y=200)
        T_ICValue.place                     (x= 80, y=200)
        self.btnTrigger.place               (x=  1, y=240)
        T_TriggerValue.place                (x= 80, y=240)
        self.btnPlot.place                  (x=  1, y=270)
        T_PlotsValues.place                 (x= 80, y=270)

        self.btnConfig.place                (x=  1, y=320)
        self.btnArm.place                   (x= 80, y=320)
    
        self.fieldNamesBox.place            (x= 200, y=1)
        
        T_startScale.focus_set()
        self.T_Trigger.set("None")
        self.T_Plots.set("None")
        self.updateUI()
        
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
        trigs = self.T_IC.get()
        plots = self.T_Plots.get()
        print(trigs)
        print(plots)

    def selectTrigger(self):
        trig = self.fieldNamesBox.curselection()
        trigstr = self.fieldNamesBox.get(trig[0]) # only 1 so 1st tuple
        self.T_Trigger.set(trigstr)
#self.T_IC.set(trigstr)

    def selectPlot(self):
        trig = self.fieldNamesBox.curselection()
        trigstr = ""
        for t in trig:
            trigstr += self.fieldNamesBox.get(t)
            trigstr += ", "
        self.T_Plots.set(trigstr)

    def updateUI(self, *ignore):
        pass
        """
        amount = self.principal.get() * (
                (1 + (self.rate.get() / 100.0)) ** self.years.get())
        self.amount.set("{0:2f}".format(amount))
        """

    def quit(self, event=None):
        pass
        self.parent.destroy()

app = Tk()
app.geometry("640x760+300+300")
 
path = os.path.join(os.path.dirname(__file__), "images/")
app.title("Plotter")
window = MainWindow(app)
app.mainloop()

