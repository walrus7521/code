#!/usr/bin/perl

while (<>) {
    chomp;
    if ($_ =~ /#/) {
        print("$_\n");
    } else {
        my ($ckno, $date, $desc, $debit, $credit, $balance) = split(/,/, $_);
        print "$ckno\t$date\t$desc\t$debit\t$credit\t$balance\n";
    }
}
