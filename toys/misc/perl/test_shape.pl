#!/usr/bin/perl

use strict;
use warnings;
use feature qw/say/;
use Shape;

# create a new Shape object
my $shape = Shape->new({
            color => 'red',
            length=> 2,
            width => 2,
        });

#print the shape object attribs
say $shape->{color};
say $shape->{length};
say $shape->{width};

