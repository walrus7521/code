#!/usr/bin/perl

use List::Util qw(sum);

$stage = 0; # current stage
$phase = 0; # current stage
$ptime = 0;
$stime = 0;
@ptimer = ();
@stimer = ();
$stimer_count = 0;

while (<STDIN>) {
    chomp;
    if ($_ =~ m/S(\d+) (\d+): (.*)/i) {
        $stage  = $1;
        $phase  = $2;
        $ptime  = $3;
        $ptimer[$stage][$phase] += $ptime
    } elsif ($_ =~ m/Stage (\d+): (.*)/i) {
        $stage  = $1;
        $stime  = $2;
        $stimer[$stage] += $stime;
        if ($stage == 0) {
            $stimer_count++;
        }
    }

}

sub average{
        my($data) = @_;
        if (not @$data) {
                die("Empty arrayn");
        }
        my $total = 0;
        foreach (@$data) {
                $total += $_;
        }
        my $average = $total / @$data;
        return $average;
}

sub stdev{
        my($data) = @_;
        if(@$data == 1){
                return 0;
        }
        my $average = &average($data);
        my $sqtotal = 0;
        foreach(@$data) {
                $sqtotal += ($average-$_) ** 2;
        }
        my $std = ($sqtotal / (@$data-1)) ** 0.5;
        return $std;
}

#print "@$_\n" for @ptimer;
#for $pt (@ptimer) {
#    print "@$pt\n";
#}
#exit;

#foreach $st (@stimer) {
#    my $s  = sprintf("%06f", $st);
#    my $av = sprintf("%06f", ($st / $stimer_count));
#    print "$s => avg: $av\n";
#}
#exit;

$idx = 0;
$stotal = 0;
print "stage times: $sdiv\n";
foreach $st (@stimer) {
    my $a = sprintf("%06f", $st / $stimer_count);
    $stotal += $a;
    print "stage[$idx]: $a\n";
    $idx++;
}

#my $elements = scalar @stimer;
#print "els: $elements\n";
#exit;

print "frame time:==> $stotal\n\n";
#$std = &std_dev_ref_sum(@stimer);
#$avg = &average(@stimer);
#$avg = sum(@stimer)/@stimer;
#$std = &stdev(@stimer);
#print "avg: $avg, std: $std\n";

sub std_dev_ref_sum {
  my $ar = shift;
  my $elements = scalar @$ar;
  print "elems: $elements\n";

  my $sum = 0;
  my $sumsq = 0;
  foreach (@$ar) {
    $sum += $_;
    $sumsq += ($_ **2);
  }
  return $sum;
  #return sqrt( $sumsq/$elements -
  #             (($sum/$elements) ** 2));
}
    my $elements = scalar @$_;

print "phase times\n";
foreach $pt (@ptimer) {
    $avg = sprintf("%0.6f", &average($pt));
    $std = sprintf("%0.6f", &stdev($pt));
    print "avg: $avg, std: $std\n";
    #foreach $st (@$pt) {    
    #    my $a = sprintf("%06f", $st / $stimer_count);
    #    print "$a, ";
    #}
    #print "\n";
}

exit;


