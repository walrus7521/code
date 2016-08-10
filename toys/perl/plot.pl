#!/usr/bin/perl

#8363, 1, 2000, 600.000, 1.000, 61
#8364, 0, 2000, 599.000, 1.000, 0
#8364, 1, 1969, 186.000, 195.000, 65
#8365, 0, 2000, 599.000, 1.000, 0
#8365, 1, 1969, 186.000, 419.000, 65
#<< F:14759  act[0], freq [2259], duty [774.0], expect_duty [346.0], count [64] >>

# Frame, Act, Freq, Duty, Expected_Duty, Count

#            8365, 1, 1969, 186.000, 419.000, 65
#my $pat = '(\d*), (\d*), (\d*), (\d*\.\d*), (\d*\.\d*), (\d*)';

#motor [1] count [128]
#[46852, 0]: [43168, 64]: [42852, 0]: [39168, 64]: [38852, 0]: [35168, 64]: [34852, 0]: [31168, 64]: [30852, 0]: [27168, 64]: [26852, 0]: [23168, 64]: [22852, 0]: [19168, 64]: [18852, 0]: [15168, 64]: [14852, 0]: [11168, 64]: [10852, 0]: [7168, 64]: [6852, 0]: [3168, 64]: [2852, 0]: [64704, 64]: [64388, 0]: [60704, 64]: [60388, 0]: [56704, 64]: [56388, 0]: [52704, 64]: [52388, 0]: [48704, 64]: [48388, 0]: [44704, 64]: [44388, 0]: [40704, 64]: [40388, 0]: [36704, 64]: [36388, 0]: [32704, 64]: [32388, 0]: [28704, 64]: [28388, 0]: [24704, 64]: [24388, 0]: [20704, 64]: [20388, 0]: [16704, 64]: [16388, 0]: [12704, 64]: [12388, 0]: [8704, 64]: [8388, 0]: [4704, 64]: [438[704, 64[61924, [57924, [50240, [46240, [41924, [37924, [30240, [26240, [22240, [17924, [13924, [6240, 6[2240, 6[63460, [59460, [51776, [47776, [43776, [39460, [35460, [27776, [23776, [19460, [15460, [7776, 6[3776, 6[64996, [60996, [53312, 

#[1]: motor [1] time [5074] pin [0]
my $pat = '\[(\d*), (\d*)\]';
my $frame = 0;
my $prev_time = 0;
my $delta_t = 0;
my $phase = 1;
my $on_time = 0;
my $total_time = 0;
my $period = 0;
while (<>) {
    if ($_ =~ /$pat/) {
        my ($time, $pin) = ($1, $2);
        if ((0 != $pin) == (0 != $phase)) {
            $delta_t = $prev_time - $time;
            if ($delta_t < 0) {
                $delta_t += 0xffff;
            }
            if ($pin != 0) {
                $total_time = $delta_t + $on_time;
                $period = $delta_t;
                printf("%4d: time %6d\tpin %5d\tdelta_t %5d\tphase %d\total_time %5d\ton_time %4d\n", $frame, $time, $pin, $delta_t, $phase, $total_time, $on_time);
            } else {
               $on_time = $delta_t;
            }
            #printf("%4d: time %6d\tpin %5d\tdelta_t %5d\tphase %d\n", $frame, $time, $pin, $delta_t, $phase);
            $prev_time = $time;
            $frame++;
            $phase ^= 1;
        } else {
            $phase = 1;
        }
    }
}
exit;


#[1]: motor [1] time [5074] pin [0]
my $pat = '\[(\d*)\]: motor \[(\d*)\] time \[(\d*)\] pin \[(\d*)\]';
while (<>) {
    if ($_ =~ /$pat/) {
        #print "$1, $2, $3, $4, $5, $6\n";
        my ($frame, $motor, $time, $pin) = ($1, $2, $3, $4);
        if ($motor == 1) {
            printf("[%5d]:\tmotor %6d\ttime %6d\tpin %5d\n", $frame, $motor, $time, $pin);
        }
    }
}
exit;

$SAMPLE_SIZE = 8;
sub cal_running_avg #(avg, new_sample)
{
    @parms = @_;
    $avg = $parms[0];
    $new_sample = $parms[1];
    #print "avg $avg, new sample $new_sample\n";
    if (abs($avg) > 0.0) {
        $avg -= $avg / $SAMPLE_SIZE;
    }
    $avg += $new_sample / $SAMPLE_SIZE;
    return $avg;
}

sub dump_duty
{
    $duty = @_;
    print "$duty\n";
}

