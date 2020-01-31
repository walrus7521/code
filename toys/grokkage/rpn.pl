#!/usr/bin/perl
#
#use Switch; # replaced with given/when
use 5.010;
no warnings 'experimental';

my @stack;
my @vars;
#

sub binop {
    my $op = shift;
    my $a = pop @stack;$b = pop @stack;
    given ($op) {
        when ($op eq '+')  {$c = $a + $b;}
        when ($op eq '-')  {$c = $a - $b;}
        when ($op eq '\/') {$c = $a / $b;}
        when ($op eq '*')  {$c = $a * $b;}
        when ($op eq '%')  {$c = $a % $b;}
    }
    push @stack, $c;print "$c\n";
}

sub unop {
    my $op = shift;
    my $a = pop @stack;
    given ($op) {
        when ($op eq '!') {$c = !$a;}
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
    given ($str) {
        print "dude: $str\n";
        when ($str eq "quit") {exit;}
        when ($str =~ /[+-\/*%]/) {binop($str);}
        when ($str =~ /(\d+)?/) {print "$str\n"; push @stack, $str;}
        when ($str =~ /[!]/) {$a = pop @stack;$c = !$a;push @stack, $c;print "unop: $c\n";}
        when ($str =~ /[.]/) {print pop @stack;print "\n";}
        when ($str =~ /(\s+)/) {print "string\n"; parse_str($str);} # push @vars, $str;}
   }
}

printf("rpn> ");
while (<>) {
    chomp;
    dispatch($_);
    printf("rpn> ");
}

