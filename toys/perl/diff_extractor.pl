#!/usr/bin/perl
use File::Basename;

my $IDX='Index:';
my $REV='revision';
my $STRIP=1;
my $PLUS=1;
my $MINUS=1;
my $ALL=0;
# note: to count $CLOC, set $ALL=1, $PLUS = $MINUS = 1;
my $CLOC = 0;

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
                } else {
                    if ($PLUS == 1) {
                        if ($_ =~ /^\+/) {
                            print $fh "$_";
                            $CLOC++;
                        }
                    }
                    if ($MINUS == 1) {
                        if ($_ =~ /^\-/) {
                            print $fh "$_";
                            $CLOC++;
                        }
                    }
                }
            }
        }
    }
}

extract_file_patches;
print "loc: $CLOC\n";
