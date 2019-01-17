#!/usr/bin/env perl

my @file = <stdin>;
my @stack;

$str_patt = "[a-zA-Z]+[a-zA-Z0-9_]*";

@primitives = (
    "F32", "f32",
    "U32", "u32", "S32", "s32",
    "U16", "u16", "S16", "s16",
    "U8",  "u8",  "S8",  "s8"
);
sub is_prim {
    $x = shift;
    print "is prim: $x\n";
    foreach my $p (@primitives) {
        if ($x eq $p) {
            return 1;
        }
    }
    return 0;
}

sub get_path {
    my $lvl = shift;
    my @tmp = @stack;
    my $i;
    my $path = "";
    for ($i = 0; $i < $lvl; $i++) {
        $val = pop @tmp;
        #print "pop: $val\n";
        $path = $path . "." . $val;
    }
#   print "path: $path\n";
#    return $path;
    return "";
}

my $i = 0;
for($i = 0; $i < scalar(@file); $i++) {
    my $line = @file[$i];
    if ($line =~ /0 \| ($str_patt)/) {
        print "$1 => $2\n";
        my $j = $i+1;
        my $sline;
        while ($sline = @file[$j++] and $sline !~ /sizeof/) {
             if ($sline =~ /(\d+).*?\|(\s+)($str_patt) ($str_patt)/) {
                $level = (length($2)-1)/2; # num spaces indented
                if (is_prim($3) == 1) {
                    $path = get_path($level);
                    print "leaf $level: $path $1 => $3 => $4\n";
                } else {
                    print "branch $level: $1 => $3 => $4\n";
                    push @stack, $3;
                }
            }
        }
        print $sline;
    }
}

