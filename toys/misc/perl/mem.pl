#!/usr/bin/perl

use Memoize;

sub iota {
    my $n = shift;
    return [1 .. $n];
}
memoize 'iota';

$i10 = iota(10);
$j10 = iota(10);
pop @$i10;
print @$j10;

