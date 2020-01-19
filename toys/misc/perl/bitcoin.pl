#!/usr/bin/perl

#my $url = 'https://coinmarketcap.com/historical/20130505';
my $url = 'https://coinmarketcap.com';

use LWP::Simple;
my $content = get $url;
die "Couldn't get $url" unless defined $content;

print "bitcoin: $content\n";

