#!/usr/bin/env perl
#use strict; use warnings;
use PDF::API2;
 
my $filename = 'Cplus2.pdf';
my $oldpdf = PDF::API2->open($filename);
my $newpdf = PDF::API2->new;
my $newfilename = 'dude.pdf';

my $count = $oldpdf->pages();
$start_page = 1;
$end_page = $count/2;
$i = 0;
for $page_nb (1..$oldpdf->pages) {
    $i++;
    print "page: $i\r";
    if ($i < $start_page) {
        continue;
    }
    if ($i >= $end_page) {
        last;
    }
    $page = $newpdf->importpage($oldpdf, $page_nb);
}
 
print "finished: $i\n";
$newpdf->saveas($newfilename);

