#!/usr/bin/env perl

# Mojolicious Web app framework in perl
# https://mojolicious.org/perldoc/Mojolicious/Guides/Tutorial
# install: cpan Mojolicious
# run by: morbo mojo.pl


use Mojolicious::Lite;
get '/'     => { text => 'Hello World' };
 
get '/echo' => { text => q{
   <form method="POST"><input name="q"><input type="submit" value="Echo"></form>
}};

post '/echo' => sub {
    my $self = shift;
    $self->render( text => $self->param('q') );
};

app->secrets(['jellyfish']);
app->start;

