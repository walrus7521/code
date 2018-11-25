#!/usr/bin/perl
##!/usr/local/bin/perl

use Text::CSV_XS;


sub read_log {
    my $fh = shift;
    $count = 0;
    @frames;
    while (<$fh>) {
        chomp;
        if ($_ =~ /FA*B*A*B*(\d+)sinfreq = (\d+\.\d+)/) {
            my $item = {}; # need this for unique instance
            $count++;
            $item->{Frame}     = $1;
            $item->{Frequency} = $2;
            push @frames, $item;
          }
    }
    return \@frames;
}

sub read_csv {
    my $fh = shift;
    my $csv = Text::CSV_XS->new;
    my @data;
    while (<$fh>) {
        $csv->parse($_);
        push @data, [$csv->fields];
    }
    return \@data;
}

sub write_csv {
}

sub main {
    my $file;
    my $fh;
    $file = "20181116_MCPA_STDIO.log";
    open($fh, '<:encoding(UTF-8)', $file)
        or die "Could not open file '$file' $!";

    my $frames = read_log($fh);

    foreach (@$frames) {
        printf("> %s => %s\n", $_->{Frame}, $_->{Frequency});
    }
    close($fh);

    $file = "20181116_FreqSweep0_25Hz_no_header.csv";
    open($fh, '<:encoding(UTF-8)', $file)
        or die "Could not open file '$file' $!";

    my $data = read_csv($fh);
    close($fh);

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

main();

