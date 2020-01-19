#!/usr/bin/perl

# https://www.xaprb.com/blog/2006/10/05/five-great-perl-programming-techniques-to-make-your-life-fun-again/
#

use strict;
use warnings FATAL => 'all';

use Term::ReadKey;

sub display_a {
   print "I am in display_a\n";
}

sub display_b {
   print "I am in display_b\n";
}

my $dispatch_for = {
   a => \&display_a,
   b => \&display_b,
   q => sub { ReadMode('normal'); exit(0) },
};

while ( 1 ) {
   print "Press a key!\n";
   ReadMode('cbreak');
   my $char = ReadKey(10);
   defined $dispatch_for->{$char} && $dispatch_for->{$char}->();
}

