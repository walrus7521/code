#!/usr/bin/perl
##!/usr/local/bin/perl

use Text::CSV_XS;


sub read_log {
    my $fh = shift; # file handle
    $count = 0;
    @frames;
    while (<$fh>) {
        chomp;
        if ($_ =~ /FA*B*A*B*(\d+)sinfreq = (\d+\.\d+)/) {
            my $item = {}; # need this for unique instance
            $count++;
            $item->{StartFrame} = $1;
            $item->{Frequency} = $2;
            push @frames, $item;
          }
    }
    return \@frames;
}

sub read_csv {
    my $fh = shift; # file handle
    my $csv = Text::CSV_XS->new;
    my @data;
    $hdr = $csv->getline($fh); # skip header
    #foreach (@$hdr) { printf("> %s\n", $_); }
    while (<$fh>) {
        $csv->parse($_);
        push @data, [$csv->fields];
    }
    return \@data;
}

sub write_csv {
    my $frames = shift;
    my $data = shift;

    foreach (@$frames) {
        printf("> %s => %s\n", $_->{StartFrame}, $_->{Frequency});
    }

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
}

sub main {

    if (scalar @ARGV[0] < 1) {
        print "usage: freq_scan 20181116\n";
        exit;
    }

    my $file_prefix = @ARGV[0];
    my $file, $fh;

    $file = $file_prefix . "_MCPA_STDIO.log";
    open($fh, '<:encoding(UTF-8)', $file)
        or die "Could not open file '$file' $!";

    my $frames = read_log($fh); # returns array of frames
    close($fh);

    $file = $file_prefix . "_FreqSweep0_25Hz.csv";
    open($fh, '<:encoding(UTF-8)', $file)
        or die "Could not open file '$file' $!";

    my $data = read_csv($fh); # returns array of csv rows
    close($fh);

    write_csv(\@$frames, \@$data);

}

main();


