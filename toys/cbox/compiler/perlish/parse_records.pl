#!/usr/bin/env perl

my @file = <stdin>; # slurp in the whole file
my @stack = (); # path accumulation stack (struct names by nesting)

$str_patt = "[a-zA-Z]+[a-zA-Z0-9_]*"; # regex for valid struct & field names
@primitives = ( # a priori types
    "F32", "f32", "U32", "u32", "S32", "s32", "U16", "u16", "S16", "s16",
    "U8",  "u8",  "S8",  "s8", "BOOLEAN");
@types = ("union", "struct"); # a priori C structure types

sub is_prim {
    $x = shift;
    foreach my $p (@primitives) { if ($x eq $p) { return 1; } }
    return 0;
}

sub is_type {
    $x = shift;
    foreach my $p (@types) { if ($x eq $p) { return 1; } }
    return 0;
}

sub get_path {
    my @tmp1 = @stack;
    my @tmp2;
    my $path = "";
    if (@stack == 0) { return ""; }
    while (@tmp1) { my $tmp = pop(@tmp1); push(@tmp2, $tmp); } # reverse @stack
    while (@tmp2) { $val = pop @tmp2; $path = $path . $val . "."; } # build path
    return $path;
}

for(my $i = 0; $i < scalar(@file); $i++) {
    my $line = @file[$i];
    if ((my $struct_name) = $line =~ /0 \| ($str_patt)/) {
        @stack = (); # empty out the path stack
        my $last_level = 0;
        my $this_level = 0;
        my $delta_levels = 0;
        my $is_union_or_struct = 0;
        my $bit_count = 0;
        my $bit_width = 0;
        print "$struct_name\n";
        my $j = $i+1;
        my $sline;
        while ($sline = @file[$j++] and $sline !~ /sizeof/) { # "sizeof" indicates an attributes record
            # valid lines begin with: OFFSET | TYPE ID => note: $num_spaces is used to determine nesting level
            if ((my $offset, my $num_spaces, my $type, my $id) = $sline =~ /(\d+).*?\|(\s+)($str_patt) ($str_patt)/) {
                $this_level = (length($num_spaces)-1)/2; # num spaces indented
                $delta_levels = $this_level - $last_level;
                if ((my $rec_num, my $bit_start, my $bit_end) = $sline =~ /(\d+):(\d+)-(\d+)/) {
                    $bit_width = abs(int($bit_start) - int($bit_end)) + 1;
                    $path = get_path();
                    printf("%10d, %s%s, BOOLEAN_Type:%d-%d\n", $offset, $path, $id, $bit_count, $bit_width);
                    $bit_count++;
                    if (length($bit_start) == 0 and length($bit_end) == 0) {
                        $is_union_or_struct = 0;
                        print "done type: $bit_start $bit_end\n";
                    }
                }
                elsif (is_type($type) == 1) {
                    if ($type == "union") {
                        $is_union_or_struct = $this_level;
                        $bit_count = 0;
                        push(@stack, $id);
                        $j += 2;
                    }
                } elsif (is_prim($type) == 0) {
                    $len = @stack;
                    if ($id =~ /flags/) {
                        if ($is_union_or_struct) { # skip 2 lines
                            pop(@stack); # need 2 pops due to union
                            pop(@stack);
                        }
                        my $tmp_line = @file[$j+1];
                        (my $dummy1, my $dummy2, my $dummy3, my $bf_name) = $tmp_line =~ /(\d+) |.*?struct ($str_patt)::\((.*?)\) ($str_patt)/;
                        push(@stack, $id);
                        push(@stack, $bf_name);
                        $is_union_or_struct = $this_level;
                        $bit_count = 0;
                        $j += 2;
                    }
                    elsif ($len > 0 and $delta_levels < 0) {
                        for (my $i = 0; $i < abs($delta_levels) and @stack > 0; $i++) {
                            pop(@stack); # backup delta_levels of structures
                        }
                        push(@stack, $id); # put the new struct on stack
                    } else {
                        push(@stack, $id);
                    }
                } else {
                    if ($len > 0 and $delta_levels < 0) {
                        pop(@stack);
                    }
                    if ($is_union_or_struct > 0) {
                        pop(@stack); # need 2nd pop due to union
                    }
                    $path = get_path();
                    printf("%10d, %s%s, %s\n", $offset, $path, $id, $type);
                    $len = @stack;
                }
                $last_level = $this_level;
            }
        }
        print "\n";
    }
}

