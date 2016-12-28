#!/usr/bin/perl

$start_time = 10.05;
$stop_time  = 19.01;
$collect = 0;

#while (<STDIN>) {
#    chomp;
#    if (($_ =~ m/Expected/i) || ($_ =~ m/Actual/i)) {
#        #print "yo: $_\n";
#    } else {
#        print "$_\n";
#    }
#
#}

# pattern: psi_dot_target 0.000174533 => 9.13852e-006
$time = 0;
while (<STDIN>) {
    chomp;
    if ($_ =~ m/Time=(\d+\.*\d{0,2})/i) {
        $time = $1;
        if (($time > $start_time) && ($time < $stop_time)) {
            $collect = 1;
        } else {
            $collect = 0;
        }
        #print "time: $time\n";
    }
    #elsif (($_ =~ m/psi_dot_target (.*) => (.*)/i)) {
    elsif (($_ =~ m/psi_target (.*) => (.*)/i)) {
        if ($collect == 1) {
            print "$time, $1, $2\n";
        }
    }

}

