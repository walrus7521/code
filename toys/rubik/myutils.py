#!/usr/bin/env python3

import scons

def build_id():
    """Return a build ID (stub version)"""
    print("dude")
    return "100"
def MakeWorkDir(workdir):
    """Create the specified dir immediately"""
    print("dup")
    #Execute(Mkdir(workdir))
