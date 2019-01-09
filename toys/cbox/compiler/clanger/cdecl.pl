#!/usr/bin/env perl

my %names = {};

while (<>) {
    my $line = $_;
    my $name;
    my $type;
    %$names = ();
    #if ($line =~ /'#'/) { 
    #    continue; 
    #}
    if ($line =~ /typedef (\w+)/) {
        $name = "";
        print "=> `$1`\n";
        if ($1 =~ /struct/) {
            print("struct: $line\n");
        } elsif ($1 =~ /enum/) {
            #print("enum:   $line\n");
        } elsif ($1 =~ /union/) {
            #print("union:  $line\n");
        } elsif ($1 =~ /unsigned/) {
            #print("unsigned:  $1  $line\n");
            if ($line =~ /char/) {
                $name = "U8";
            } elsif ($line =~ /short/) {
                $name = "U16";
            } elsif ($line =~ /long/) {
                $name = "U32";
            }
        } elsif ($1 =~ /signed/) {
            #print("signed:  $1  $line\n");
            if ($line =~ /char/) {
                $name = "S8";
            } elsif ($line =~ /short/) {
                $name = "S16";
            } elsif ($line =~ /long/) {
                $name = "S32";
            }
        } elsif ($1 =~ /float/) {
            print("float:  $line\n");
        }

        if (length($name) > 1) {
            $names{$name} = "dude"; #$type;
        }
        
    }

}

#while (($name, $type) = each (%names)) {
#    print "$name isa $type\n";
#}

