#!/usr/bin/python

import os
from time import sleep
from tkinter import *

import azure
from azure.storage import BlobService
from azure.storage import TableService
from azure.storage import QueueService
from azure.storage import Entity

class TodoList(object):

    def __init__(self, initdir=None):

        self.queue_service = QueueService(account_name='bbb', account_key='xxx')
        self.sw_queue = self.queue_service.create_queue('swqueue')

        self.top = Tk()
        self.label = Label(self.top, text='my Messages')
        self.label.pack()

        self.cwd = StringVar(self.top)

        self.dirl = Label(self.top, fg='blue', font=('Helvietica', 12, 'bold'))
        self.dirl.pack()

        self.dirfm = Frame(self.top)
        self.dirsb = Scrollbar(self.dirfm)
        self.dirsb.pack(side=RIGHT, fill=Y)

        self.dirs = Listbox(self.dirfm, height=35, 
                width=100, yscrollcommand=self.dirsb.set)
        self.dirs.bind('<Double-1>', self.setDirAndGo)
        self.dirsb.config(command=self.dirs.yview)
        self.dirs.pack(side=LEFT, fill=BOTH)
        self.dirfm.pack()

        self.dirn = Entry(self.top, width=50,
                textvariable=self.cwd)
        self.dirn.bind('<Return>', self.doLS);
        self.dirn.pack()

        self.bfm = Frame(self.top)
        self.clr = Button(self.bfm, text='Clear',
                command=self.clrDir,
                activeforeground='white',
                activebackground='blue')

        self.ls = Button(self.bfm,
                text='List Messages',
                command=self.doLS,
                activeforeground='white',
                activebackground='green')

        self.sm = Button(self.bfm,
                text='Send Message',
                command=self.doSM,
                activeforeground='white',
                activebackground='green')

        self.quit = Button(self.bfm, text='Quit',
                command=self.top.quit,
                activeforeground='white',
                activebackground='red')

        self.clr.pack(side=LEFT)
        self.sm.pack(side=LEFT)
        self.ls.pack(side=LEFT)
        self.quit.pack(side=LEFT)
        self.bfm.pack()

        if initdir:
            self.cwd.set(os.curdir)
            self.doLS()

    def clrDir(self, ev=None):
        self.dirs.delete(0, END)
        self.cwd.set('')
        self.queue_service.clear_messages('swqueue')
        self.queue_service.put_message('swqueue', 'learn queues, tables and blobs on azure')
        self.queue_service.put_message('swqueue', 'research DRM format and implement in dbg ext')
        self.queue_service.put_message('swqueue', 'buy island in France')

    def setDirAndGo(self, ev=None):
        top = Toplevel()
        top.title("About this application...")
        msg = Message(top, text="message details")
        msg.pack()
        button = Button(top, text="Dismiss", command=top.destroy)
        button.pack()

        pass

    def doSM(self, ev=None):
        msg = self.dirn.get()
        print("put message ", msg);
        self.queue_service.put_message('swqueue', msg)

    def doLS(self, ev=None):
        result = self.queue_service.get_messages('swqueue', numofmessages=7)
        print("Number of messages: ", len(result))
        for message in result:
            msg = message.insertion_time + ": " + message.message_text
            self.dirs.insert(END, msg)
            #self.queue_service.update_message('swqueue', message.message_id, message.message_text, visibilitytimeout=0, )
        self.dirs.config(selectbackground='LightSkyBlue')


def main():
    d = TodoList(os.curdir)
    mainloop()

if __name__ == '__main__':
    main()
