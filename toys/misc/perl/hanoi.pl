use warnings;
use strict;

# Towers of Hanoi
# Perl version (5.8.0)
# Ported from Java

my $numdisks = 0;

print "Number of disks? ";
chomp( $numdisks = <STDIN> );

print "The moves are:\n\n";
movedisks( $numdisks, 'A', 'B', 'C' );

sub movedisks {

  my( $num, $from, $to, $aux ) = @_;

  if( $num == 1 ) {
    print "Move disk $num from $from to $to\n";
  }

  else {
    movedisks( $num-1, $from, $aux, $to );
    print "Move disk $num from $from to $to\n";
    movedisks( $num-1, $aux, $to, $from );
  }
}

