#!/usr/bin/env python3

import daemon

from spam import do_main_program

with daemon.DaemonContext():
    do_main_program()
