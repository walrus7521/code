#!/usr/bin/perl

# Very important.
use strict;
use warnings;

# Define some functions.
sub multiply { $_[0] * $_[1] }
sub divide   { $_[0] / $_[1] }
sub add      { $_[0] + $_[1] }
sub subtract { $_[0] - $_[1] }

# Create a hash of references to those functions (dispatch table).
my %funcs = (
    mul => \&multiply,
    div => \&divide,
    add => \&add,
    sub => \&subtract,
);

# Register some more functions.
sub register {
    my ($key, $func) = @_;
    $funcs{$key} = $func;
}

register('+', \&add);    # As above.
register('sum', sub {    # Or using an anonymous subroutine.
    my $s = 0;
    $s += $_ for @_;
    return $s;
});

# Invoke them dynamically.
# ussage: add 2 4
#         mul 4 5
while (<>){
    my ($op, @args) = split;
    print "$op\n";
    last unless $op and exists $funcs{$op}; # No need for equality tests.
    print $funcs{$op}->(@args), "\n";
}


