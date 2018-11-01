#!/usr/bin/perl

# gcc test.c -fdump-translation-unit
# https://gcc.gnu.org/onlinedocs/gcc-8.2.0/gccint.pdf

# find var_decl => telem_data
# 
$struct_name = "TELEMETRY_LOG_STRUCT";
$arraybase[6000] =0;
$filebase[30000] =0;
$max_file_idx = 0;

# scan in the file
while(<>) {
    $filebase[$max_file_idx++] = $_;
    if ($_ =~ /^(@\d+)(.*)/) {
        $node_num = $1;
        my $foo = reverse($node_num);
        chop($foo);
        $node_num = reverse($foo);
        $arraybase[$node_num] = $_;
    }
}

sub find_id_node {
    # 1. find @3229 identifier_node TELEMETRY_LOG_STRUCT
    # 2. search backwards for type_decl name: @3229
    # 3. from @3229 --> type: @3230 (record)
    # 4. from @3230 --> unql: @3217
    # 5. in field below @3217 flds: @3228
    # 6. return @3228
    my $name = shift;
    my $id = "";
    my $len = scalar(@arraybase);
    # 1. find @3229 identifier_node TELEMETRY_LOG_STRUCT
    for my $key (0 .. $#arraybase) {
        $val = @arraybase[$key];
        if ($val =~ /$name/) {
            $id = $key;
            # 2. search backwards for line with name: $id
            $prev_node = $id - 1;
            while ($prev_node >= 0) {
                $line = @arraybase[$prev_node];
                if ($line =~ /$id/) {
                    # 3. from @3229 extract type: @3230 (record)
                    if ($line =~ /type: (@\d+)(.*)/) {
                        $type_index = $1;
                        my $foo = reverse($type_index);
                        chop($foo);
                        $type_index = reverse($foo);
                        $line = @arraybase[$type_index];
                        if ($line =~ /unql: (@\d+)(.*)/) {
                            $unql_index = $1;
                            # linear search through filebase for line after @3217
                            # and grab flds: @3228 ::: the magic number
                            for ($i = 0; $i < $max_file_idx; $i++) {
                                $fline = @filebase[$i];
                                if ($fline =~ /^$unql_index/) {
                                    $fline = @filebase[$i+1];
                                    $fline =~ /flds: @(\d+)/;
                                    $fields_idx = $1;
                                    return $fields_idx;
                                }
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
    }
    elsif ($1 =~ /real/) {
        return "F32_Type";
    }
    elsif ($1 =~ /enumeral/) {
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

sub get_fields_offset {
    $search_field = shift;
    substr($search_field, 0, 0) = '@';
    for ($i = 0; $i < $max_file_idx; $i++) {
        $line = @filebase[$i];
        if ($line =~ /^$search_field/) {
            $line = @filebase[$i+1];
            $line =~ /flds: @(\d+)/;
            $fields_idx = $1;
            return $fields_idx;
        }
    }
}

sub parse_record {
    my $struct_name = shift;
    my $record_index = shift;

    $unique_idx = $record_index++;
    $line = @arraybase[$unique_idx];
    my $len = scalar(@arraybase);

    $line =~ /unql: @(\d+) /;
    $field_idx = $1;
    $fields_idx = get_fields_offset($field_idx);
    $next_node = $fields_idx;
    $i = 0;

    while ($next_node < $len) {
        $line = @arraybase[$next_node];
        if ($line =~ /field_decl/) {
            my($name_offset, $type_offset) = $line =~ /name: @(\d+).*type: @(\d+)/;
            $var_type = translate_type($type_offset);
            $var_name = get_name($name_offset);
            print "$struct_name.$var_name, $var_type\n";
            $next_node = $name_offset; # increment node to next field_decl
            $next_node++;
            $cur_line = @arraybase[$next_node];
            if ($i > 0 && ($cur_line !~ /field_decl/)) {
                return; 
            } # exclude zeroth line
            $i++;
        } else {
            $next_node++; # increment node to next field_decl
        }
    }
}

sub get_line_at {
    $target = shift;
    for ($i = 0; $i < $max_file_idx; $i++) {
        $line = @filebase[$i];
        if ($line =~ /^\@$target/) {
            return $i;
        }
    }
    return -1;
}

sub parse_enum {
    my $enum_name = shift;
    my $enum_index = shift;
    #print "enum: $enum_index\n";
    #print "name: $enum_name\n";
    $next_node = $enum_index;
    $line = @arraybase[$next_node];
    # 1. grag unql: @2893 and read line
    $line =~ /unql: @(\d+)(.*)/;
    $unql_index = $1;
    #print "unql: $unql_index\n";
    # 2. @line read csts: @2902 => first tree_list
    $unql_line_no = get_line_at($unql_index); # line no in filebase
    $line = @filebase[$unql_line_no+2];
    #print "line: $line\n";
    $line =~ /csts: @(\d+)(.*)/;
    $first_tree = $1;
    #print "tree: $first_tree\n";
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

sub find_fields {
    my $next_node = shift;
    my $len = scalar(@arraybase);
    $i = 0;
    # follow links - find field_decl    
    while ($next_node < $len) {
        $context = @arraybase[$next_node];
        if ($context =~ /field_decl/) {
            my($name_offset, $type_offset) = $context =~ /name: @(\d+).*type: @(\d+)/;
            $var_type = get_type($type_offset);
            $var_name = get_name($name_offset);
            if ($var_type =~ /record/) {
                parse_record($var_name, $type_offset);
            } elsif ($var_type =~ /enumeral/) {
                parse_enum($var_name, $type_offset);
            } else {
                $var_type = translate_type($type_offset);
                print "$var_name, $var_type\n";
            }
            $prev_line = @arraybase[$next_node-1];
            if ($i > 0 && $prev_line !~ /identifier_node/) { return; } # exclude zeroth line
            $next_node = $name_offset; # increment node to next field_decl
            $next_node++;
            $cur_line = @arraybase[$next_node];
            if ($i > 0 && ($cur_line !~ /field_decl/)) {
                return; # we're done here
            } # exclude zeroth line
            $i++;
        } else {
            $next_node++; # increment node to next field_decl
        }
    }
}

$id_node = find_id_node($struct_name); # needs work finding var_decl = telem_data
#$id_node = 3228; # this is what should be returned for var_decl = telem_data
#print "id: $id_node\n";
find_fields($id_node);

