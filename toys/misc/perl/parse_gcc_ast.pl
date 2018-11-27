#!/usr/bin/perl

# gcc test.c -fdump-translation-unit
# https://gcc.gnu.org/onlinedocs/gcc-8.2.0/gccint.pdf

# find var_decl => telem_data
# 
#$struct_name = "TELEMETRY_LOG_STRUCT_ADP";
$struct_name = "";
$arraybase[6000] =0;
$max_file_idx = 0;

#print $#ARGV;
my $nargs = $#ARGV + 1;
if ($nargs < 2) {
    print "please pass in the name of the data structure and input TU file name\n";
}
$struct_name = $ARGV[0];
$file_name = $ARGV[1];
#print "struct: $struct_name $file_name\n";
#exit();

open(my $fh, '<:encoding(UTF-8)', $file_name)
  or die "Could not open file '$file_name' $!";

# scan in the file
while(<$fh>) {
    if ($_ =~ /^(@\d+)(.*)/) {
        $node_num = $1;
        my $foo = reverse($node_num);
        chop($foo);
        $node_num = reverse($foo);
        $arraybase[$node_num] = $_;
    }
}

sub find_struct_name_node {
    my $name = shift;
    my $id = "";
    my $len = scalar(@arraybase);
    # 1. find identifier_node TELEMETRY_LOG_STRUCT
    for my $key (0 .. $#arraybase) {
        $val = @arraybase[$key];
        if ($val =~ /$name/) {
            $id = $key;
            # 2. search backwards for line with name: $id
            $prev_node = $id - 1;
            while ($prev_node >= 0) {
                $line = @arraybase[$prev_node];
                if ($line =~ /$id/) {
                    # 3. extract type: (record)
                    if ($line =~ /type: (@\d+)(.*)/) {
                        $type_index = $1;
                        my $foo = reverse($type_index);
                        chop($foo);
                        $type_index = reverse($foo);
                        $line = @arraybase[$type_index];
                        if ($line =~ /unql: (@\d+)(.*)/) {
                            if ($line =~ /flds: @(\d+)(.*)/) {
                                $fields_idx = $1;
                                return $fields_idx;
                            }
                        }
                    }
                }
                $prev_node--;
            }
        }
    }    
}

sub get_type {
    $type_index = shift;
    $str = @arraybase[$type_index];
    $str =~ /\s+(.*)_type /;
    return $1;
}

sub translate_type {
    $type_index = shift;
    $str = @arraybase[$type_index];
    $str =~ /\s+(.*)_type /;
    if ($1 =~ /int/)  {
        return "U32_Type";
    } elsif ($1 =~ /real/) {
        return "F32_Type";
    } elsif ($1 =~ /enumeral/) {
        return "BOOLEAN_Type";
    }
    return $1;
}

sub get_name {
    $name_index = shift;
    $str = @arraybase[$name_index];
    $str =~ /strg: (\w+).*/;
    return $1;
}

sub parse_record {
    my $struct_name = shift;
    my $record_index = shift;

    my $len = scalar(@arraybase);
    my $line = @arraybase[$record_index];
    $line =~ /flds: @(\d+) /;
    my $fields_idx = $1;
    my $next_node = $fields_idx;

    while ($next_node < $len) {
        $line = @arraybase[$next_node];
        if ($line =~ /field_decl/) {
            (my $name_offset, $type_offset) = $line =~ /name: @(\d+).*type: @(\d+)/;
            $var_type = translate_type($type_offset);
            $var_name = get_name($name_offset);
            print "$struct_name.$var_name, $var_type\n";
            $next_node = $name_offset; # increment node to next field_decl
            if ($line !~ /chain:/) {
                return;
            }
        } else {
            $next_node++; # increment node to next field_decl
        }
    }
}

