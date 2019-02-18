#!/usr/bin/env python3

import collections
from pyparsing import (
    alphanums, alphas, nums, CharsNotIn, Forward, restOfLine,
    Group, hexnums, OneOrMore, Optional, ParseException,
    ParseSyntaxException, Suppress, Word, ZeroOrMore,
    Combine, LineEnd)

#data structure
Song = collections.namedtuple("Song", "title seconds filename")
songs = []

def add_song(tokens):
    songs.append(Song(tokens.title, tokens.seconds, tokens.filename))

lowercase_keys = True

title = restOfLine("title")
filename = restOfLine("filename")
seconds = Combine(Optional("-") + Word(nums)).setParseAction(
    lambda tokens: int(tokens[0]))("seconds")
info = Suppress("#EXTINF:") + seconds + Suppress(",") + title
entry = info + LineEnd() + filename + LineEnd()
entry.setParseAction(add_song)
parser = Suppress("#EXTM3U") + OneOrMore(entry)

def do_parse(file_name):
    file = open(file_name, "r")
    try:
        parser.parseFile(file)
    except ParseException as err:
        print("parse error: {0}".format(err))
        return []
    return songs

song_list = do_parse("my.m3u")

if song_list:
    for s in song_list:
        print(s.title)

