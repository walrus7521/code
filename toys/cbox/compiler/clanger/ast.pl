#!/usr/bin/env perl

use Fcntl;

my $filename = shift;

open ( INPUT, $filename ) or
  die "Unable to open $filename: $!";

my $string = shift; # structure to dump
my $hex_ref = "None";

print "Finding: $string\n";

while (<INPUT>) {
    if ($hex_ref eq "None") {
        if ($_ =~ /RecordType.*$string/) { 
            print("$_\n");
            $hex_ref = "Next";
        }
    } elsif ($hex_ref eq "Next") {
        if ($_ =~ /Record (0x[a-fA-F0-9]+)/) { 
            print("$1\n");
            seek INPUT, 0, SEEK_SET;
            $hex_ref = "Dump";       
        }
    } elsif ($hex_ref eq "Dump") {
        if ($_ =~ /RecordDecl/) { 
            print("$1\n");
            $hex_ref = "Fields";
        }
    } elsif ($hex_ref eq "Fields") {
        if ($_ =~ /FieldDecl/) { 
            print("$_");
        }
    }
}
