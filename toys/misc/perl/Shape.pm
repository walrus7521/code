#!/usr/bin/perl

# http://perltricks.com/article/25/2013/5/20/Old-School-Object-Oriented-Perl/
# Creating default attribute values

package Shape;

sub new {
    my ($class, $args) = @_;
    my $self = { # attributes
        color  => $args->{color},
        length => $args->{length},
        width  => $args->{width},
    };
    return bless $self, $class;
}

1;
