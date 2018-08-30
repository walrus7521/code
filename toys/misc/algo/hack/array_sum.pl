#!/usr/bin/perl

$n = <STDIN>;
chomp $n;
$arr_temp = <STDIN>;
@arr = split / /,$arr_temp;
chomp @arr;

#print "@arr\n";

my $sum = 0;
for ( @arr ) {
    $sum += $_;
}

print "$sum\n";
