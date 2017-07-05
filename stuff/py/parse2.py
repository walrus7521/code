#!/usr/bin/python

# https://www.accelebrate.com/blog/pyparseltongue-parsing-text-with-pyparsing/

from pyparsing import *

# bnf grammar
'''
grammar:
ssn ::= nums+ '-' nums+ '-' nums+
nums ::= '0' | '1' | '2' etc etc
'''
dash = '-'

def process_ssn(tokens):
    print "tokens: {}".format(tokens)
    pass
#   print "hello"
#   return [t.upper() for t in tokens]

ssn_parser = Combine(
  Word(nums, exact=3)
  + dash
  + Word(nums, exact=2)
  + dash
  + Word(nums, exact=4)
)

ssn_parser.setParseAction(process_ssn)

input_string = """
  xxx 225-92-8416 yyy
  103-33-3929 zzz 028-91-0122
  aaa 1234-34-987
  aaa 123-34-9897
"""

#for match, start, stop in ssn_parser.scanString(input_string):
#  print(match, start, stop)


while True:
    input_string = raw_input()
    for match, start, stop in ssn_parser.scanString(input_string):
        print(match, start, stop)


