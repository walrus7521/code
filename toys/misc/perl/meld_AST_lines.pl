#!/usr/bin/perl

@array;
$in = 0;
$save_line;
while (<>) {
    $line = $_;
    chomp($line);
restart:
    if ($in == 0 && $line =~ /^@\d+/i) {
        $in = 1;
        push(@array, $line);
    }
    elsif ($in == 0 && $line !~ /^@\d+/i) {
        print "!!!! bogus state !!!!!\n";
    }
    elsif ($in == 1 && $line !~ /^@\d+/i) {
        push(@array, $line);
    }
    elsif ($in == 1 && $line =~ /^@\d+/i) {
        $in = 0;
        while (@array) {
            print shift @array;
        }
        print "\n";
        goto restart;
    }
}
