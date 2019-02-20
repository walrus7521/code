#!/usr/bin/env python3

# @run: python3 recdec.py > out
# @todo: add support for arrays

from pyparsing import (
    alphanums, col, alphas, nums, CharsNotIn, Forward, restOfLine, Group, hexnums, OneOrMore,
    Optional, ParseException, White, ParseSyntaxException, Suppress, Word, ZeroOrMore,
    CaselessLiteral, CaselessKeyword, Literal, Regex, LineEnd, Keyword, MatchFirst)
import collections
import argparse
import sys
import os

Struct = collections.namedtuple("Struct", "offset level type name path bit")

file_to_parse = ""
struct_to_parse = ""
structs      = []
path_queue   = [] # path accumulation names by nesting)
this_level   = 0
last_level   = 0
bit_count    = 0
top          = ""
parse_it     = False

def get_path():
    global path_queue
    path = ""
    tmp1 = path_queue.copy()
    while (len(tmp1)): # build path
        path += (tmp1.pop() + ".")
    path = path[:-1] # delete extra dot in path
    return path;

def dump_structs():
    for s in structs:
        if (s.bit >= 0):    print("{0}.{1}, BOOLEAN_Type :{2}".format(s.path, s.name, s.bit))
        elif (len(s.path)): print("{0}.{1}, {2}_Type".format(s.path, s.name, s.type[0]))
        else:               print("{0}, {1}_Type".format(s.name, s.type[0]))

def do_top(tokens):
    global structs, path_queue, top, parse_it
    #print("top: {0}".format(tokens.id))
    if tokens.id == struct_to_parse:
        #print("parsing on")
        parse_it = True
        top = tokens.id
    else:
        #print("parsing off")
        parse_it = False
    structs    = [] # clear out the structs and path queue
    path_queue = []

def do_attrib(tokens):
    global structs, path_queue, top, parse_it
    if (len(structs)):
        #print("STRUCT: {0}".format(top))
        dump_structs()

def do_bits(tokens):
    global structs, bit_count, this_level, last_level, parse_it
    if not parse_it: return
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    path = (get_path() + ".flags_bf")
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, path, bit_count))
    bit_count += 1
    last_level = this_level

def do_term(tokens):
    global structs, this_level, last_level, bit_count, parse_it
    if not parse_it: return
    #print("term: {0}".format(tokens.id))
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    if (bit_count > 0):
        bit_count = 0
    if "flags" in tokens.id: return # ignore names with 'flag' in terminals
    if (delta_levels < 0):
        path_queue.pop()
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, get_path(), -1))
    last_level = this_level

def do_array(tokens):
    global path_queue, structs, bit_count, this_level, last_level, parse_it
    if not parse_it: return
    #print("array: {0} {1}".format(tokens.id, tokens.id2))
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    structs.append(Struct(tokens.num, delta_levels, tokens.id, tokens.id2, get_path(), -1))
    last_level = this_level

def do_struct(tokens):
    global this_level, last_level, bit_count, parse_it
    if not parse_it: return
    #print("struct: {0}".format(tokens.id2))
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    if (bit_count > 0):
        path_queue.pop()        
    if (delta_levels < 0):
        dx = abs(delta_levels)
        while (dx and len(path_queue)):
            path_queue.pop()
            dx -= 1
    path_queue.append(tokens.id2) # push new id on path_queue
    last_level = this_level

### Tokens ###
Types = (F32, U32, S32, U8, BOOLEAN) = map(Keyword, """F32 U32 S32 U8 BOOLEAN""".split())
Types = MatchFirst(list(Types))

TYPE    = Group(F32 | U32 | U8 | BOOLEAN)("type")
INDENT  = White()("white")
NUM     = Word(nums)("num")
NUM2    = NUM("num2")
ID      = Word(alphas+'_', alphanums+'_')("id")
ID2     = ID("id2")
EOL     = LineEnd().suppress()

### Grammar ###
skip      = ((NUM + "|" + INDENT + Word("struct") + Regex(r".*"))
          | (EOL))
attrib    = (INDENT + "|" + "[sizeof" + Regex(r".*"))
array     = (NUM + "|" + INDENT + ID + "[" + NUM2 + "]" + ID2)
terminal  = (NUM + "|" + INDENT + TYPE + ID)
structure = (NUM + "|" + INDENT + ID + ID2)
bitflags  = (NUM + ":" + NUM + "-" + NUM + "|" + INDENT + TYPE + ID)
toplevel  = (NUM + "|" + ID) # top level structure name

terminal.setParseAction(do_term)
structure.setParseAction(do_struct)
toplevel.setParseAction(do_top)
bitflags.setParseAction(do_bits)
array.setParseAction(do_array)
attrib.setParseAction(do_attrib)

decl = ( skip | terminal | array | structure | bitflags | toplevel | attrib )
parser = OneOrMore(decl)

def do_parse(file_name):
    #print("file_to_parse: {0}".format(file_to_parse))
    #print("struct_to_parse: {0}".format(struct_to_parse))
    file = open(file_name, "r")
    try: parser.parseFile(file)
    except ParseException as err:
        print("parse error: {0}".format(err))

def get_file(file_name):
    global file_to_parse
    file_to_parse = file_name

def get_struct(struct_name):
    global struct_to_parse
    struct_to_parse = struct_name

def main():
    aparse = argparse.ArgumentParser()
    aparse.add_argument("-i", help="file name containing AST", required=True, type=get_file)
    aparse.add_argument("-s", help="structure name to parse", required=True, type=get_struct)
    aparse.parse_args()
    do_parse(file_to_parse)

if __name__=='__main__':
    main()

