#!/usr/bin/perl -w

use strict;
use warnings;

use Parse::RecDescent;

my $grammar = q {
                                         {my %vars}

start:          statements               {print "$item[1]\n"}

statements:     statement ';' statements
              | statement

statement:      <rightop: variable '=' expression>
                         {my $value = pop @{$item [1]};
                          while (@{$item [1]}) {
                              $vars {shift @{$item [1]}} = $value;
                          }
                          $value
                         }

expression:     <leftop: term ('+' | '-') term>
                         {my $s = shift @{$item [1]};
                          while (@{$item [1]}) {
                              my ($op, $t) = splice @{$item [1]}, 0, 2;
                              if ($op eq '+') {$s += $t}
                              else            {$s -= $t}
                          }
                          $s
                         }

term:           <leftop: factor m{([*/])} factor>
                         {my $t = shift @{$item [1]};
                          while (@{$item [1]}) {
                              my ($op, $f) = splice @{$item [1]}, 0, 2;
                              if ($op eq '/') {$t /= $f}
                              else            {$t *= $f}
                          }
                          $t
                         }


factor:         number
              | variable                 {$vars {$item [1]} ||= 0 }
              | '+' factor               {$item [2]}
              | '-' factor               {$item [2] * -1}
              | '(' statement ')'        {$item [2]}

number:         /\d+/                    {$item [1]}

variable:       /[a-z]+/i


};

my $parser=Parse::RecDescent->new($grammar);

my $result = $parser->start("three=3;six=2*three;eight=three+5;2+eight*six+50+42");
