#!/usr/bin/perl

# https://www.tutorialspoint.com/perl/perl_database_access.htm

use strict;
use warnings;
use DBI;

my $driver = "mysql"; 
my $database = "TESTDB";
my $dsn = "DBI:$driver:database=$database";
my $userid = "testuser";
my $password = "test123";

my $dbh = DBI->connect($dsn, $userid, $password ) or die $DBI::errstr;

