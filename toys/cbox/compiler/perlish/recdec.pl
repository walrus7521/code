#!/usr/bin/perl -w

use strict;
use Parse::RecDescent;
use Data::Dumper;

# Enable warnings within the Parse::RecDescent module.
$::RD_ERRORS = 1; # Make sure the parser dies when it encounters an error
$::RD_WARN   = 1; # Enable warnings. This will warn on unused rules &c.
$::RD_HINT   = 1; # Give out hints to help fix problems.

our @stack        = (); # path accumulation stack (struct names by nesting)
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

    typedecl : (NUM) ('|') (PRIM) (ID)
              {     my $indent = $itempos[3]{offset}{from}; 
                    my $offset = $item[1];
                    my $type   = $item[3];
                    my $id     = $item[4];
                    our $bit_count = 0;
                    my @args = ();
                    push(@args, (0, $indent, $offset, $id, $type, -1, -1));
                    #print "1:   (@args)\n"; 
                    return main::term(@args);
              }
             | (NUM) ('|') (ID) (ID)
              {     my $indent = $itempos[3]{offset}{from};
                    my $offset = $item[1];
                    my $type   = $item[3];
                    my $id     = $item[4];
                    #print "2 - ($indent): $offset, $type, $id\n"; 
                    return main::non_term($indent, $id);
              }
             | (NUM)':'(NUM)'-'(NUM) ('|') (ID) (ID)
              {     my $indent    = $itempos[3]{offset}{from};
                    my $offset    = $item[1];
                    my $bit_start = $item[3];
                    my $bit_end   = $item[5];
                    my $bit_width = abs(int($bit_start) - int($bit_end)) + 1;
                    my $type      = $item[7];
                    my $id        = $item[8];
                    our $bit_count;
                    my @args = ();
                    push(@args, (0, $indent, $offset, $id, $type, $bit_count, $bit_width));
                    #print "3 - (@args)\n"; 
                    my $ret = main::term(@args);
                    $bit_count++;
                    return $ret;
              }
             | (NUM) ('|') (ID)
              {
                    our @stack = (); # clear path accum stack
                    print "$item[3]\n"; 
              }

    startrule: typedecl(s)

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
    shift;
    my ($this_level, $offset, $id, $type, $bt_count, $bt_width) = @_;
    our $delta_levels = $this_level - $last_level;
    if ($delta_levels < 0) { 
        pop(@stack); 
    }
    if ($id !~ /flags/i) {
        my $path = get_path();
        if ($bt_count ge 0) {
            if ($path eq "") {
                printf("%10d, %s, BOOLEAN_Type:%d-%d\n", $offset, $id, $bt_count, $bt_width);
            } else {
                printf("%10d, %s.%s, BOOLEAN_Type:%d-%d\n", $offset, $path, $id, $bt_count, $bt_width);
            }
        } else {
            if ($path eq "") {
                printf("%10d, %s, %s\n", $offset, $id, $type);
           } else {
                printf("%10d, %s.%s, %s\n", $offset, $path, $id, $type);
            }
        }
    }
    our $last_level = $this_level;
}

sub non_term {
    my $this_level = shift;
    my $id = shift;
    our $delta_levels = $this_level - $last_level;
    our @stack;
    if ($id =~ /flags/i) {
#       print "non term flags: $id : $delta_levels\n";
#       pop(@stack); # backup delta_levels of structures
#       pop(@stack); # backup delta_levels of structures
    }
    if ($delta_levels < 0) {
        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
            pop(@stack); # backup delta_levels of structures
        }
    }
    push(@stack, $id); # put the new struct on stack
    $last_level = $this_level;
}

my $parser = Parse::RecDescent->new($grammar);
while (<>) {
    $parser->startrule($_);
}

