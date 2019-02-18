#!/usr/bin/env python3

from pyparsing import Word, alphas

def accumulate(tokens):
    for t in tokens:
        print(t)

greet = Word( alphas ) + "," + Word( alphas ) + "!"
greet.setParseAction(accumulate)

def do_parse(string):
    greet.parseString(string)

hello = "Hello, World!"
str_val = do_parse(hello)
print(str_val)

#print(hello, "->", greet.parseString( hello ))
