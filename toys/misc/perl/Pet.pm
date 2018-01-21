#!/usr/bin/perl

package Pet;

# http://perltricks.com/article/25/2013/5/20/Old-School-Object-Oriented-Perl/


# This is the constructor method
sub new {
    my $class = shift;
    my $pet = {
        "Name"  => undef,
        "Owner" => undef,
        "Type"  => undef,
    };
    bless($pet, $class);
# returns a pointer to the object

    sub set_pet { # accessor
        my $self = shift;
        my ($name, $owner, $type) = @_;
        $self->{'Name'}  = $name;
        $self->{'Owner'} = $owner;
        $self->{'Type'}  = $type;
        #print "name : $name\n";
        #print "owner: $owner\n";
        #print "type : $type\n";
    }

    sub get_pet {
        my $self = shift;
        while (($key,$value)=each(%$self)) {
            print "$key: $value\n";
        }
    }

}

1;

