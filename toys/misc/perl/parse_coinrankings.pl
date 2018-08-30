#!/usr/bin/perl
#

print "Rankings:\n";
my $rank = 1;
while (<>) {
    chomp;
    if ($_ =~ /id-(.*)"  class/) {
        print "$rank: $1\n";
        $rank++;
    }
}

