#!/usr/bin/perl

use Parse::RecDescent;

my $grammar = q(
        sentence: subject verb object
        subject: noun_phrase
        object: noun_phrase
        verb: 'wrote' | 'likes' | 'ate'
        noun_phrase: pronoun | proper_noun
        article: 'a' | 'the' | 'this'
        pronoun: 'it' | 'he'
        proper_noun: 'Perl' | 'Dave' | 'Larry'
        noun: 'book' | 'cat'
        );
        
$Parse::RecDescent::skip = '[ \t]+';
my $parser = Parse::RecDescent->new($grammar);

#while (<>) {
while (<DATA>) {
    chomp;
    print "'$_' is ";
    print 'NOT ' unless $parser->sentence($_);
    print "a valid sentence\n"
}

__END__
Larry wrote Perl
Larry wrote a book
Dave likes Perl
Dave to very angry

