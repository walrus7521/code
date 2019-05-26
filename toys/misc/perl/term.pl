#!/usr/bin/env perl

use Term::ANSIColor;
use Term::ANSIScreen qw(cls);

my $clear_screen = cls();

print $clear_screen;

print color("red"), "Stop!\n", color("reset");
print color("green"), "Go!\n", color("reset");

