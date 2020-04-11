#!/usr/bin/env python

import facebook
import json

def pp(o):
    print(json.dumps(o, indent=1))

g = facebook.GraphAPI(ACCESS_TOKEN, version='2.7')

pp(g.get_object('me'))

