#!/usr/bin/env python3

#================================================================
# trivex: Trivial example
# http://infohost.nmt.edu/~shipman/soft/pyparsing/web/small-example.html
#----------------------------------------------------------------

# - - - - -   I m p o r t s

import sys
import pyparsing as pp

# - - - - -   M a n i f e s t   c o n s t a n t s
first = pp.Word(pp.alphas+"_", exact=1)
rest = pp.Word(pp.alphanums+"_")
identifier = first+pp.Optional(rest)

testList = [ # List of test strings    
    # Valid identifiers
    "a", "foo", "_", "Z04", "_bride_of_mothra",
    # Not valid
    "", "1", "$*", "a_#" ]

# - - - - -   m a i n
def main():
    """
    """
    for text in testList:
        test(text)

# - - -   t e s t
def test(s):
    '''See if s matches identifier.
    '''
    print("---Test for '{0}'".format(s))

    try:
        result = identifier.parseString(s)
        print("  Matches: {0}".format(result))
    except pp.ParseException as x:
        print("  No match: {0}".format(str(x)))

# - - - - -   E p i l o g u e
if __name__ == "__main__":
    main()



