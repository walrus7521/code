#!/usr/bin/perl

use Text::CSV;

sub read_csv {
    my $csv = Text::CSV->new;
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

foreach (@$data) {
    print "$_->[0], $_->[1]\n";
}


