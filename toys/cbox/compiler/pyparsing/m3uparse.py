#!/usr/bin/env python3

"""
BNF

    M3U         ::= '#EXTM3U' ENTRY+
    ENTRY       ::= INFO FILENAME
    INFO        ::= '#EXTINF:' SECONDS ',' TITLE
    SECONDS     ::= -?\d+
    TITLE       ::= .+
    FILENAME    ::= .+
"""

import collections
import re
import ply.lex


Song = collections.namedtuple("Song", "title seconds filename")


lowercase_keys = True

def songs(fh):
    if fh.readline() != "#EXTM3U\n":
        print("this is not a .m3u file")
        return []

    songs = [] # list of Song named tuples
    INFO_RE = re.compile(r"#EXTINF:(?P<seconds>-?\d+),(?P<title>.+)")
    WANT_INFO, WANT_FILENAME = range(2)
    state = WANT_INFO

    for lino, line in enumerate(fh, start=2):
        line = line.strip()
        if not line:
            continue

#        print(line)
        if state == WANT_INFO:
            info = INFO_RE.match(line)
            if info:
                title = info.group("title")
                seconds = int(info.group("seconds"))
                state = WANT_FILENAME
            else:
                print("Failed to parse line {0}: {1}".format(lino, line))
        elif state == WANT_FILENAME:
            songs.append(Song(title, seconds, line))
            title = seconds = None
            state = WANT_INFO
    return songs



fh = open("my.m3u", "r")
song_list = songs(fh)


if song_list:
    for s in song_list:
        print(s.title)

