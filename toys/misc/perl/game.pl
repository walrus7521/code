#!/usr/bin/perl

# https://www.xaprb.com/blog/2006/10/05/five-great-perl-programming-techniques-to-make-your-life-fun-again

use strict;
use warnings FATAL => 'all';

use Term::ReadKey;
use Term::ANSIColor;

sub display_a { print color('bold blue');     print "I am in display_a\n"; color('reset'); }
sub display_b { print color('red');           print "I am in display_b\n"; color('reset'); }
sub display_c { print color('yellow');        print "I am in display_c\n"; color('reset'); }
sub display_d { print color('green');         print "I am in display_d\n"; color('reset'); }
sub display_e { print color('magenta');       print "I am in display_e\n"; color('reset'); }
sub display_f { print color('blue');          print "I am in display_f\n"; color('reset'); }
sub display_g { print color('cyan');          print "I am in display_g\n"; color('reset'); }
sub display_h { print color('white');         print "I am in display_h\n"; color('reset'); }
sub display_i { print color('bright_cyan');   print "I am in display_i\n"; color('reset'); }
sub display_j { print color('bright_blue');   print "I am in display_j\n"; color('reset'); }
sub display_k { print color('bright_yellow'); print "I am in display_k\n"; color('reset'); }

#print color('bold blue');
#print "This text is bold blue.\n";
#print color('reset');
#print "This text is normal.\n";
#print colored("Yellow on magenta.", 'yellow on_magenta'), "\n";
#print "This text is normal.\n";
#print colored(['yellow on_magenta'], 'Yellow on magenta.', "\n");
#print colored(['red on_bright_yellow'], 'Red on bright yellow.', "\n");
#print colored(['bright_red on_black'], 'Bright red on black.', "\n");
#print "\n";

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
   q => sub { color('reset'); ReadMode('normal'); exit(0) },
};

while ( 1 ) {
   print "Press a key!\n";
   ReadMode('cbreak');
   my $char = ReadKey(10);
   defined $dispatch_for->{$char} && $dispatch_for->{$char}->();
}

