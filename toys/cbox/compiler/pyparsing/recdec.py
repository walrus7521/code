#!/usr/bin/env python3

# todo: convert path stack to queue
#       test on full mcp.rec
#       document

from pyparsing import (
    alphanums, col, alphas, nums, CharsNotIn, Forward, restOfLine,
    Group, hexnums, OneOrMore, Optional, ParseException, White,
    ParseSyntaxException, Suppress, Word, ZeroOrMore, CaselessLiteral,
    CaselessKeyword, Literal, Regex)
import pyparsing as pp
import collections

Struct = collections.namedtuple("Struct", "offset level type name path bit")

structs      = []
stack        = [] # path accumulation stack (struct names by nesting)
delta_levels = 0
this_level   = 0
last_level   = 0
bit_count    = 0

def get_path():
    global stack
    tmp1 = stack.copy()
    tmp2 = []
    path = ""
    if (len(stack) == 0): return path
    while (len(tmp1)):
        tmp = tmp1.pop()
        tmp2.append(tmp) # reverse @stack
    while (len(tmp2)):
        val = tmp2.pop()
        path += val
    return path;

def do_skip(tokens):
    global bit_count
    bit_count = 0

def do_top(tokens):
    pass

def do_bits(tokens):
    global bit_count
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, get_path(), bit_count))
    bit_count += 1

def do_term(tokens):
    global delta_levels, this_level, last_level
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    if "flags" in tokens.id: return # ignore names with 'flag' in terminals
    if (delta_levels < 0):
        stack.pop()
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, get_path(), -1))
    last_level = this_level

def do_struct(tokens):
    global delta_levels, this_level, last_level, bit_count
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    if (bit_count > 0):
            stack.pop()        
    if (delta_levels < 0):
        dx = abs(delta_levels)
        while (dx and len(stack)):
            stack.pop()
            dx -= 1
    stack.append(tokens.id) # push new id on stack
    last_level = this_level

Types = (F32, U32, S32) = map(pp.Keyword, """F32 U32 S32""".split())
Types = pp.MatchFirst(list(Types))

TYPE    = Group(F32 | U32)("type")
INDENT  = White()("white")
NUM     = Word(nums)("num")
SKIP    = Word("struct")
ID      = Word(alphas+'_', alphanums+'_')("id")

skip      = (NUM + "|" + INDENT + SKIP + Regex(r".*"))
terminal  = (NUM + "|" + INDENT + TYPE + ID)
structure = (NUM + "|" + INDENT + ID + ID)
bitflags  = (NUM + ":" + NUM + "-" + NUM + "|" + INDENT + TYPE + ID)
toplevel  = Group(NUM + "|" + ID) # top level structure name

decl = ( skip | terminal | structure | bitflags | toplevel )

skip.setParseAction(do_skip)
terminal.setParseAction(do_term)
structure.setParseAction(do_struct)
toplevel.setParseAction(do_top)
bitflags.setParseAction(do_bits)
parser = OneOrMore(decl)

def do_parse(file_name):
    global delta_levels, this_level, last_level
    delta_levels = this_level = last_level = 0
    file = open(file_name, "r")
    try:
        parser.parseFile(file)
    except ParseException as err:
        print("parse error: {0}".format(err))

do_parse("telem.rec")
for s in structs:
    if (s.bit >= 0):
        print("{0}.{1} {2} {3}".format(s.path, s.name, s.type, s.bit))
    elif (len(s.path)):
        print("{0}.{1} {2}".format(s.path, s.name, s.type))
    else:
        print("{0} {1}".format(s.name, s.type))

