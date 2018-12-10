#!/usr/local/bin/python

from antlr4 import *
from antlr4.tree.Trees import Trees

from ExprLexer import ExprLexer
from ExprParser import ExprParser
from ExprListener import ExprListener

import sys
 
class ExprPrinter(ExprListener):     
    def enterProg(self, ctx):         
        print("enterProg baby!") 

    def exitProg(self, ctx):         
        print("exitProg baby!") 

    def enterStat(self, ctx):         
        print("enterStat baby!") 

    def exitStat(self, ctx):         
        print("exitStat baby!") 

    def enterExpr(self, ctx):         
        print("enterExpr baby!") 

    def exitExpr(self, ctx):         
        print("exitExpr baby!") 

def main(argv):
    input = FileStream(argv[1])
    lexer = ExprLexer(input)
    stream = CommonTokenStream(lexer)
    parser = ExprParser(stream)
    tree = parser.prog()

#   print(Trees.toStringTree(tree, None, parser))    

    printer = ExprPrinter()
    walker = ParseTreeWalker()
    walker.walk(printer, tree)

 
if __name__ == '__main__':
    main(sys.argv)

