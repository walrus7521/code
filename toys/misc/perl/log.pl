#!/usr/bin/perl

@cases = ();
$caseid = "";
$status = "";
$action = "";
$customer = "";
$deliverable = "";
$itemid = 1;
$now = localtime time;
print "$now\n\n";
print "\n";

while (<>) {
    chomp;
    if ($_ =~ /::caseid:: (\S{3})(\d+)/) {
        $caseid = "$1$2";
        #print "case:   $caseid\n";
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
    if ($caseid && $status && $action && $deliverable) {
        #my $item = $Outlook->CreateItem(0);  # 0 = mail item.
        #print "$itemid> caseid: $caseid\n";
        #print "status: $status \n";
        #print "action: $action\n";
        #print "\n";
        $msg = "<UPDATE>\nstatus: $status\nnext action: $action\n\n</UPDATE>\n";
        $item->{'Subject'} = $caseid;
        $item->{'To'} = "bbartel; compmail";
        $item->{'Body'} = $msg;
        push @cases, $item;
        #print "Subject:  $item->{'Subject'}\n";
        #print "To:       $item->{'To'}\n";
        #print "Body:     $item->{'Body'}\n";
        #$item->Send();
        #print "$caseid\n$msg";
        $caseid         = "";
        $status         = "";
        $action         = "";
        $customer       = "";
        $deliverable    = "";
        $itemid++;
    }
}

foreach (@cases) {
    print "$_->{'Subject'}\n";
    print "$_->{'Body'}\n";
}

