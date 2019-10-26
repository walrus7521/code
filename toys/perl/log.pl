#!/usr/bin/perl

@cases = ();
$caseid = "";
$status = "";
$action = "";
$customer = "";
$deliverable = "";
$repo = "";
$itemid = 1;
$now = localtime time;
print "$now\n\n";

while (<>) {
    chomp;
    if ($_ =~ /::caseid:: (\S{3})(\d+)/) {
        $caseid = "$1$2";
        #print "case: $caseid\n";
    }
    if ($_ =~ /::status:: /) { #if ($_ =~ /::status:: (\S*)/) {
        $status = $'; #$1;
        #print "status: $status \n";
    }
    if ($_ =~ /::action:: /) {
        $action = $'; #$1;
        #print "action: $action\n";
    }
    if ($_ =~ /::deliverable:: /) {
        $deliverable = $'; #$1;
        #print "deliverable: $deliverable\n";
    }
    if ($_ =~ /::repo:: /) {
        $repo = $'; #$1;
        #print "repo: $repo\n";
    }
    if ($caseid && $status && $action && $deliverable && $repo) {
        #my $item = $Outlook->CreateItem(0);  # 0 = mail item.
        my $item = {}; # need this for unique instance
        #my %item = (); # need this for unique instance
        #print "$itemid> caseid: $caseid\n";
        #print "status: $status \n";
        #print "action: $action\n";
        #print "\n";
        $item->{Subject} = $caseid;
        $item->{Deliverable} = $deliverable;
        $item->{Repository} = $repo;
        push @cases, $item;
        #$item->{'To'} = "bbartel; compmail";
        #$msg = "<UPDATE>\nstatus: $status\nnext action: $action\n\n</UPDATE>\n";
        #$item->{'Body'} = $msg;
        print "Subject:     $item->{Subject}\n";
        print "Deliverable: $item->{Deliverable}\n";
        print "Repository:  $item->{Repository}\n";
        print "\n";
        #print "To:       $item->{'To'}\n";
        #print "Body:     $item->{'Body'}\n";
        #$item->Send();
        #print "$caseid\n$msg";
        $caseid         = "";
        $status         = "";
        $action         = "";
        $customer       = "";
        $deliverable    = "";
        $repo           = "";
        $itemid++;
    }
}

printf("\n");
my $id = 0;
foreach (@cases) {
    #printf("> (%s) \n => (%s) \n => (%s) \n", $_->{'Subject'}, $_->{'Repository'}, $_->{'Deliverable'});
    printf("> %s\n", $_->{Subject});
    printf("> %s\n", $_->{Repository});
    printf("> %s\n", $_->{Deliverable});
    $id++;
}

