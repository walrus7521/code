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
    startcol : '' { $thiscolumn }    # NEED THE '' TO STEP PAST TOKEN SEP
    endcol   :  { $prevcolumn }              
    typeDecl : (NUM) ('|') (PRIM) (ID)
              { my $indent = $itempos[3]{offset}{from}; 
                print "1 - ($indent): $item[1], $item[2], $item[3], $item[4]\n"; 
                #print "$itempos[2]{offset}{from}\n";
                #print "$itempos[3]{offset}{from}\n";
                #print "$itempos[$item[2]]{column}{to}\n";
                #return main::term(@item,$prevcolumn,$thiscolumn) 
              }
             | (NUM) ('|') (ID) (ID)
              { my $indent = $itempos[3]{offset}{from};
                print "2 - ($indent): $item[1], $item[2], $item[3], $item[4]\n"; 
                #return main::non_term(@item,$prevcolumn,$thiscolumn) 
              }
             | (NUM) ('|') (ID)
              { my $indent = $itempos[1]{offset}{from};
                print "3 - ($indent): $item[1], $item[2], $item[3]\n"; 
                #return main::non_term(@item,$prevcolumn,$thiscolumn) 
              }

    startrule: typeDecl(s)

_EOGRAMMAR_

my @stack = (); # path accumulation stack (struct names by nesting)
sub get_path {
    my @tmp1 = @stack;
    my @tmp2;
    my $path = "";
    if (@stack == 0) { return ""; }
    while (@tmp1) { my $tmp = pop(@tmp1); push(@tmp2, $tmp); } # reverse @stack
    while (@tmp2) { my $val = pop @tmp2; $path = $path . $val . "."; } # build path
    return $path;
}

sub term {
    shift;
    #print "@_\n";
    my $path = get_path();
    my ($offset,$pipe,$type,$id,$col1,$col2) = @_;
    print "TERM: $offset : $type : $id : $path\n";
}
sub non_term {
    shift;
    #print "@_\n";
    my ($offset,$pipe,$type,$id,$col1,$col2) = @_;
    push(@stack, $id);
    print "PROD: $offset : $type : $id\n";
}

my $parser = Parse::RecDescent->new($grammar);

while (<>) {
    #print $_; 
    $parser->startrule($_);
}


