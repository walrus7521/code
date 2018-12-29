#!/usr/local/bin/python

from antlr4 import *
from antlr4.tree.Trees import Trees

from ExprLexer import ExprLexer
from ExprParser import ExprParser
from ExprListener import ExprListener
from ExprVisitor import ExprVisitor

import sys
 
class Listen(ExprListener):     
    def __init__(self, parser: ExprParser):
        self.parser = parser

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
    def __init__(self):
        self.memory = {}

    def visitAssign(self, ctx):
        name = ctx.ID().getText()
        value = self.visit(ctx.expr())
        self.memory[name] = value
        return value

    def visitPrintExpr(self, ctx):
        value = self.visit(ctx.expr())
        print(value)
        return 0

    def visitInt(self, ctx):
        value = ctx.INT().getText()
        return value

    def visitId(self, ctx):
        name = ctx.ID().getText()
        if name in self.memory:
            return self.memory[name];
        return 0

    def visitMulDiv(self, ctx):
        left = int(self.visit(ctx.expr(0)))
        right = int(self.visit(ctx.expr(1)))
        if ctx.op.type == ExprParser.MUL:
            return left * right
        return left / right

    def visitAddSub(self, ctx):
        left = int(self.visit(ctx.expr(0)))
        right = int(self.visit(ctx.expr(1)))
        if ctx.op.type == ExprParser.ADD:
            return left + right
        return left - right

    def visitParens(self, ctx):
        return self.visit(ctx.expr())


def main(argv):

    if len(sys.argv) > 1:
        input = FileStream(argv[1])
    else:
        input = InputStream(sys.stdin.readline())

    lexer = ExprLexer(input)
    stream = CommonTokenStream(lexer)
    parser = ExprParser(stream)
    tree = parser.prog()

#   lisp_tree_str = tree.toStringTree(recog=parser)
#   print(lisp_tree_str)
#   print(Trees.toStringTree(tree, None, parser))    

#   print("start listener...")
#   listener = Listen(parser)
#   walker = ParseTreeWalker()
#   walker.walk(listener, tree)

#   print("start visitor...")
    visitor = Visit()
    visitor.visit(tree)

 
if __name__ == '__main__':
    main(sys.argv)

