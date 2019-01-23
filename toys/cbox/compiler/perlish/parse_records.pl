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

sub is_prim {
    $x = shift;
    foreach my $p (@primitives) { if ($x eq $p) { return 1; } }
    return 0;
}
@types = (
    "union", "struct"
);
sub is_type {
    $x = shift;
    foreach my $p (@types) { if ($x eq $p) { return 1; } }
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
my $is_union_or_struct = 0;
my $bit_count = 0;
my $bit_width = 0;
for(my $i = 0; $i < scalar(@file); $i++) {
    my $line = @file[$i];
    if ($line =~ /0 \| ($str_patt)/) {
        @stack = ();
        $last_level = 0;
        $this_level = 0;
        $delta_levels = 0;
        $is_union_or_struct = 0;
        $bit_count = 0;
        $bit_width = 0;
        print "$1\n";
        my $j = $i+1;
        my $sline;
        while ($sline = @file[$j++] and $sline !~ /sizeof/) {
            if ($sline =~ /(\d+).*?\|(\s+)($str_patt) ($str_patt)/) {
                my $type = $3;
                my $id = $4;
                my $offset = $1;
                #print "type: $type\n";
                $this_level = (length($2)-1)/2; # num spaces indented
                $delta_levels = $this_level - $last_level;
                if ($sline =~ /(\d+):(\d+)-(\d+)/) {
                    $bit_width = abs(int($2) - int($3)) + 1;
                    $path = get_path($this_level);
                    #print "bool: $id\n";
                    printf("%10d, %s%s, BOOLEAN_Type:%d-%d\n", $offset, $path, $id, $bit_count, $bit_width);
                    $bit_count++;
                    #printf("done yet? $sline\n");
                    if (length($2) == 0 and length($3) == 0) {
                        $is_union_or_struct = 0;
                        print "done type: $2 $3\n";
                    }
                }
                elsif (is_type($type) == 1) {
                    if ($type == "union") {
                        $is_union_or_struct = $this_level;
                        #print "got a type: $type @ $id -> $is_union_or_struct\n";
                        $bit_count = 0;
                        push(@stack, $id);
                        $j += 2;
                    }
                    #printf("%10d, %s%s, %s\n", $offset, $path, $id, $type);
                } elsif (is_prim($type) == 0) {
                    $len = @stack;
                    #print "br:: lvl: $delta_levels: slen: $len, id: $id\n";
                    if ($id =~ /flags/) {
                        #print "got a type2: $id, $type @ $is_union_or_struct\n";
                        # skip 2 lines
                        if ($is_union_or_struct) {
                            $tmp = pop(@stack); # need 2 pops due to union
                            $tmp = pop(@stack);
                        }
                        my $tmp_line = @file[$j+1];
                        $tmp_line =~ /(\d+) |.*?struct ($str_patt)::\((.*?)\) ($str_patt)/;
                        my $bf_name = $4;
                        #print "cap: $1, $2, +> $3, $4\n";
                        #print "push: $id - $bf_name\n";
                        push(@stack, $id);
                        push(@stack, $bf_name);
                        $is_union_or_struct = $this_level;
                        $bit_count = 0;
                        $j += 2;
                    }
                    elsif ($len > 0 and $delta_levels < 0) {
                        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
                            $tmp = pop(@stack);
                        }
                        push(@stack, $id);
                    } else {
                        push(@stack, $id);
                    }
                } else {
                    if ($len > 0 and $delta_levels < 0) {
                        $tmp = pop(@stack);
                    }
                    #printf("done yet2? $sline\n");
                    if ($is_union_or_struct > 0) {
                        $tmp = pop(@stack); # need 2 pops due to union
                    }
                    $path = get_path($this_level);
                    printf("%10d, %s%s, %s\n", $offset, $path, $id, $type);
                    $len = @stack;
                }
                #print("last: $last_level, this: $this_level, type: $type\n");
                $last_level = $this_level;
            }
        }
        print "\n";
    }
}

