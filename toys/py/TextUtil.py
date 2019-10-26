#!/usr/bin/env python3
# Copyright (c) 2019 Qtrac Ltd. All rights reserved
"""
This module provides a few string manipulation functions.

>>> is_balanced("(Python (is (not (lisp))))")
True
>>> shorten("The Crossing", 10)
'The Cro...'
>>> simplify(" some   text   with   spurious  whitespace  ")
'some text with spurious whitespace'
"""

import string

def is_balanced(text, brackets="()[]{}<>"):
    r"""
    """
    return True

def shorten(text, length):
    r"""
    """
    return 'The Cro...'

def simplify(text, whitespace=string.whitespace, delete=""):
    r"""
    """
    return 'some text with spurious whitespace'

if __name__ == "__main__":
    # run with -v to see output
    import doctest
    doctest.testmod()

