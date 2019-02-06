#!/usr/bin/env perl

# http://blogs.perl.org/users/brian_medley/2016/06/rest-api-with-mojolicious.html

use Mojolicious::Lite;

use Mojo::Util qw(secure_compare);

# App instructions
get '/' => qw(index);

# Authentication
under(sub {
    my $c = shift;

    # Have access
    return 1 if secure_compare(
        $c->req->url->to_abs->userinfo,
        'user:523487063f1011e68442002500f18b6d'
    );

    # Do not have access
    $c->render(json => 
        {status => "error", data => { message => "Credentials mis-match" }}
    );
    return undef;
});

# Anything works, a long as it's GET and POST
any ['GET', 'POST'] => '/v1/time' => sub {
    shift->render(json => { now => scalar(localtime) });
};

# Just a GET request
get '/v1/epoch' => sub {
    shift->render(json => { now => time });
};

# Required
app->start;

__DATA__

@@ index.html.ep

<pre>
Try: 

    $ curl -v -X GET --user 'user:523487063f1011e68442002500f18b6d' \
         http://127.0.0.1:3000/v1/time
    $ curl -v -X POST --user 'user:523487063f1011e68442002500f18b6d' \
         http://127.0.0.1:3000/v1/time
    $ curl -v -X GET --user 'user:523487063f1011e68442002500f18b6d' \
         http://127.0.0.1:3000/v1/epoch
    $ curl -v -X POST --user 'user:523487063f1011e68442002500f18b6d' \
         http://127.0.0.1:3000/v1/epoch

    All except the last should work.
</pre>

