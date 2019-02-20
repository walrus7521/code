#!/usr/bin/env python3

"""
BNF

    BLOCKS      ::= NODES+
    NODES       ::= NEW_ROW* \s* NODE+
    NODE        ::= '[' \s* (COLOR ':')? \s* NAME? \s* NODES* \s* ']'
    COLOR       ::= '#' [\dA-Fa-f]{6} | [a-zA-Z]\w*
    NAME        ::= [^][/]+
    NEW_ROW     ::= '/'
"""

import collections
import re
import ply.lex

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

class Data:
    def __init__(self, text):
        self.text = text
        self.pos = 0
        self.line = 1
        self.column = 1
        self.brackets = 0
        self.stack = [Block.get_root_block()]
    def location(self):
        return "line {0}, column{1}".format(self.line, self.column)
    def advance_by(self, amount):
        for x in range(amount):
            self._advance_by_one()
    def _advance_by_one(self):
        self.pos += 1
        if (self.pos < len(self.text) and
            self.text[self.pos] == "\n"):
            self.line += 1
            self.column = 1
        else:
            self.column += 1
    def advance_to_position(self, position):
        while self.pos < position:
            self._advance_by_one()
    def advance_up_to(self, characters):
        while (self.pos < len(self.text) and
               self.text[self.pos] not in characters and
               self.text[self.pos].isspace()):
            if not self.pos < len(self.text):
                return False
            if self.text[self.pos] in characters:
                return True
            raise LexError("expected '{0}' but got '{1}'"
                    .format(characters, self.text[self.pos]))
    def parse(data):
        while data.pos < len(data.text):
            if not data.advance_up_to("[]/"):
                break
            if data.text[data.pos] == "[":


            
data = Data(text)
try:
    parse(data)
except LexError as err:
    raise ValueError("Error {{0}}{{0}: {1}".format(data.location(), err))

return data.stack[0]


