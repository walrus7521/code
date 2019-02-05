#!/usr/bin/env perl

$host = "127.0.0.1";
use Net::SSH::Perl;
my $ssh = Net::SSH::Perl->new($host);
$ssh->login($user, $pass);
my($stdout, $stderr, $exit) = $ssh->cmd($cmd);

