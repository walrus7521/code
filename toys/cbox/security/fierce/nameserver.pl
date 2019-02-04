#!/usr/bin/perl
 
use strict;
use warnings;
use Net::DNS::Nameserver;
 
sub reply_handler {
    my ( $qname, $qclass, $qtype, $peerhost, $query, $conn ) = @_;
    my ( $rcode, @ans, @auth, @add );
 
    print "Received query from $peerhost to " . $conn->{sockhost} . "\n";
    $query->print;
 
    #if ( $qtype eq "A" && $qname eq "foo.example.com" ) {
    if ( $qtype eq "A" && $qname eq "127.0.0.1" ) {
            my ( $ttl, $rdata ) = ( 3600, "10.1.2.3" );
            my $rr = new Net::DNS::RR("$qname $ttl $qclass $qtype $rdata");
            push @ans, $rr;
            $rcode = "NOERROR";
    } elsif ( $qname eq "foo.example.com" ) {
            $rcode = "NOERROR";
 
    } else {
            $rcode = "NXDOMAIN";
    }
 
    # mark the answer as authoritative (by setting the 'aa' flag)
    my $headermask = {aa => 1};
 
    # specify EDNS options  { option => value }
    my $optionmask = {};
 
    return ( $rcode, \@ans, \@auth, \@add, $headermask, $optionmask );
}
 
 
my $ns = new Net::DNS::Nameserver(
    LocalPort    => 5353,
    ReplyHandler => \&reply_handler,
    Verbose      => 1
    ) || die "couldn't create nameserver object\n";
 
 
$ns->main_loop;

