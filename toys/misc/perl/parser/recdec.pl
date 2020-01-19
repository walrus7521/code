#!/usr/bin/perl -w

use strict;
use Parse::RecDescent;

# Enable warnings within the Parse::RecDescent module.
$::RD_ERRORS = 1; # Make sure the parser dies when it encounters an error
$::RD_WARN   = 1; # Enable warnings. This will warn on unused rules &c.
$::RD_HINT   = 1; # Give out hints to help fix problems.

our @stack        = (); # path accumulation stack (struct names by nesting)
our $delta_levels = 0;
our $this_level   = 0;
our $last_level   = 0;
our $bit_count    = 0;

my $grammar = do 'grammar.pl'; # load the grammar

sub get_path {
    our @stack;
    my @tmp1 = @stack;
    my @tmp2;
    my $path = "";
    my $val;
    if (@stack == 0) { return ""; }
    while (@tmp1) { my $tmp = pop(@tmp1); push(@tmp2, $tmp); } # reverse @stack
    while (@tmp2) { $val = pop @tmp2; $path .= $val."."; } # build path
    chop($path);
    return $path;
}

sub term {
    shift;
    my ($this_level, $offset, $id, $type, $bt_count, $bt_width) = @_;
    our $delta_levels = $this_level - $last_level;
    if ($delta_levels < 0) { 
        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
            pop(@stack); # backup delta_levels of structures
        }
    }
    if ($id !~ /flags/i) {
        my $path = get_path();
        if ($bt_count ge 0) {
            if ($path eq "") {
                printf("%s, BOOLEAN_Type, %d:%d\n", $id, $bt_count, $offset);
            } else {
                printf("%s.%s, BOOLEAN_Type, %d:%d\n", $path, $id, $bt_count, $offset);
            }
        } else {
            if ($path eq "") {
                printf("%s, %s_Type, %d\n", $id, $type, $offset);
           } else {
                printf("%s.%s, %s_Type, %d\n", $path, $id, $type, $offset);
            }
        }
        our $last_level = $this_level;
    }
}

sub non_term {
    shift;
    my ($this_level, $offset, $id, $type, $rest) = @_;
    our $delta_levels = $this_level - $last_level;
    our @stack;
    my $struct_name = "";
    if ($id =~ /flags/i) {
        if ($type =~ /struct/) {
            $rest =~ /(\b\w+$)/;
            $id = $1;
        }
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

