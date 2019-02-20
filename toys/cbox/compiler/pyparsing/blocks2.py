#!/usr/bin/env python3

from pyparsing import (
    alphanums, alphas, CharsNotIn, Forward, restOfLine,
    Group, hexnums, OneOrMore, Optional, ParseException,
    ParseSyntaxException, Suppress, Word, ZeroOrMore)

import Block as blk

"""
class LexError(Exception): pass


class Block:
    def __init__(self, name, color="white"):
        self.name = name
        self.color = color
        self.children = []
    def has_children(self):
        return bool(self.children)

    get_root_block = lambda: Block(None, None)
    get_empty_row = lambda: Block("")
    get_new_row = lambda: None
    is_new_row = lambda x: x is None
"""

def populate_children(items, stack):
    pass

def add_block(tokens):
    return blk.Block(tokens.name, tokens.color 
            if tokens.color else "white")

left_bracket, right_bracket = map(Suppress, "[]")

new_rows = Word("/")("new_rows").setParseAction(
        lambda tokens: len(tokens.new_rows))

name = CharsNotIn("[]/\n")("name").setParseAction(
        lambda tokens: tokens.name.strip())

color = (Word("#", hexnums, exact=7) |
         Word(alphas, alphanums))("color")

empty_node = (left_bracket + right_bracket).setParseAction(
        lambda: EmptyBlock)

nodes = Forward()
node_data = Optional(color + Suppress(":")) + Optional(name)
node_data.setParseAction(add_block)
node = left_bracket - node_data + nodes + right_bracket
nodes << Group(ZeroOrMore(Optional(new_rows) +
                          OneOrMore(node | empty_node)))

def do_parse(file_name):
    file = open(file_name, "r")
    stack = [blk.get_root_block()]
    try:
#       results = nodes.parseString(text, parseAll=True)
        results = nodes.parseFile(file)
        assert len(results) == 1
        items = results.asList()[0]
        populate_children(items, stack)
    except (ParseException, ParseSyntaxException) as err:
        raise ValueError("Error {{0}}: syntax error, line "
                         "{0}".format(err,lineno))
    return stack[0]


blks = do_parse("hierarchy.blk")
print(blks)


