#!/usr/bin/env python3

# todo: bit transitions are broken
#       fix dotted path
#       convert path stack to queue
#       test on full mcp.rec
#       document

from pyparsing import (
    alphanums, col, alphas, nums, CharsNotIn, Forward, restOfLine,
    Group, hexnums, OneOrMore, Optional, ParseException, White,
    ParseSyntaxException, Suppress, Word, ZeroOrMore, CaselessLiteral,
    CaselessKeyword, Literal, Regex, LineEnd)
import pyparsing as pp
import collections

Struct = collections.namedtuple("Struct", "offset level type name path bit")

structs      = []
stack        = [] # path accumulation stack (struct names by nesting)
delta_levels = 0
this_level   = 0
last_level   = 0
bit_count    = 0
top          = ""

def get_path():
    global stack
    tmp1 = stack.copy()
    tmp2 = []
    path = ""
    if (len(stack) == 0): return path
    while (len(tmp1)):
        tmp = tmp1.pop()
        tmp2.append(tmp) # reverse @stack
    while (len(tmp2)): # build path
        val = tmp2.pop()
        path += val
        path += "."
    return path;

def dump_structs():
    for s in structs:
        if (s.bit >= 0):
            print("  {0}.{1} {2} {3}".format(s.path, s.name, s.type, s.bit))
        elif (len(s.path)):
            print("  {0}.{1} {2}".format(s.path, s.name, s.type))
        else:
            print("  {0} {1}".format(s.name, s.type))

def dump_structs2():
    for s in structs:
        print("  {0} '|' {1} {2}".format(s.offset, s.name, s.type))

def do_skip1(tokens):
    #print("skip1")
    pass
    
def do_skip2(tokens):
    #print("skip2")
    pass
    
def do_skip3(tokens):
    #print("skip3")
    pass

def do_skip(tokens):
    global bit_count
    #bit_count = 0
    #print("skip")
    pass
    #for t in tokens:
    #    print(t)

def do_top(tokens):
    global structs, stack, top
    if (len(structs)):
        print("STRUCT: {0}".format(top))
        dump_structs2()
    else:
        top = tokens.id
    structs      = []
    stack        = []
    pass

def do_bits(tokens):
    global bit_count, delta_levels, this_level, last_level
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    #print("bits: delta {0} {1}".format(delta_levels, tokens.id))
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, get_path(), bit_count))
    bit_count += 1
    last_level = this_level

def do_term(tokens):
    global delta_levels, this_level, last_level, bit_count
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    #print("delta: {0} {1}".format(delta_levels, tokens.id))
    if (bit_count > 0):
        bit_count = 0
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
        #print("oldbits: delta {0} {1}".format(delta_levels, tokens.id))
        #bit_count = 0
        stack.pop()        
    if (delta_levels < 0):
        dx = abs(delta_levels)
        while (dx and len(stack)):
            stack.pop()
            dx -= 1
    #print("post: delta {0} {1}".format(delta_levels, tokens.id))
    stack.append(tokens.id) # push new id on stack
    last_level = this_level

Types = (F32, U32, S32, U8, BOOLEAN) = map(pp.Keyword, """F32 U32 S32 U8 BOOLEAN""".split())
Types = pp.MatchFirst(list(Types))

TYPE    = Group(F32 | U32 | U8 | BOOLEAN)("type")
INDENT  = White()("white")
NUM     = Word(nums)("num")
ID      = Word(alphas+'_', alphanums+'_')("id")
EOL     = LineEnd().suppress()

skip1     = (NUM + "|" + INDENT + Word("struct") + Regex(r".*"))
skip2     = (INDENT + "|" + "[sizeof" + Regex(r".*"))
skip3     = (EOL)
skip      = (skip1 | skip2 | skip3)
terminal  = (NUM + "|" + INDENT + TYPE + ID)
structure = (NUM + "|" + INDENT + ID + ID)
bitflags  = (NUM + ":" + NUM + "-" + NUM + "|" + INDENT + TYPE + ID)
toplevel  = (NUM + "|" + ID) # top level structure name

decl = ( skip | terminal | structure | bitflags | toplevel )

skip1.setParseAction(do_skip1)
skip2.setParseAction(do_skip2)
skip3.setParseAction(do_skip3)
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

filename = "mcp.recs" #"telem.rec"
do_parse(filename)
#exit()

