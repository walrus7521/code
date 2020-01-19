#!/usr/bin/perl -w

use strict;

#my $Expression="1+3*(((4*7)-29))/3+(90/5)";
my $Expression="(1/2)*16";
my $ParenExpression;
my $ParenContents;
my $MatcherMul = "((-?\\d+|-?\\d+\\.\\d+)\\*(-?\\d+|-?\\d+\\.\\d+))";
my $MatcherDiv = "((-?\\d+|-?\\d+\\.\\d+)\\/(-?\\d+|-?\\d+\\.\\d+))";
my $MatcherAdd = "((-?\\d+|-?\\d+\\.\\d+)\\+(-?\\d+|-?\\d+\\.\\d+))";
my $MatcherSub = "((-?\\d+|-?\\d+\\.\\d+)\\-(-?\\d+|-?\\d+\\.\\d+))";
sub evaluate {
    my $Expr = join("", @_);
    my $A;
    my $B;
    my $C;
    my $X;

    while ($Expr =~ /$MatcherMul/) {
        $A = $2;
        $B = $3;
        $C = $A * $B;
        $Expr =~ s/$MatcherMul/$C/;
    }
    while ($Expr =~ /$MatcherDiv/) {
        $A = $2;
        $B = $3;
        $X = $1;
        $C = $A / $B;
        $Expr =~ s/$MatcherDiv/$C/;
    }
    while ($Expr =~ /$MatcherAdd/) {
        $A = $2;
        $B = $3;
        $C = $A + $B;
        $Expr =~ s/$MatcherAdd/$C/;
    }
    while ($Expr =~ /$MatcherSub/) {
        $A = $2;
        $B = $3;
        $X = $1;
        $C = $A - $B;
        $Expr =~ s/$MatcherSub/$C/;
    }
    return $Expr;
}

while ($Expression =~ /(\((.*?)\))/) {
    $ParenContents = $2;
    $ParenContents = evaluate($ParenContents);
    $Expression =~ s/(\((.*?)\))/$ParenContents/;
}

$Expression = evaluate($Expression);
print "$Expression\n";

