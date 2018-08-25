#define IS_MAC

// http://jhnet.co.uk/articles/cpp_magic
//#!/usr/bin/perl

#pragma message("#!/usr/bin/perl")

#ifdef IS_WIN
    use Win32::Console::ANSI;
#endif

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

