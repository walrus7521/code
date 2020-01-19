#!/usr/bin/perl

use Digest::SHA qw(sha256_hex);
use File::Slurp;

my $text = read_file('telemetry.xml');

$sha = sha256_hex($text);
print "SHA256(telemetry.xml)= $sha\n";

