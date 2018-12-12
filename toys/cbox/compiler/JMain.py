#!/usr/local/bin/python

import sys
from antlr4 import *
from antlr4.InputStream import InputStream

from JavaLexer import JavaLexer
from JavaListener import JavaListener
from JavaParser import JavaParser

class Listen(JavaListener):     
    def __init__(self, parser: JavaParser):
        self.parser = parser

    def enterClassDeclaration(self, ctx):         
        print('interface I', ctx.Identifier(), '{', sep='')

    def exitClassDeclaration(self, ctx):         
        print('}')

    def enterMethodDeclaration(self, ctx: JavaParser.MethodDeclarationContext):
        dt = 'void'
        dt_ctx = ctx.datatype()
        if dt_ctx is not None:
            dt = self.getAllText(dt_ctx)
        args = self.getAllText(ctx.formalParameters())
        print("\t", dt, ' ', ctx.Identifier(), args, ';', sep='')

    def getAllText(self, ctx): #include hidden channel
        token_stream = ctx.parser.getTokenStream()
        lexer = token_stream.tokenSource
        input_stream = lexer.inputStream
        start = ctx.start.start
        stop = ctx.stop.stop
        return input_stream.getText(start, stop)

def main(argv):

    if len(sys.argv) > 1:
        input = FileStream(argv[1])
    else:
        input = InputStream(sys.stdin.readline())

    lexer = JavaLexer(input)
    stream = CommonTokenStream(lexer)
    parser = JavaParser(stream)
    tree = parser.compilationUnit()

#   lisp_tree_str = tree.toStringTree(recog=parser)
#   print(lisp_tree_str)
#   print(Trees.toStringTree(tree, None, parser))    

    listener = Listen(parser)
    walker = ParseTreeWalker()
    walker.walk(listener, tree)

 
if __name__ == '__main__':
    main(sys.argv)

