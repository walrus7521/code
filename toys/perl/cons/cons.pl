#!/usr/bin/perl

use Win32::Console;
my $CONSOLE = Win32::Console->new(STD_OUTPUT_HANDLE);
my $attr = $CONSOLE->Attr(); # Get current console colors
$CONSOLE->Attr($FG_YELLOW | $BG_GREEN); # Yellow text on green

print "This is a test\n";

$CONSOLE->Attr($attr); # Set console colors back to original
