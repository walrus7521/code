#!/usr/bin/perl -w

use strict;
use Parse::RecDescent;
use Data::Dumper;

use vars qw(%VARIABLE);

# Enable warnings within the Parse::RecDescent module.
$::RD_ERRORS = 1; # Make sure the parser dies when it encounters an error
$::RD_WARN   = 1; # Enable warnings. This will warn on unused rules &c.
$::RD_HINT   = 1; # Give out hints to help fix problems.

my $grammar = <<'_EOGRAMMAR_';
   # Terminals (macros that can't expand further)

   OP       : m([-+*/%])      # Mathematical operators
   INTEGER  : /[-+]?\d+/      # Signed integers
   VARIABLE : /\w[a-z0-9_]*/i # Variable

   typeDecl : (INTEGER) '|' (VARIABLE) (VARIABLE)
              { return main::typeDecl(@item) }

   startrule: typeDecl(s)

_EOGRAMMAR_

sub typeDecl {
   shift;
   #print "@_\n";
   my ($offset,$pipe,$type,$id) = @_;
   #print "$offset - $type -> $id\n";
}

my $parser = Parse::RecDescent->new($grammar);

while (<>) {
    #print $_; 
    $parser->startrule($_);
}

#print "        24 |   VECTOR3 mags\n"; $parser->startrule("        24 |   VECTOR3 mags");
#print "        24 |     F32 X\n";      $parser->startrule("        24 |     F32 X");

