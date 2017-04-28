#!/usr/bin/perl

while (<STDIN>) {
    chomp;
    if ($_ =~ m/hello/i) {
        print "got a hello pattern!!\n";
    }
    print "$_\n";
}
