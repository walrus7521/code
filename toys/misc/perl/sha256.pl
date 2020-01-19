#!/usr/bin/env perl

# https://passwordsgenerator.net/sha256-hash-generator/

use Digest::SHA qw(sha256);
print unpack("H*", sha256('dude, wusup')), "\n";

