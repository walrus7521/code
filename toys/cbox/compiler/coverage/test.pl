#!/usr/bin/perl

#$cmd = "c:\\llvm\\bin\\clang -v -S -Xclang -fdump-record-layouts main.c > main.ast";
$cmd = "c:\\llvm\\bin\\clang -v -S -fprofile-instr-generate -fcoverage-mapping main.c -o main.cov";
system($cmd);

