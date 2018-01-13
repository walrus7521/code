#!/usr/bin/perl

use Curses::UI;

use strict;

my $cui = new Curses::UI( -color_support => 1 );

my @menu = (
    { -label => 'File', 
      -submenu => [
        { -label => 'Save      ^S', -value => \&file_save_dialog  },
        { -label => 'Exit      ^Q', -value => \&file_exit_dialog  }
                  ]
    },
    { -label => 'View', 
      -submenu => [
        { -label => 'Full      ^F', -value => \&view_full_dialog  }
                  ]
    },
    { -label => 'Utils', 
      -submenu => [
        { -label => 'Check     ^C', -value => \&utils_check_dialog  }
                  ]
    },
    { -label => 'Help', 
      -submenu => [
        { -label => 'About     ^A', -value => \&help_about_dialog  }
                  ]
    }
);

sub view_full_dialog()
{
    my $return = $cui->dialog(
        -message   => "This is the full meal deal",
        -title     => "View Full",
    );
}

sub utils_check_dialog()
{
    my $return = $cui->dialog(
        -message   => "This is the checker",
        -title     => "Check Dialog",
    );
}

sub help_about_dialog()
{
    my $return = $cui->dialog(
        -message   => "This is the awesome app packed with features.",
        -title     => "About",
    );
}

sub file_save_dialog()
{
    my $return = $cui->dialog(
        -message   => "enter file name to save",
        -title     => "dude???", 
    );
}

sub file_exit_dialog()
{
    my $return = $cui->dialog(
        -message   => "Do you really want to quit?",
        -title     => "Are you sure???", 
        -buttons   => ['yes', 'no'],
    );
    exit(0) if $return;
}

my $menu = $cui->add( 'menu','Menubar', 
    -menu => \@menu,
     -fg  => "blue",
   );

my $win1 = $cui->add( 'win1', 'Window',
    -border => 1,
    -y      => 1,
    -bfg    => 'red',
   );


my $texteditor = $win1->add("text", "TextEditor",
    -text => "Here is some text\n"
              . "And some more");

$cui->set_binding(sub {$menu->focus()},  "\cX");
$cui->set_binding( \&file_exit_dialog ,  "\cQ");
$cui->set_binding( \&file_save_dialog ,  "\cS");
$cui->set_binding( \&view_full_dialog ,  "\cF");
$cui->set_binding( \&utils_check_dialog, "\cC");
$cui->set_binding( \&help_about_dialog , "\cA");

$texteditor->focus();
$cui->mainloop();        


