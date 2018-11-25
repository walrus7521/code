#!/usr/bin/perl

# this is faster (written in C) than Text::CSV which was written in Perl
use Text::CSV;

# this file uses format:
# 4270, 0, 2, 0
# 4271, 0, 2, 0
# 4272, 0, 2, 0
# 4273, 0, 2, 0
# 4274, 0, 2, 0
# 4275, 0, 2, 0
#

sub read_csv {
    my $csv = Text::CSV_XS->new;
    my @data;
    while (<STDIN>) {
        $csv->parse($_);
        push @data, [$csv->fields];
    }
    return \@data;
}

sub write_csv {
}

my $data = read_csv;

$transition = 0;
foreach (@$data) {
    if ($transition == 0 && $_->[2] != 0) {
        $transition = 1;
        print "going hi: $_->[0]\n";
    } elsif ($transition != 0 && $_->[2] == 0) {
        $transition = 0;
        print "going lo: $_->[0]\n";
    }
    print "Frame: $_->[0], Cpd: $_->[2]\n";
}


