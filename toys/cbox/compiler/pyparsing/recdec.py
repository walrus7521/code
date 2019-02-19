#!/usr/bin/env python3

# @run: python3 recdec.py > out
# @todo: add support for arrays

from pyparsing import (
    alphanums, col, alphas, nums, CharsNotIn, Forward, restOfLine, Group, hexnums, OneOrMore,
    Optional, ParseException, White, ParseSyntaxException, Suppress, Word, ZeroOrMore,
    CaselessLiteral, CaselessKeyword, Literal, Regex, LineEnd, Keyword, MatchFirst)
import collections

Struct = collections.namedtuple("Struct", "offset level type name path bit")

structs      = []
path_queue   = [] # path accumulation names by nesting)
delta_levels = 0
this_level   = 0
last_level   = 0
bit_count    = 0
top          = ""

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
        if (s.bit >= 0):    print("  {0}.{1} {2} {3}".format(s.path, s.name, s.type, s.bit))
        elif (len(s.path)): print("  {0}.{1} {2}".format(s.path, s.name, s.type))
        else:               print("  {0} {1}".format(s.name, s.type))

def do_top(tokens):
    global structs, path_queue, top
    if (len(structs)):
        print("STRUCT: {0}".format(top))
        dump_structs()
    else: top = tokens.id
    structs    = [] # clear out the structs and path queue
    path_queue = []

def do_bits(tokens):
    global bit_count, delta_levels, this_level, last_level
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    path = (get_path() + ".flags_bf")
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, path, bit_count))
    bit_count += 1
    last_level = this_level

def do_term(tokens):
    global delta_levels, this_level, last_level, bit_count
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    if (bit_count > 0):
        bit_count = 0
    if "flags" in tokens.id: return # ignore names with 'flag' in terminals
    if (delta_levels < 0):
        path_queue.pop()
    structs.append(Struct(tokens.num, delta_levels, tokens.type, tokens.id, get_path(), -1))
    last_level = this_level

def do_struct(tokens):
    global delta_levels, this_level, last_level, bit_count
    this_level = len(tokens.white)
    delta_levels = this_level - last_level
    if (bit_count > 0):
        path_queue.pop()        
    if (delta_levels < 0):
        dx = abs(delta_levels)
        while (dx and len(path_queue)):
            path_queue.pop()
            dx -= 1
    path_queue.append(tokens.id) # push new id on path_queue
    last_level = this_level

### Tokens ###
Types = (F32, U32, S32, U8, BOOLEAN) = map(Keyword, """F32 U32 S32 U8 BOOLEAN""".split())
Types = MatchFirst(list(Types))

TYPE    = Group(F32 | U32 | U8 | BOOLEAN)("type")
INDENT  = White()("white")
NUM     = Word(nums)("num")
ID      = Word(alphas+'_', alphanums+'_')("id")
EOL     = LineEnd().suppress()

### Grammar ###
skip     = ((NUM + "|" + INDENT + Word("struct") + Regex(r".*"))
         |  (INDENT + "|" + "[sizeof" + Regex(r".*"))
         |  (EOL))
terminal  = (NUM + "|" + INDENT + TYPE + ID)
structure = (NUM + "|" + INDENT + ID + ID)
bitflags  = (NUM + ":" + NUM + "-" + NUM + "|" + INDENT + TYPE + ID)
toplevel  = (NUM + "|" + ID) # top level structure name

terminal.setParseAction(do_term)
structure.setParseAction(do_struct)
toplevel.setParseAction(do_top)
bitflags.setParseAction(do_bits)

decl = ( skip | terminal | structure | bitflags | toplevel )
parser = OneOrMore(decl)

def do_parse(file_name):
    file = open(file_name, "r")
    try: parser.parseFile(file)
    except ParseException as err:
        print("parse error: {0}".format(err))

filename = "mcp.recs" #"telem.rec"
do_parse(filename)

