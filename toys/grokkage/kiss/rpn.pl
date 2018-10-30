#!/usr/bin/perl
#
use Switch;

my @stack;
my @vars;
#

sub binop {
    my $op = shift;
    my $a = pop @stack;$b = pop @stack;
    switch ($op) {
        case /[+]/  {$c = $a + $b;}
        case /[-]/  {$c = $a - $b;}
        case /[\/]/ {$c = $a / $b;}
        case /[*]/  {$c = $a * $b;}
        case /[%]/  {$c = $a % $b;}
    }
    push @stack, $c;print "$c\n";
}

sub unop {
    my $op = shift;
    my $a = pop @stack;
    switch ($op) {
        case /[!]/ {$c = !$a;}
    }
    push @stack, $c;print "$c\n";    
}

printf("rpn> ");
while (<>) {
    my $c;
    switch ($_) {
        case /quit/ { exit; }
        case /[.]/   {print pop @stack;}
        case /[+-\/*%]/ {binop($_);}
        case /(\d+)/ {print "$_"; push @stack, $_;}
        case /[!]/   {$a = pop @stack;my $c = !$a;push @stack, $c;print "unop: $c\n";}
        case /(\s+)/ {print "string\n"; push @vars, $_;}
    }
    printf("rpn> ");
}

