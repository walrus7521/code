#!/usr/bin/perl
use Switch;

my @stack;
my @vars;
#
# push @stack, "An item to push on the stack";
# print "The top stack item is: $stack[-1]\n";
# pop @stack;
#
printf("rpn> ");
while (<>) {
    printf("$_");
    if ($_ =~ /quit/) {
        exit;
    }
        $a = pop @stack;
        $b = pop @stack;
        my $c;
        switch ($_) {
            case /[+]/  {$c = $a + $b;}
            case /[-]/  {$c = $a - $b;}
            case /[\/]/ {$c = $a / $b;}
            case /[*]/  {$c = $a * $b;}
            case /[%]/   {$c = $a % $b;}
            case /(\d+)/  {print "number"; push @stack, $_;}
            case /[.]/  {print pop @stack;}
            case /[%]/  {$c = $a % $b;}
            case /[%]/  {$c = $a % $b;}
        }
        push @stack, $c;
        print "binop: $c\n";
    } elsif ($_ =~ /[=!]/) {
        $a = pop @stack;
        my $c = !$a;
        print "unop: $c\n";
    } elsif ($_ =~ /(\s+)/) {
        print "string\n";
        push @vars, $_;
    }
    printf("rpn> ");
}

#     } elsif ($_ =~ /[-+*/=!%]/) {

