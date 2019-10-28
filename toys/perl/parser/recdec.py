#!/usr/bin/env python3

# @run: python3 recdec.py > out
# @todo: adapt to input file is AST, e.g. mcp.ast
#        fix unions: e.g. TARGET_VOLTAGE_MONITORS_HW_UNION

from pyparsing import (
    alphanums, col, alphas, nums, CharsNotIn, Forward, restOfLine, Group, hexnums, OneOrMore,
    Optional, ParseException, White, ParseSyntaxException, Suppress, Word, ZeroOrMore,
    CaselessLiteral, CaselessKeyword, Literal, Regex, LineEnd, Keyword, MatchFirst)
import collections
import argparse
import sys
import os

Struct = collections.namedtuple("Struct", "offset level type name path bit")

Key_Types = ["F32", "U32", "U16", "U8", "S32", "S16", "S8", "BOOLEAN", "int"]


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
        if (s.bit >= 0):
            pair = s.path.split('.', 2)
            #print("  => bits pair: {0}".format(pair))
            print("{0}.{1}.{2}, BOOLEAN_Type, {3}:{4}".format(pair[1], pair[2], s.name, pair[0], s.bit))
        elif not any(x in Key_Types for x in s.type): print("{0}, U16_Type, {1}".format(s.name, s.offset)) # enum's here
        elif (len(s.path)): print("{0}.{1}, {2}_Type, {3}".format(s.path, s.name, s.type[0], s.offset))
        else:               print("{0}, {1}_Type, {2}".format(s.name, s.type[0], s.offset))

def do_top(tokens):
    #print("top: {0}".format(tokens.id))
    global structs, path_queue, top, parse_it
    if tokens.id == struct_to_parse:
        parse_it = True
        top = tokens.id
    else:
        parse_it = False
    structs    = [] # clear out the structs and path queue
    path_queue = []

def do_attrib(tokens):
    #print("attrib: {0} {1}".format(tokens.attrib, tokens.all))
    global structs
    if (len(structs)):
        #print("STRUCT: {0}".format(top))
        dump_structs()

def do_bits(tokens):
    global structs, bit_count, this_level, last_level, parse_it
    #print("bits: {0} {1} {2} {3}".format(tokens.type, tokens.id, tokens.num2, bit_count))
    if not parse_it: return
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    path = (get_path() + ".flags_bf")
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, path, bit_count))
    bit_count += 1
    last_level = this_level

def do_term(tokens):
    #print("term: {0} {1}".format(tokens.type, tokens.id))
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
    #print("array: {0} {1}".format(tokens.id, tokens.id2))
    global path_queue, structs, bit_count, this_level, last_level, parse_it
    if not parse_it: return
    #print("array: {0} {1}".format(tokens.id, tokens.id2))
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    structs.append(Struct(tokens.num, delta_levels, tokens.id, tokens.id2, get_path(), -1))
    last_level = this_level

def do_struct(tokens):
    #print("struct: {0} {1}".format(tokens.id, tokens.id2))
    global this_level, last_level, bit_count, parse_it
    is_an_enum = False
    is_a_flag = False
    is_a_type = False
    if "INDEX" in tokens.id: 
        is_an_enum = True
    elif "FLAG" in tokens.id.upper():
        #print("flag type: {0}".format(tokens.id))
        is_a_flag = True
    #elif (tokens.id in Key_Types):
    #    #print("got type", tokens.id)
    #    is_a_type = True
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
    if is_an_enum == True:
        structs.append(Struct(tokens.num, delta_levels, tokens.struct, tokens.id2, get_path(), -1))
    elif is_a_flag == True:
        #print("is a flag type: {0} {1} {2}".format(tokens.id, tokens.id2, tokens.num))
        #structs.append(Struct(tokens.num, delta_levels, tokens.struct, tokens.id, get_path(), -1))
        new_token = tokens.num + "." + tokens.id2
        path_queue.append(new_token) # push new id on path_queue
    #elif is_a_type == True:
    #    structs.append(Struct(tokens.num, delta_levels, tokens.struct, tokens.id2, get_path(), -1))
    else:
        path_queue.append(tokens.id2) # push new id on path_queue
    last_level = this_level

def do_comment(tokens):
    #print("comment")
    pass

### Tokens ###
Types = (F32, U32, U16, U8, S32, S16, S8, BOOLEAN, INT) = map(Keyword, """F32 U32 U16 U8 S32 S16 S8 BOOLEAN int""".split())
Types = MatchFirst(list(Types))

TYPE    = Group(F32 | U32 | U16 | U8 | S32 | S16 | S8 | BOOLEAN | INT)("type")
INDENT  = White()("white")
NUM     = Word(nums)("num")
NUM2    = NUM("num2")
ID      = Word(alphas+'_', alphanums+'_')("id")
ID2     = ID("id2")
EOL     = LineEnd().suppress()
ATTRIB  = Word("[sizeof")("attrib")
ALL     = Regex(r".*")("all")
SPLATS  = Literal("***")
STRUCT  = Word("struct")

### Grammar ###
skip      = ((NUM + "|" + INDENT + STRUCT + ALL) | (EOL))
comment   = SPLATS.suppress() + Optional(restOfLine).setParseAction(do_comment)
attrib    = (INDENT + "|" + ATTRIB + ALL).setParseAction(do_attrib)
array     = (NUM + "|" + INDENT + ID + "[" + NUM2 + "]" + ID2).setParseAction(do_array)
terminal  = (NUM + "|" + INDENT + TYPE + ID).setParseAction(do_term)
structure = (NUM + "|" + INDENT + ID + Optional("*") + ID2).setParseAction(do_struct)
bitflags  = (NUM + ":" + NUM + "-" + NUM + "|" + INDENT + TYPE + ID).setParseAction(do_bits)
toplevel  = (NUM + "|" + ID).setParseAction(do_top) # top level structure name

decl = ( skip | terminal | array | structure | bitflags | toplevel | attrib | comment )
parser = OneOrMore(decl)

def do_parse(file_name):
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

