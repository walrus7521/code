#!/usr/bin/perl

use C::Utility;

sub make_date_time {
    return localtime;
}

my $git_sha = `git rev-parse HEAD`;
$git_sha =~ s/\s+//g;
# This contains all the build variables.
my %build;
$build{date} = make_date_time ();
$build{git_sha} = $git_sha;

C::Utility::hash_to_c_file ("version.c", \%build, "build_");
#C::Utility::hash_to_c_file ('version.c', 'build_');
