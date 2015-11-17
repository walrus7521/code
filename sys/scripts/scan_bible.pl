#!/usr/bin/perl
#my $url = 'https://www.biblegateway.com/passage/?search=Genesis+1&version=NASB';
my $url = 'http://www.studylight.org/bible/nas/genesis/1.html';
#my $url = 'http://www.biblestudytools.com/nas/leviticus/1.html';
use LWP::Simple;
my $content = get $url;
print $content;
