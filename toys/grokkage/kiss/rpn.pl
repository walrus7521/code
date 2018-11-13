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

sub parse_str {
    print "parse_str\n";
    my $str = shift;
    @fields = split ' ', $str;    
    #print "@fields\n";
    foreach $l (@fields) {
        print "$l\n";
        #dispatch($l);
    }
}

sub dispatch {
    my $str = shift;
    my $c;
    switch ($str) {
        case /quit/     {exit;}
        case /[+-\/*%]/ {binop($str);}
        case /(\d+)?/   {print "$str\n"; push @stack, $str;}
        case /[!]/      {$a = pop @stack;$c = !$a;push @stack, $c;print "unop: $c\n";}
        case /[.]/      {print pop @stack;print "\n";}
        case /(\s+)/    {print "string\n"; parse_str($str);} # push @vars, $str;}
    }
}

printf("rpn> ");
while (<>) {
    chomp;
    dispatch($_);
    printf("rpn> ");
}

