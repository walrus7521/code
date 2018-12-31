#!/usr/bin/perl

# https://metacpan.org/pod/Win32::Console::ANSI

use constant IS_ANDROID => ($^O eq "Android"); 
use constant IS_MSWIN32 => ($^O eq "MSWin32"); 
use constant IS_MAC     => ($^O eq "darwin"); 

#define DUDE (1)

#ifdef DUDE
    print "dude\n";
#endif

my $os = $^O;
    print "Running in: $os\n";


if (IS_MAC)
{
    print "is a mac\n";
}
elsif (IS_MSWIN32)
{
    use Win32::Console::ANSI;
}

use Term::ANSIColor;
 
print color('bold blue');
print "This text is bold blue.\n";
print color('reset');
print "This text is normal.\n";
print colored("Yellow on magenta.", 'yellow on_magenta'), "\n";
print "This text is normal.\n";
print colored(['yellow on_magenta'], 'Yellow on magenta.', "\n");
print colored(['red on_bright_yellow'], 'Red on bright yellow.', "\n");
print colored(['bright_red on_black'], 'Bright red on black.', "\n");
print "\n";
