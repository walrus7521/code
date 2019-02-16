#!/usr/bin/env python3

# https://github.com/tanium/pytan/blob/master/EXAMPLES

import os
import sys
import tempfile
import pprint
import traceback

# disable python from generating a .pyc file
sys.dont_write_bytecode = True

# Determine our script name, script dir
my_file = os.path.abspath(sys.argv[0])
my_dir = os.path.dirname(my_file)
my_path = "dude you suck"

print("dir:{0}, file:{1}".format(my_dir, my_file))

path_adds = [my_file, my_dir, my_path]
path = []

def dude(): # generator
    return ["x","y","z"]

#[path.append(aa) for aa in path_adds if aa not in path]
[path.append(aa) for aa in dude()]
for p in path:
    print("path: {0}".format(p))

# create a dictionary of arguments for the pytan handler
handler_args = {}

# establish our connection info for the Tanium Server
handler_args['username'] = "Administrator"
handler_args['password'] = "Tanium2015!"
handler_args['host'] = "10.0.1.240"
handler_args['port'] = "443"  # optional

# optional, level 0 is no output except warnings/errors
# level 1 through 12 are more and more verbose
handler_args['loglevel'] = 1

# optional, use a debug format for the logging output (uses two lines per log entry)
handler_args['debugformat'] = False

# optional, this saves all response objects to handler.session.ALL_REQUESTS_RESPONSES
# very useful for capturing the full exchange of XML requests and responses
handler_args['record_all_requests'] = True



