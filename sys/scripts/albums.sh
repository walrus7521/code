#!/bin/bash
#
#   highest filename [howmany]
#
#   Print howmany highest-numbered lines in file filename.
#   The input file is assumed to have lines that start with
#   numbers. Default for howmany is 10.
#
#echo $0, $1, $2
progname=$0
filename=$1
filename=${filename:?"missing."}
howmany=$2
echo -e -n ${header:+"ALBUMS  ARTISTS\n"}
echo prog: $progname, file: $filename, n: $n_highest
sort -nr $filename | head -${howmany:=10}
