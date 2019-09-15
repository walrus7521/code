#!/usr/bin/env python3

import sys
import os
import tkinter

import fieldnames


class MainWindow(tkinter.Frame):

    def __init__(self, parent):
        super().__init__(parent)
        self.parent = parent
        self.grid(row=0, column=0)

        fields = fieldnames.fieldnames

        self.T_start = tkinter.DoubleVar()
        self.T_start.set(0.0)
        self.T_stop = tkinter.DoubleVar()
        self.T_stop.set(10.0)
        self.T_degrees = tkinter.DoubleVar()
        self.T_degrees.set(10.0)
        self.NO_FRAMES_PER_CLICK_HORZ = tkinter.IntVar()
        self.NO_FRAMES_PER_CLICK_HORZ.set(1)
        self.NO_DEG_PER_CLICK_VERT = tkinter.IntVar()
        self.NO_DEG_PER_CLICK_VERT.set(1)
        self.fieldNames = tkinter.StringVar()
        self.fieldNames.set(fields)
        self.om = tkinter.Listbox(self, listvariable=self.fieldNames)

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

        NO_FRAMES_PER_CLICK_HORZLabel = tkinter.Label(self, text="FR/CLK HORZ",
                anchor=tkinter.W, underline=0)
        NO_FRAMES_PER_CLICK_HORZScale = tkinter.Scale(self, variable=self.NO_FRAMES_PER_CLICK_HORZ,
                command= self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)

        NO_DEG_PER_CLICK_VERTLabel = tkinter.Label(self, text="DEG/CLK VERT",
                anchor=tkinter.W, underline=0)
        NO_DEG_PER_CLICK_VERTScale = tkinter.Scale(self, variable=self.NO_DEG_PER_CLICK_VERT,
                command= self.updateUI, from_=1, to=10,
                resolution=1, orient=tkinter.HORIZONTAL)

        T_startLabel.grid                 (row=0, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_startScale.grid                 (row=0, column=1, padx=2, pady=2, sticky=tkinter.EW)
        T_stopLabel.grid                  (row=1, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_stopScale.grid                  (row=1, column=1, padx=2, pady=2, sticky=tkinter.EW)
        T_degreesLabel.grid               (row=2, column=0, padx=2, pady=2, sticky=tkinter.W)
        T_degreesScale.grid               (row=2, column=1, padx=2, pady=2, sticky=tkinter.EW)
        NO_FRAMES_PER_CLICK_HORZLabel.grid(row=3, column=0, padx=2, pady=2, sticky=tkinter.W)
        NO_FRAMES_PER_CLICK_HORZScale.grid(row=3, column=1, padx=2, pady=2, sticky=tkinter.EW)
        NO_DEG_PER_CLICK_VERTLabel.grid   (row=4, column=0, padx=2, pady=2, sticky=tkinter.W)
        NO_DEG_PER_CLICK_VERTScale.grid   (row=4, column=1, padx=2, pady=2, sticky=tkinter.EW)
        self.om.grid              (row=5, column=0, padx=2, pady=2, sticky=tkinter.W)

        T_startScale.focus_set()
        self.updateUI()
        
        parent.bind("<Alt-p>",     lambda *ignore: T_startScale.focus_set())
        parent.bind("<Alt-r>",     lambda *ignore: T_stopScale.focus_set())
        parent.bind("<Alt-y>",     lambda *ignore: T_degreesScale.focus_set())
        parent.bind("<Control-q>", lambda *ignore: self.quit())
        parent.bind("<Escape>",    lambda *ignore: self.quit())


    def updateUI(self, *ignore):
        pass
        """
        amount = self.principal.get() * (
                (1 + (self.rate.get() / 100.0)) ** self.years.get())
        self.amount.set("{0:2f}".format(amount))
        """

    def quit(self, event=None):
        self.parent.destroy()


application = tkinter.Tk()
path = os.path.join(os.path.dirname(__file__), "images/")
#if sys.platform.startswith("win"):
#    icon = path + "interest.ico"
#else:
#    icon = "@" + path + "interest.xbm"
#application.iconbitmap(icon)
application.title("Plotter")
window = MainWindow(application)
#application.protocol("WM_DELETE_WINDOW". window.quit)
application.mainloop()


