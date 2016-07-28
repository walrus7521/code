#!/usr/bin/perl
use File::Basename;

my $IDX='Index:';

sub extract_file_patches
{
    my $path;
    my $fh;
    while (<>) {
        if ($_ =~ /$IDX(.*)/)  { 
            $path = $1; 
new_module:
            $file = basename($path);
            print "$file\n";
            open($fh, ">", "$file") or die "Can't open < $file: $!";
            while (<>) {
                if ($_ =~ /$IDX(.*)/)  { 
                    $path = $1;
                    goto new_module;
                    close($fh);
                }
                print $fh "$_";
            }
        }
    }
}

extract_file_patches;

