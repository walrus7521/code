#!/usr/bin/perl

my @file = (); #<STDIN>;
while (<>) {
    chomp;
    my @line = split(/\s+/, $_);
    push(@line, "----");
    #print "@line\n";
    push(@file, @line);
}

#print "@file\n";
#$line = $file->[8];
#$word = $line->[0];

foreach $line (@file) {
    #print "----\n";
    print "$line\n";
#    foreach $word (@line) {
#        print $word;
#    }
#    #print "\n";
}
