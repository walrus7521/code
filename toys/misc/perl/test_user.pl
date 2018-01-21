#!/usr/bin/perl

use User;

my $user = User->new(
    first_name => 'Example',
    last_name  => 'User',
    password   => 'letmein',
);

$user->login('letmein');

$date = $user->date_of_last_login;
print "date of last login: $date\n";


