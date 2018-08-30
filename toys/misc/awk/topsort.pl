#!/usr/bin/perl
%predct;
while ($line = <>) {
    chomp $line;
    ($p, $s) = split / /, $line;
    $predct[$s]++;
    print "$line: $p => $s\n";
}

for $e (keys %predct) {
    print "$e\n";
}
