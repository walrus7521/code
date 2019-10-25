#!/usr/bin/env python3

import dis # disassemble byte code

seq3 = ['python', '3']
iterator = iter(seq3)

while True:
    try:
        x = iterator.__next__()
        print(x)
    except StopIteration as e:
        print(e)
        break

def loop(seq):
    for x in seq:
        print(x)


dis.dis(loop)

