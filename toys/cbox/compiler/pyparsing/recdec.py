#!/usr/bin/env python3

from pyparsing import (
    alphanums, col, alphas, nums, CharsNotIn, Forward, restOfLine,
    Group, hexnums, OneOrMore, Optional, ParseException, White,
    ParseSyntaxException, Suppress, Word, ZeroOrMore, CaselessLiteral,
    CaselessKeyword, Literal, Regex)
import pyparsing as pp
import collections

Struct = collections.namedtuple("Struct", "offset level type name path")

structs      = []
stack        = [] # path accumulation stack (struct names by nesting)
delta_levels = 0;
this_level   = 0;
last_level   = 0;

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
    print("skip")

def do_top(tokens):
    print("top")

def do_bits(tokens):
    print("bits")
    for t in tokens:
        print(t)

def do_term(tokens):
    global delta_levels, this_level, last_level
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
#   print("t: '{0}' - {1}.{2}".format(delta_levels, get_path(), tokens.id))
#   print("{0}.{1}".format(get_path(), tokens.id))
    if (delta_levels < 0):
#       print("poping from t")
        stack.pop()
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, get_path()))
    last_level = this_level

def do_struct(tokens):
    global delta_levels, this_level, last_level
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
#   print("s: '{0}' - {1}".format(delta_levels, tokens.id))
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
    if (len(s.path)):
        print("{0}.{1} {2}".format(s.path, s.name, s.type))
    else:
        print("{0} {1}".format(s.name, s.type))

