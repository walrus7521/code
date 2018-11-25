#!/usr/local/bin/perl
####!/usr/bin/perl

use Text::CSV_XS;

$now = localtime time;
print "$now\n\n";
#FBB29100sinfreq = 0.000000

#$file = "20181116_FreqSweep0_25Hz_no_header.csv";
$file = "20181116_MCPA_STDIO.log";
open(my $fh, '<:encoding(UTF-8)', $file)
    or die "Could not open file '$file' $!";

$count = 0;
@frames = ();
while (<$fh>) {
    chomp;
    if ($_ =~ /FA*B*A*B*(\d+)sinfreq = (\d+\.\d+)/) {
        my $item = {}; # need this for unique instance
        $count++;
        print "freq start $1 => $2\n";
        $item->{Frame}     = $1;
        $item->{Frequency} = $2;
        push @frames, $item;
      }
}

foreach (@frames) {
    printf("> %s => %s\n", $_->{Frame}, $_->{Frequency});
}

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
#   if ($transition == 0 && $_->[2] != 0) {
#       $transition = 1;
#       print "going hi: $_->[0]\n";
#   } elsif ($transition != 0 && $_->[2] == 0) {
#       $transition = 0;
#       print "going lo: $_->[0]\n";
#   }
    print "Frame: $_->[0], $_->[3]\n";
}


