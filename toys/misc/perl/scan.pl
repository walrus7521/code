#!/usr/bin/perl

while (<>) {
    chomp;
    if ($_ =~ /BT: (.*)/) {
        print "BT: $1\n";
    }
    if ($_ =~ /BAT: (.*)/) {
        print "BAT: $1\n";
    }
}
