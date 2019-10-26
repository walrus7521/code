#!/usr/bin/env perl

# https://perldoc.perl.org/perlreftut.html
#
sub hard_reset {
    my @input = @_;
    print(scalar @input, "> @input\n");
    my @rocks = ();
    $rocks[0] = "soft";
    $rocks[1] = "sand";
    $rocks[2] = "hard";
    ($rocks[1], $rocks[2]) = ($rocks[2], $rocks[1]);
    print("hard reset ..: @rocks\n");
}

sub get_resetter {
    return &hard_reset;
}

sub main() {
    print("dude: "); <> or die "you suck";
    #$this_reset = hard_reset;
    #$this_reset;
    #&hard_reset("wusup");
    $the_resetter = &get_resetter;
    #&the_resetter("susup");

    print(<STDERR>, "you suck\n");
}

&main();

