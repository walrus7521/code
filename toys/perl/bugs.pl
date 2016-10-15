#!/usr/bin/perl

%all_bugs = {};
@bugs = [];
while (<>) {
    if ( my($id, $rest) = $_ =~ /\[Bug ([0-9]*)\](.*)/) {
        $nid = $id + 0;
        #print "$id, $rest\n";
        if (!exists($all_bugs{$nid})) {
            #print "adding $nid\n";
            $all_bugs{$nid} = $rest;
            $bugs[$nid] = $rest
        }
    }
}

$id=0;
foreach (@bugs)
{
    if ($_ ne '') {
        $shortened = substr( $_, 0, 50 );
        print "[Bug $id]: $shortened\n";
    }
    $id++;
}
#foreach my $id (@bugs) {
#    if ($id ne '') {
#        print "$id\n";
#    }
#}
#foreach my $id (sort keys %all_bugs) {
#    print "$id\n";
#}

