#!/usr/bin/perl

$n = <STDIN>;
chomp $n;
$arr_temp = <STDIN>;
@arr = split / /,$arr_temp;
chomp @arr;
print "@arr\n";

my (@rev) = reverse (@arr);
print "@rev\n";
