#!/usr/bin/perl

use strict;
use warnings;

use SDL;
use SDLx::App;
use SDL::Video;
use SDL::Surface;
use SDL::Rect;
use SDL::Image;
    
# http://sdl.perl.org/SDL-Tutorial-LunarLander.html
#
#my $app = SDLx::App->new( w => 800, h => 600, t => 'Space Invaders - A clone' );

my $app = SDLx::App->new(
        title  => "Lunar Lander",
        width  => 800,
        height => 600,
        depth  => 32,
    );

$app->draw_rect([ $app->width / 4, $app->height / 4,
$app->width / 2, $app->height / 2, ],
        [ 0, 0, 255, 255] );

$app->update();

sleep(5);

