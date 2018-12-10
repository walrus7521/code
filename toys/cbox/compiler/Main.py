#!/usr/local/bin/python

from antlr4 import *
from antlr4.tree.Trees import Trees

from ExprLexer import ExprLexer
from ExprParser import ExprParser
from ExprListener import ExprListener
from ExprVisitor import ExprVisitor

import sys
 
class Listen(ExprListener):     
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

class Visit(ExprVisitor):
    def visitAssign(self, ctx):
        print("visitAssign: ")
        print(ctx.ID())
        val = self.visit(ctx.expr())
        print(val)
        return val

    def visitPrintExpr(self, ctx):
        val = ctx.expr()
        print("visitPrintExpr: ")
        print(val)
        return 0

    def visitInt(self, ctx):
        val = ctx.INT()
        print("visitInt: ")
        print(val)
        return val

    def visitId(self, ctx):
        id = ctx.ID()
        print("visitId: ")
        print(id)
        return 0

    def visitMulDiv(self, ctx):
        left = ctx.expr(0)
        right = ctx.expr(1)
        print("visitMulDiv: ")
        val = 0
        if (ctx.op == MUL):
            val = left*right
        else:
            val = left*right
        print (val)
        return val

    def visitAddSub(self, ctx):
        left = ctx.expr(0)
        right = ctx.expr(1)
        print("visitAddSub: ")
        print (left+right)
        return left+right

    def visitParens(self, ctx):
        print("visitParens: ")


def main(argv):
    input = FileStream(argv[1])
    lexer = ExprLexer(input)
    stream = CommonTokenStream(lexer)
    parser = ExprParser(stream)
    tree = parser.prog()

#   print(Trees.toStringTree(tree, None, parser))    

    print("start listener...")
    listener = Listen()
    walker = ParseTreeWalker()
    walker.walk(listener, tree)

    print("start visitor...")
    evalV = Visit()
    evalV.visit(tree)


 
if __name__ == '__main__':
    main(sys.argv)

