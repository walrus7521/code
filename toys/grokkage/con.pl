# 1 "console.pp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 328 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "console.pp" 2


//#!/usr/bin/perl


# 5 "console.pp"
#pragma message("#!/usr/bin/perl")





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


