#!/usr/bin/env perl

use strict;
use Parse::RecDescent;
use Data::Dumper;


# https://www.perl.com/pub/2001/06/13/recdecent.html/

use vars qw(%VARIABLE);


# Enable warnings within the Parse::RecDescent module.


$::RD_ERRORS = 1; # Make sure the parser dies when it encounters an error
$::RD_WARN   = 1; # Enable warnings. This will warn on unused rules &c.
$::RD_HINT   = 1; # Give out hints to help fix problems.


my $grammar = <<'_EOGRAMMAR_';


   # Terminals (macros that can't expand further)
   #


   OP       : m([-+*/%])       # Mathematical operators
   INTEGER  : /[-+]?\d+/       # Signed integers
   FLOAT    : /[0-9]+\.[0-9]+/ # simple floating point
   VARIABLE : /\w[a-z0-9_]*/i  # Variable


   expression : INTEGER OP expression
              { return main::expression(@item) }
              | VARIABLE OP expression
              { return main::expression(@item) }
              | INTEGER
              | VARIABLE
              { return $main::VARIABLE{$item{VARIABLE}} }


   print_instruction  : /print/i expression
                      { print $item{expression}."\n" }
   assign_instruction : VARIABLE "=" expression
                      { $main::VARIABLE{$item{VARIABLE}} = $item{expression} }


   instruction : print_instruction
               | assign_instruction

   header :  'puma' {}
   footer :  'end'  {}

   startrule: header
            | instruction(s /;/)


_EOGRAMMAR_


sub expression {
   shift;
   my ($lhs,$op,$rhs) = @_;
   $lhs = $VARIABLE{$lhs} if $lhs=~/[^-+0-9]/;
   return eval "$lhs $op $rhs";
}


my $parser = Parse::RecDescent->new($grammar);


# Add
#    "puma 1.3",
#    "mode(AHCI)",
 
my @lists  = (
    "puma",
    "a=2",
    "f=42",
    "print a",
    "a=1+3",
    "print a",
    "print 5*7",
    "print 2/4",
    "print 2+2/4",
    "print 2+-2/4",
    "a = 5 ; print a",
    "f = f + 3;",
    "print f"
);


foreach my $list(@lists) {
    print $list . ' => ' .
        (defined($parser->startrule($list))?"CORRECT":"INCORRECT") . "\n";
}


