#!/usr/bin/perl
use strict;
use warnings;
 
use MyModule qw(add);
 
my $v1 = add(19, 23);
my $v2 = MyModule::add(17, 23);

print "$v1\n";
print "$v2\n";

