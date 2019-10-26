#!/usr/bin/perl

my $select_1, $select_2, $select_3;
my $input_1, $input_2, $input_3;
my $default_value;
my $final_value;

$select_1 = 0;
$select_2 = 0;
$select_3 = 0;

$input_1  = 1;
$input_2  = 2;
$input_3  = 3;

$default_value = 42;

$final_value = $select_1 ? $input_1 :
               $select_2 ? $input_2 :
               $select_3 ? $input_3 :
                           $default_value;

print "final: $final_value\n";

