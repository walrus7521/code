#!/usr/bin/perl

# https://stackoverflow.com/questions/15800230/how-can-i-dump-an-abstract-syntax-tree-generated-by-gcc-into-a-dot-file
# gcc test.c -fdump-tree-all-graph

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
    my $name = shift;
    my $id = "";
    my $len = scalar(@arraybase);
    for my $key (0 .. $#arraybase) {
        $val = @arraybase[$key];
        if ($val =~ /$name/) {
            $id = $key;
            $next_node = $id;
            $next_node++;
            while ($next_node < $len) {
                $line = @arraybase[$next_node];
                if ($line =~ /record_type/) {
                    for ($i = 0; $i < $max_file_idx; $i++) {
                        $fline = @filebase[$i];
                        if ($fline =~ /^$line/) {
                            $fline = @filebase[$i+1];
                            $fline =~ /flds: @(\d+)/;
                            $fields_idx = $1;
                            return $fields_idx;
                        }
                    }
                }
                $next_node++;
            }
        }
    }    
}

sub get_type {
    $type_index = shift;
    $str = @arraybase[$type_index];
    $str =~ /\s+(.*)_type /;
    if ($1 =~ /int/)  {
        return "U32_Type";
    }
    elsif ($1 =~ /real/) {
        return "F32_Type";
    }
    return $1;
}

sub get_name {
    $name_index = shift;
    $str = @arraybase[$name_index];
    $str =~ /strg: (\w+)\s+ /;
    return $1;
}

sub get_fields_offset {
    $search_field = shift;
    substr($search_field, 0, 0) = '@';
    #print "search: $search_field\n";
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
            $var_type = get_type($type_offset);
            $var_name = get_name($name_offset);
            #print "$var_name, $var_type\n";
            #$prev_line = @arraybase[$next_node-1];
            #if ($i > 0 && $prev_line !~ /identifier_node/) { return; } # exclude zeroth line
            #$i++;
            #print "current: $next_node, next: $name_offset, name: $var_name, type: $var_type\n";
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
            } else {
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

$id_node = find_id_node($struct_name);
#$id_node = 3228;
#print "id: $id_node\n";
find_fields($id_node);

