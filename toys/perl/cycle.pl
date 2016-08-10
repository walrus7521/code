#!/usr/bin/perl

my $frame_count = 0;
my $toa = 0;
my $dir = 1;
while (1) {
    if ($frame_count % 100) {
        if ($dir > 0) {
            $toa += 0.1;
            if ($toa >= 7.0) {
                $dir = -$dir;
            }
        } else {
            $toa -= 0.1;
            if ($toa <= -7.0) {
                $dir = -$dir;
            }
        }
        printf("frame: %d dir %d -> toa %.2f\n", $frame_count, $dir, $toa);
    }
    $frame_count++;
}

