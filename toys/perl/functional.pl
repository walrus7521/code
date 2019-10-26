#!/usr/bin/perl


# first class functions
my $print_something = sub { print "Something\n" };
sub do_something {
    my ($function) = @_;
    $function->();
}
do_something($print_something);

# list
@list = (1,2,3);
foreach $l (@list) {
    print "$l\n";
}

# hash
%hash1 = ( foo => 42, bar => 43, baz => 44 );
%hash2 = ( 'foo', 42, 'bar', 43, 'baz', 44 );
print "$hash2{foo}\n";

my %HoA = {};
#while ( <> ) {
#    next unless s/^(.*?):\s*//;
#    $HoA{$1} = [ split ];
#}
while ( $line = <> ) {
    ($who, $rest) = split /:/, $line; #, 2;
    @fields = split ' ', $rest;
    $HoA{$who} = [ @fields ];
}

for $family ( keys %HoA ) {
    print "$family: @{ $HoA{$family} }\n";
}

exit;