# PRINTF_6("\n\n\r<< F:%d  act[%d], duty [%.1f], total_on [%d], total_period [%d], count [%d] >>\n\r", FRAME_NUM, act, duty, total_on, total_period, count);
#my $pat = '<< F\:(\d*)  act\[(\d*)\], duty \[(\d*\.\d*)\], total_on \[(\d*)\], total_period \[(\d*)\], count \[(\d*)\]';
while (<>) {
    $my_avg = 0;
    if ($_ =~ /$pat/) {
        #print "$1, $2, $3, $4, $5, $6\n";
        my ($frame, $act, $duty, $total_on, $total_period, $count) = ($1, $2, $3, $4, $5, $6);
        #print "$duty\t$pwm_mon_delta_t usec\t$expected_duty\t$scope_delta_t usec\n";
        $my_duty = ((1.0*$total_on)/(1.0*$total_period))*100.0;
        $my_avg = cal_running_avg($my_avg, $total_on);
        $total_on = $total_on / 64;
        $total_period = $total_period / 64;
        #printf("%6.1f\ttotal_on %d  -> avg %d\t%d total_period\t derived duty %f\n", $duty, $total_on, $my_avg, $total_period, $my_duty);
        printf("%6.1f\ttotal_on %6d\ttotal_period %5d\t derived duty %5.1f\n", $duty, $total_on, $total_period, $my_duty);
        #dump_duty($duty);
    }
}
exit;

#           << F:14759  act[0], freq [2259], duty [774.0], expect_duty [346.0], count [64] >>
#my $pat = '<< F\:(\d*)  act\[(\d*)\], freq \[(\d*)\], duty \[(\d*\.\d*)\], expect_duty \[(\d*\.\d*)\], count \[(\d*)\]';
while (<>) {
    if ($_ =~ /$pat/) {
        #print "$1, $2, $3, $4, $5, $6\n";
        my ($frame, $act, $freq, $duty, $expected_duty, $count) = ($1, $2, $3, $4, $5, $6);
        $pwm_mon_delta_t = ($duty/4000)*(0.000050)*(1000000);
        $pwm_mon_percent = ($duty/4000)*(100.0);
        $scope_delta_t   = ($expected_duty/4000)*(0.000050)*(1000000);
        $scope_percent   = ($expected_duty/4000)*(100.0);
        $delta_percent   = abs($pwm_mon_percent - $scope_percent);
        #print "$duty\t$pwm_mon_delta_t usec\t$expected_duty\t$scope_delta_t usec\n";
        printf("%6.1f\t%4.1f usec\t%4.1f \%\t%4.1f\t%2.1f usec\t%4.1f \% ==> delta \%:  %4.1f\n", 
            $duty, $pwm_mon_delta_t, $pwm_mon_percent, $expected_duty, $scope_delta_t, $scope_percent, $delta_percent);
        #dump_duty($duty);
    }
}
exit;

$EXPECTED_PWM_FREQ_HZ   = 2000;
$PWM_FREQ_ERR_TOL_HZ    = 40;
$PWM_MON_MIN_DUTY       = 1.0;
$PWM_MON_MAX_DUTY       = 4000.0;
$PWM_MAX_DUTY_DEVIATION = 80;
$MIN_COUNT              = 31;
$MAX_COUNT              = 65;
$MAX_ERROR_COUNT        = 2;

sub is_fatal_error {
    @errs = @_;
    my $res=1, $nerrs=0, $prev=0, $curr=0;
    foreach $curr (@errs){
        if ($prev) {
            if ($prev != $curr-1) {
                $res = 0;
                break;
            }
        }
        $prev = $curr;
    }
    $nerrs = scalar(@errs);
    if ($nerrs < $MAX_ERROR_COUNT) {
        $res = 0;
    }
    shift @errs;
    return $res;
}

my @freq_errs;
my @duty_errs;
my @expect_errs;
@freq_errs = ();
@duty_errs = ();
@expect_errs = ();
while (<>) {
    if ($_ =~ /$pat/) {
        #print "$1, $2, $3, $4, $5, $6\n";
        my ($frame, $act, $freq, $duty, $expected_duty, $count) = ($1, $2, $3, $4, $5, $6);
        if (($count > $MIN_COUNT) && ($count < $MAX_COUNT)) {
            #print "frame: $frame, act: $act, freq: $freq, duty $duty, expect: $expected_duty, count: $count\n";
            if (($freq < $EXPECTED_PWM_FREQ_HZ - $PWM_FREQ_ERR_TOL_HZ) ||
                ($freq > $EXPECTED_PWM_FREQ_HZ + $PWM_FREQ_ERR_TOL_HZ)) {
                push @freq_errs, $frame;
                if (is_fatal_error(@freq_errs)) {
                    print "frame: $frame frequency error $freq\n";
                }
            }
            if ($expected_duty > 1.0) {
                if (abs($expected_duty) > 1.0 && abs($duty - $expected_duty) > $PWM_MAX_DUTY_DEVIATION) {
                    push @duty_errs, $frame;
                    if (is_fatal_error(@duty_errs)) {
                        print "frame: $frame duty error duty=$duty, expected_duty=$expected_duty\n";
                    }
                }
            }
        }
        elsif ($expected_duty > 1.0) {
            if (($expected_duty < $PWM_MON_MIN_DUTY) || ($expected_duty > $PWM_MON_MAX_DUTY))
            {
                push @expect_errs, $frame;
                if (is_fatal_error(@expect_errs)) {
                    print "frame: $frame PWM duty MIN/MAX error $expected_duty\n";
                }
            }
        }
    }
}

