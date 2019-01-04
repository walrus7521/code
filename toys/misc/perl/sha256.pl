#!/usr/bin/env perl

use Digest::SHA qw(sha256);
print unpack("H*", sha256('dude, wusup')), "\n";

