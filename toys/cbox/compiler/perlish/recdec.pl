#!/usr/bin/perl -w

use strict;
use Parse::RecDescent;
use Data::Dumper;

use vars qw(%VARIABLE);

# Enable warnings within the Parse::RecDescent module.
$::RD_ERRORS = 1; # Make sure the parser dies when it encounters an error
$::RD_WARN   = 1; # Enable warnings. This will warn on unused rules &c.
$::RD_HINT   = 1; # Give out hints to help fix problems.

our @stack = (); # path accumulation stack (struct names by nesting)
our $delta_levels = 0;
our $this_level   = 0;
our $last_level   = 0;
our $bit_count    = 0;

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
                my $offset = $item[1];
                my $type   = $item[3];
                my $id     = $item[4];
                our $bit_count = 0;
                #print "1 - ($indent): $item[1], $item[2], $item[3], $item[4]\n"; 
                return main::term($indent, $offset, $id, $type) 
              }
             | (NUM) ('|') (ID) (ID)
              { my $indent = $itempos[3]{offset}{from};
                my $type   = $item[3];
                my $id     = $item[4];
                #print "2 - ($indent): $item[1], $item[2], $item[3], $item[4]\n"; 
                return main::non_term($indent, $id) 
              }
             | (NUM)':'(NUM)'-'(NUM) ('|') (ID) (ID) #    124:0-0 |       U32 mag_valid
              { my $indent    = $itempos[3]{offset}{from};
                my $offset    = $item[1];
                my $bit_start = $item[3];
                my $bit_end   = $item[5];
                my $bit_width = abs(int($bit_start) - int($bit_end)) + 1;
                my $type      = $item[7];
                my $id        = $item[8];
                our $bit_count;
                #print "3 - ($indent): $offset:$bit_start-$bit_end - $type, $id : $bit_count\n"; 
                $bit_count++;
                return main::term_bit($indent, $offset, $id, $type, $bit_count) 
              }
             | (NUM) ('|') (ID)
              {
                #print "4 - ($item[1], $item[2], $item[3]\n"; 
              }

    startrule: typeDecl(s)

_EOGRAMMAR_

sub get_path {
    our @stack;
    my @tmp1 = @stack;
    my @tmp2;
    my $path = "";
    if (@stack == 0) { return ""; }
    while (@tmp1) { my $tmp = pop(@tmp1); push(@tmp2, $tmp); } # reverse @stack
    while (@tmp2) { my $val = pop @tmp2; $path = $path . $val; } # build path
    return $path;
}

sub term {
    my $indent = shift;
    my $offset = shift;
    my $id     = shift;
    my $type   = shift;
    our $this_level = $indent;
    our $delta_levels = $this_level - $last_level;
    if ($delta_levels < 0) { pop(@stack); }
    my $path = get_path();
    if ($path eq "") {
        print "$offset, $id, $type\n";
    } else {
        print "$offset, $path.$id, $type\n";
    }
    our $last_level = $this_level;
}
sub term_bit {
    my $indent = shift;
    my $offset = shift;
    my $id     = shift;
    my $type   = shift;
    my $bit_count   = shift;
    our $this_level = $indent;
    our $delta_levels = $this_level - $last_level;
    if ($delta_levels < 0) { pop(@stack); }
    my $path = get_path();
    if ($path eq "") {
        print "$offset, $id, $type : $bit_count\n";
    } else {
        print "$offset, $path.$id, $type : $bit_count\n";
    }
    our $last_level = $this_level;
}

sub non_term {
    my $indent = shift;
    our $this_level = $indent;
    our $delta_levels = $this_level - $last_level;
    my $id     = shift;
    #print "PROD: $delta_levels : $id\n";
    our @stack;
    if ($delta_levels < 0) {
        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
            pop(@stack); # backup delta_levels of structures
        }
        push(@stack, $id); # put the new struct on stack
    } else { push(@stack, $id); }
    $last_level = $this_level;
}

my $parser = Parse::RecDescent->new($grammar);
while (<>) {
    $parser->startrule($_);
}

