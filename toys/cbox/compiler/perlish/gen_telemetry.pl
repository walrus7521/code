#!/usr/bin/env perl

@finders = (
    "TELEMETRY_LOG_STRUCT",
);

@file = ();
$str_patt = "[a-zA-Z]+[a-zA-Z0-9_.]*";
$start = 0;
while ($line = <stdin>) {
    if ($line =~ /@finders[0]/) {
        while ($line = <stdin>) {
            if ($line =~ /(\d+), ($str_patt), (.*)/) {
                my $offset = $1;
                my $id = $2;
                my $type = $3;
                if ($1 == 0 and $start == 0) {
                    $start = 1;
                } elsif ($1 == 0 && $start != 0) {
                    $start = 0;
                }
                if ($start > 0) {
                    #print "parse type: $type\n";
                    if ($type =~ /($str_patt):(\d+)-(\d+)/) {
                        $bit_num   = int($2);
                        $bit_width = int($3);
                        #print "spew: $type : $bit_width\n";
                        if ($bit_width > 0) {
                            print("$id, BOOLEAN_Type :$bit_num\n");
                        }
                    } else {
                        $type =~ /($str_patt), /;
                        $type = $type. "_Type";
                        print("$id, $type\n");
                    }
                }
            }
        }
    }
}

