#!/usr/bin/env python3

from pyparsing import (
    alphanums, alphas, CharsNotIn, Forward, restOfLine,
    Group, hexnums, OneOrMore, Optional, ParseException,
    ParseSyntaxException, Suppress, Word, ZeroOrMore)

def accumulate(tokens):
    key, value = tokens
    key = key.lower() if lowercase_keys else key
    key_values[key] = value

key_values = {}
lowercase_keys = True

left_bracket, right_bracket, equals = map(Suppress, "[]=")
ini_header = left_bracket + CharsNotIn("]") + right_bracket
key_value = Word(alphanums) + equals + restOfLine
key_value.setParseAction(accumulate)
comment = "#" + restOfLine
parser = OneOrMore(ini_header | key_value)
parser.ignore(comment)

def do_parse(file_name):
    file = open(file_name, "r")
    try:
        parser.parseFile(file)
    except ParseException as err:
        print("parse error: {0}".format(err))
        return {}
    return key_values

kv = do_parse("my.pls")

for k in kv:
    print("[{0}] = {1}".format(k, kv[k]))


