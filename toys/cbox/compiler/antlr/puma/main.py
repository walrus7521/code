#!/usr/bin/env python3

import sys
from antlr4 import *
from antlr4.InputStream import InputStream

from PUMALexer import PUMALexer
from PUMAParser import PUMAParser
from PUMAListener import PUMAListener

from ctypes import *

#class Log(Structure):
#    _fields_ = [("id",   w_char_p)]

class PUMALoader(PUMAListener):
    def __init__(self):
        super().__init__()
        self.props = {}

    def exitPuma(self, ctx):
        print("exit puma")
        #self.props[ctx.ID().getText()] = ctx.STRING().getText()

    def enterActivate(self, ctx):
        print("enter activate")

    def exitActivate(self, ctx):
        print("exit activate")

    def exitLog(self, ctx):
        print(ctx.ID().getText(), ctx.QUEST().getText(), ctx.adr().getText(), ctx.NUM().getText())
#        log = Log(id=ctx.ID().getText()) 
#                  quest=int(ctx.QUEST().getText()),
#                  adr=int(ctx.adr().getText()))
        print("exit log")

        
    def show(self):
        for (key, value) in self.props.items():
            print(key, '=>', value)

if __name__ == '__main__':
    if len(sys.argv) > 1:
        input_stream = FileStream(sys.argv[1])
    else:
        input_stream = InputStream(sys.stdin.read())

    lexer = PUMALexer(input_stream)
    token_stream = CommonTokenStream(lexer)
    parser = PUMAParser(token_stream)
    tree = parser.puma()

    walker = ParseTreeWalker()
    listener = PUMALoader()
    walker.walk(listener, tree)

    listener.show()
