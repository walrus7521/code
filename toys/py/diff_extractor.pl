#!/usr/bin/perl
use File::Basename;

my $IDX='Index:';
my $REV='revision';
my $PLUS=1;
my $MINUS=1;
my $ALL=1;

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
                if ($ALL == 1) {
                    print $fh "$_";
                } 
                else
                {
                    if ($PLUS == 1) {
                        if ($_ =~ /^\+/) {
                            print $fh "$_";
                        }
                    }
                    if ($MINUS == 1) {
                        if ($_ =~ /^\-/) {
                            print $fh "$_";
                        }
                    }
                }
            }
        }
    }
}

extract_file_patches;