sub parse_union {
    my $union_name = shift;
    my $union_index = shift;

    my $line = @arraybase[$union_index];
    my $len = scalar(@arraybase);

    if ($line !~ /union_type/) {
        print "bogus union type\n";
        return;
    }
    $line =~ /flds: @(\d+) /;

    my $union_idx = $1;
    my $next_node = $union_idx;

    my $bit_field_count = 0;
    while ($next_node < $len) {
        $line = @arraybase[$next_node];
        if ($line =~ /field_decl/) {
            if ((my $name_offset, $type_offset) = $line =~ /name: @(\d+).*type: @(\d+)/) {
                $var_type = translate_type($type_offset);
                $var_name = get_name($name_offset);
                my $tmp = @arraybase[$type_offset];
                $tmp =~ /prec: (\d+)/;
                my $prec = $1;
                if ($prec == 1) {
                    $var_type = "BOOLEAN_Type";
                    print "$union_name.$var_name, $var_type, $bit_field_count\n";
                    $bit_field_count++;
                } else {
                    # override union name with this name
                    $union_name = $var_name;
                }
                $next_node = $name_offset; # increment node to next field_decl
                if ($line !~ /chain:/) {
                    return;
                }
                $line =~ /chain: @(\d+) /;
                $next_node = $1;
            } elsif ($line =~ /type: @(\d+)/) {
                # got a record
                $next_node++;
            }
        } else {
            $next_node++; # increment node to next field_decl
        }
    }
    
    return;
}

sub parse_enum {
    my $enum_name = shift;
    my $enum_index = shift;
    print "enum: $enum_index\n";
    print "name: $enum_name\n";
    print "parse_enum is broken!!\n";
    return; # broken!!

    my $next_node = $enum_index;
    my $line = @arraybase[$next_node];
    # 1. grag unql: and read line
    $line =~ /unql: @(\d+)(.*)/;
    $unql_index = $1;
    # 2. @line read csts: @2902 => first tree_list
    # this needs rewriting
    #$unql_line_no = 0get_line_at($unql_index); # line no in filebase
    $line = @filebase[$unql_line_no+2];
    $line =~ /csts: @(\d+)(.*)/;
    $first_tree = $1;
    # 3. walk the tree
    $next_node = $first_tree;
    my $len = scalar(@arraybase);
    while ($next_node < $len) {
        $line = @arraybase[$next_node];
        if ($line =~ /tree_list/) {
            $line =~ /purp: @(\d+)(.*)/;
            $purp_node = $1;
            $name = get_name($purp_node);
            print "$enum_name.$name, BOOLEAN_Type\n";
            if ($line =~ /chan: @(\d+)(.*)/) {
                $next_node = $1;
            } else {
                return;
            }
        } else {
            $next_node++;
        }
    }
}

sub dump_struct_fields {
    my $next_node = shift;
    my $len = scalar(@arraybase);
    $i = 0;
    # follow links - find field_decl    
    while ($next_node < $len) {
        my $context = @arraybase[$next_node];
        if ($context =~ /field_decl/) {
            #print "context: $context\n";
            #if ((my $name_offset, $type_offset, $chain_offset) = $context =~ /name: @(\d+).*type: @(\d+).*chain: @(\d+)/) {
            if ((my $name_offset, $type_offset) = $context =~ /name: @(\d+).*type: @(\d+)/) {
                my $var_type = get_type($type_offset);
                my $var_name = get_name($name_offset);
                #print "field: $next_node : $name_offset => $var_name, $type_offset => $var_type => $chain_offset\n";
                if ($var_type =~ /record/) {
                    parse_record($var_name, $type_offset);
                } elsif ($var_type =~ /enumeral/) {
                    #parse_enum($var_name, $type_offset); # broken
                } elsif ($var_type =~ /union/) {
                    parse_union($var_name, $type_offset);
                } else {
                   $var_type = translate_type($type_offset);
                   print "$var_name, $var_type\n";
                }
                if ((my $chain_offset) = $context =~ /chain: @(\d+)/) {
                    $next_node = $chain_offset;
                } else {
                    return;
                }
                if ($context !~ /chain:/) {
                    return;
                }
            }
        } else {
            $next_node++;
        }
    }
}

$id_node = find_struct_name_node($struct_name); # needs work finding var_decl = telem_data
#print "id: $id_node\n";
#print @arraybase;
dump_struct_fields($id_node);

