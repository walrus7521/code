#!/usr/bin/env perl

my @file = <stdin>;
my @stack = ();

$str_patt = "[a-zA-Z]+[a-zA-Z0-9_]*";

@primitives = (
    "F32", "f32",
    "U32", "u32", "S32", "s32",
    "U16", "u16", "S16", "s16",
    "U8",  "u8",  "S8",  "s8",
    "BOOLEAN"
);

sub is_leaf {
    $x = shift;
    foreach my $p (@primitives) { if ($x eq $p) { return 1; } }
    return 0;
}

sub get_path {
    my $lvl = shift;
    my @tmp1 = @stack;
    my @tmp2;
    my $path = "";
    if (@stack == 0) { return ""; }
    while (@tmp1) {
        my $tmp = pop(@tmp1);
        push(@tmp2, $tmp);
    }
    while (@tmp2) {
        $val = pop @tmp2;
        $path = $path . $val . ".";
    }
    return $path;
}

my $last_level = 0;
my $this_level = 0;
my $delta_levels = 0;
for(my $i = 0; $i < scalar(@file); $i++) {
    my $line = @file[$i];
    if ($line =~ /0 \| ($str_patt)/) {
        @stack = ();
        print "$1\n";
        my $j = $i+1;
        my $sline;
        while ($sline = @file[$j++] and $sline !~ /sizeof/) {
            if ($sline =~ /(\d+).*?\|(\s+)($str_patt) ($str_patt)/) {
                my $type = $3;
                my $id = $4;
                my $offset = $1;
                $this_level = (length($2)-1)/2; # num spaces indented
                $delta_levels = $this_level - $last_level;
                if (is_leaf($type) == 0) {
                    #print "br:: lvl: $delta_levels: slen: @stack, id: $id\n";
                    if (@stack > 0 and $delta_levels < 0) {
                        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
                            $tmp = pop(@stack);
                        }
                        push(@stack, $id);
                    } else {
                        push(@stack, $id);
                    }
                } else {
                    $path = get_path($this_level);
                    printf("%10d | %s%s %s\n", $offset, $path, $id, $type);
                }
                #print("last: $last_level, this: $this_level, type: $type\n");
                $last_level = $this_level;
            }
        }
        print "\n";
    }
}

