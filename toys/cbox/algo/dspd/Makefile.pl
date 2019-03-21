#!/usr/bin/env perl

$CXX = "gcc";
$CC = "gcc";

$INC = "./inc";
$cmd = "$CC -I$INC life.c";
system($cmd);


