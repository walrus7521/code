#!/usr/bin/perl

use strict;
use warnings;
use File::Slurp;

my @dirs            = ('.');
my $directory_count = 0;
my $file_count      = 0;
my $outfile         = 'log.txt';

open my $fh, '>', $outfile or die "can't create logfile; $!";
for my $dir (@dirs) {
    for my $file (read_dir ($dir)) {
        if ( -d "$dir/$file" ) {
            $directory_count++;
        }
        else {
            $file_count++;
        }
    }
    print $fh "Directories: $directory_count\n";
    print $fh "Files: $file_count\n";
}
close $fh;use strict;

