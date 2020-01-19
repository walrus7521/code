#!/usr/bin/perl

# http://perltricks.com/article/25/2013/5/20/Old-School-Object-Oriented-Perl/
# Creating default attribute values

package Shape;

sub new {
    my ($class, $args) = @_;
    my $self = { # attributes
        color  => $args->{color}  || 'black',
        length => $args->{length} || 1,
        width  => $args->{width}  || 1,
    };
    return bless $self, $class;
}

1;
