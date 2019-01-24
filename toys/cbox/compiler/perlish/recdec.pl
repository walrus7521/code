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

    INTEGER   : /[-+]?\d+/      # Signed integers
    TYPE      : /[a-z0-9_]+/i   # Type
    IDENT     : /[a-z_]+/i      # Identifier
    PRIM      : "F32" | "U32"   # Primitive

    space    : <skip:''>
    indent   : space(s?)
    typeDecl : (INTEGER) '|' (PRIM) (TYPE)
              { print "1 - "; return main::typeDecl(@item,$prevcolumn,$thiscolumn) }
             | (INTEGER) '|' (TYPE) (IDENT)
              { print "2 - "; return main::typeDecl(@item,$prevcolumn,$thiscolumn) }
             | (INTEGER) '|' (TYPE)
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


