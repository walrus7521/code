#!/usr/bin/env perl

use YAML::Tiny;
 
# Create a new object with a single hashref document
my $yaml = YAML::Tiny->new( { wibble => "wobble" } );
 
# Add an arrayref document
push @$yaml, [ 'foo', 'bar', 'baz' ];
 
# Save both documents to a file
$yaml->write( 'data.yml' );

