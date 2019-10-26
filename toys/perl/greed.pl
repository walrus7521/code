#!/usr/bin/perl

sub sql_wait_times
{
    my @times = (2,5,1,3);    
    unshift @times, 0; # prepend list w/a zero
    my @sorted_times = sort(@times); # sort the list
    my $num_waits = scalar(@sorted_times);
    print "$len => @sorted_times\n";
    $total = 0;
    $sum = 0;
    for (my $i=1; $i < $num_waits; $i++) { 
        for (my $j=0; $j < $i; $j++) {
            print "$sorted_times[$j] ";
            $sum += $sorted_times[$j];
        }
        print "\n";
    }
    print "sum = $sum\n";
}

sql_wait_times;

