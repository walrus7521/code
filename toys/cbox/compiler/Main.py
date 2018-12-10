#!/usr/local/bin/python

from antlr4 import *
from ExprLexer import ExprLexer
from ExprParser import ExprParser
from ExprListener import ExprListener
import sys
 
class KeyPrinter(ExprListener):     
    def exitProg(self, ctx):         
        print("Oh yeah baby, a key!") 

def main(argv):
    input = FileStream(argv[1])
    lexer = ExprLexer(input)
    stream = CommonTokenStream(lexer)
    parser = ExprParser(stream)
    tree = parser.prog()

    printer = KeyPrinter()
    walker = ParseTreeWalker()
    walker.walk(printer, tree)

 
if __name__ == '__main__':
    main(sys.argv)

