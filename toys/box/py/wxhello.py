#!/usr/bin/env python
import wx
 
# https://wiki.wxpython.org/Getting%20Started

app = wx.App(False)  # Create a new app, don't redirect stdout/stderr to a window.
frame = wx.Frame(None, wx.ID_ANY, "dude, wusup") # A Frame is a top-level window.
frame.Show(True)     # Show the frame.
app.MainLoop()
