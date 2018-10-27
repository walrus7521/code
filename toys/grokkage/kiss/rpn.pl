#!/usr/bin/perl
use Switch;

my @stack;
my @vars;
#
# push @stack, "An item to push on the stack";
# print "The top stack item is: $stack[-1]\n";
# pop @stack;
#

sub binop {
    $op = shift;
    $a = pop @stack;$b = pop @stack;
    switch ($op) {
        case /[+]/  {$c = $a + $b;}
        case /[-]/  {$c = $a - $b;}
        case /[\/]/ {$c = $a / $b;}
        case /[*]/  {$c = $a * $b;}
        case /[%]/  {$c = $a % $b;}
    }
    push @stack, $c;print "$c\n";
}

printf("rpn> ");
while (<>) {
    printf("$_");
    if ($_ =~ /quit/) {
        exit;
    }
    my $c;
    switch ($_) {
        case /[+-\/*%]/   {binop($_);}
        case /(\d+)/ {push @stack, $_;}
        case /[.]/   {print pop @stack;}
        case /[!]/   {$a = pop @stack;my $c = !$a;push @stack, $c;print "unop: $c\n";}
        case /(\s+)/ {print "string\n"; push @vars, $_;}
    }
    printf("rpn> ");
}

