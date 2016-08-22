#!/usr/bin/perl

$Regex_Pattern = '[1-9a-zA-Z^\S\n]{3}\.[1-9a-zA-Z^\S\n]{3}\.[1-9a-zA-Z^\S\n]{3}\.[1-9a-zA-Z^\S\n]{3}';

$Test_String = <STDIN> ;
 
if ($Test_String =~ /$Regex_Pattern/g) {
    print 'true';
} else {
    print 'false';
}
print "\n";

