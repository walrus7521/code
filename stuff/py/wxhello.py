#!/usr/bin/env python
import wx
 
# https://wiki.wxpython.org/Getting%20Started

class App(wx.App):

    def OnInit(self):
        frame = wx.Frame(parent=None, title='dude') # A Frame is a top-level window.
        frame.Show()
        return True

app = App()
app.MainLoop()


