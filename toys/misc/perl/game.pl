#!/usr/bin/perl

# https://www.xaprb.com/blog/2006/10/05/five-great-perl-programming-techniques-to-make-your-life-fun-again

use strict;
use warnings FATAL => 'all';

use Term::ReadKey;

sub display_a { print "I am in display_a\n"; }
sub display_b { print "I am in display_b\n"; }
sub display_c { print "I am in display_c\n"; }
sub display_d { print "I am in display_d\n"; }
sub display_e { print "I am in display_e\n"; }
sub display_f { print "I am in display_f\n"; }
sub display_g { print "I am in display_g\n"; }
sub display_h { print "I am in display_h\n"; }
sub display_i { print "I am in display_i\n"; }
sub display_j { print "I am in display_j\n"; }
sub display_k { print "I am in display_k\n"; }

my $dispatch_for = {
   a => \&display_a,
   b => \&display_b,
   c => \&display_c,
   d => \&display_d,
   e => \&display_e,
   f => \&display_f,
   g => \&display_g,
   h => \&display_h,
   i => \&display_i,
   j => \&display_j,
   k => \&display_k,
   q => sub { ReadMode('normal'); exit(0) },
};

while ( 1 ) {
   print "Press a key!\n";
   ReadMode('cbreak');
   my $char = ReadKey(10);
   defined $dispatch_for->{$char} && $dispatch_for->{$char}->();
}

