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

my $grammar = do 'grammar.pl';

sub get_path {
    our @stack;
    my @tmp1 = @stack;
    my @tmp2;
    my $path = "";
    if (@stack == 0) { return ""; }
    while (@tmp1) { my $tmp = pop(@tmp1); push(@tmp2, $tmp); } # reverse @stack
    while (@tmp2) { my $val = pop @tmp2; $path = $path . $val; } # build path
    print("path: $path\n");
    return $path;
}

sub term {
    shift;
    my ($this_level, $offset, $id, $type, $bt_count, $bt_width) = @_;
    our $delta_levels = $this_level - $last_level;
    if ($delta_levels < 0) { 
        pop(@stack); 
    }
    my $path = get_path();
    printf("term path: $path, $this_level\n");
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
    }
    our $last_level = $this_level;
}

sub non_term {
    shift;
    my ($this_level, $offset, $id, $type, $rest) = @_;
    our $delta_levels = $this_level - $last_level;
    our @stack;
    my $struct_name = "";
    print("non-term $id\n");
    if ($id =~ /flags/i) {
        if ($type =~ /struct/) {
            $rest =~ /(\b\w+$)/;
            $struct_name = $1;
            print("...non term struct flags: $id : $type, $delta_levels, $rest\n");
            print("name: $struct_name\n");
        } else {
            print("...non term non struct flags: $id : $type, $delta_levels\n");
            return;
        }
    }
    if ($delta_levels < 0) {
        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
            pop(@stack); # backup delta_levels of structures
        }
    }
    if (length($struct_name) > 0) {
        push(@stack, $struct_name); # put the new struct on stack
        my $path = get_path();
        printf("pushed struct name: $path\n");
    } else {
        push(@stack, $id); # put the new struct on stack
    }        
    $last_level = $this_level;
}

sub non_term2 {
    my $this_level = shift;
    my $id = shift;
    #print("non-term2 $id\n");
    our $delta_levels = $this_level - $last_level;
    our @stack;
    if ($id =~ /flags/i) {
       print "non term flags: $id : $delta_levels\n";
       #pop(@stack); # backup delta_levels of structures
       #pop(@stack); # backup delta_levels of structures
    }
    if ($delta_levels < 0) {
        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
            pop(@stack); # backup delta_levels of structures
        }
    }
    push(@stack, $id); # put the new struct on stack
    $last_level = $this_level;
}

sub non_term3 {
    #print("non-term3\n");
    shift;
    my ($this_level, $id) = @_;
    our $delta_levels = $this_level - $last_level;
    our @stack;
    if ($id =~ /flags/i) {
       print "non term flags: $id : $delta_levels\n";
       #pop(@stack); # backup delta_levels of structures
       #pop(@stack); # backup delta_levels of structures
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

