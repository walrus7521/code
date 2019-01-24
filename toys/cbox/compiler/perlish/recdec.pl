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

    NUM       : /[-+]?\d+/      # numbers
    ID        : /[a-z0-9_]+/i   # Identifier or Type
    PRIM      : /(f32)/i | /(u|s)32/i | /(u|s)16/i | /(u|s)8/i | /(boolean)/i

    space    : <skip:''>
    indent   : space(s?)
    typeDecl : (NUM) '|' (PRIM) (ID)
              { print "1 - "; return main::typeDecl(@item,$prevcolumn,$thiscolumn) }
             | (NUM) '|' (ID) (ID)
              { print "2 - "; return main::typeDecl(@item,$prevcolumn,$thiscolumn) }
             | (NUM) '|' (ID)
              { print "3 - "; return main::typeDecl(@item,$prevcolumn,$thiscolumn) }

    startrule: typeDecl(s)

_EOGRAMMAR_

sub typeDecl {
    shift;
    #print "@_\n";
    my ($offset,$pipe,$type,$id,$col1,$col2) = @_;
    print "$offset : $type : $id\n";
}

my $parser = Parse::RecDescent->new($grammar);

while (<>) {
    #print $_; 
    $parser->startrule($_);
}


