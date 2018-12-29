#!/usr/bin/perl

use Inline::Files;

my @pair;
my @full_names;

while (<MCP_PARSER_BEGIN>) {
    print $_;
}

while (<>) {
    chomp;
    #print $_;
    undef @pair;
    undef @full_names;
    @pair = split(/\,/, $_);
    #print @pair;
    $name = @pair[0];
    $type = @pair[1];
    my @full_names = split(/\./, $name);
    #print "$name, $type\n";
    if ($type =~ /BOOLEAN_Type/) {
        $_ =~ /BOOLEAN_Type, (\d+)/;
        $shift = $1;
        print "    parser->Set_Column_Masked(++column, \"$full_names[1]\", TELEMETRY_LOG_STRUCT, u.$full_names[0], $type, (1 << $shift));\n"
    #elsif (length(@full_names > 1)) {
    #    print "parser->Set_Column(++column, \"$full_names[1]\", TELEMETRY_LOG_STRUCT, $name, $type)\n"
    } else {
        print "    parser->Set_Column(++column, \"$name\", TELEMETRY_LOG_STRUCT, $name, $type);\n"
    }
}
print "\n";

while (<MCP_PARSER_END>) {
    print $_;
}

__MCP_PARSER_BEGIN__
static Parser_Alias * Create_MCP_Telemetry_Parser(const std::string & filename)
{
    Parser<TELEMETRY_LOG_STRUCT> * parser = new Parser<TELEMETRY_LOG_STRUCT>(filename);
	int column = -1;

    parser->Duplicate_To_Combined_File(true);

    // Set the max number of lines per file. When this limit is reached, a new file is created.
    parser->Set_Lines_Per_File(25000);

    // Uncomment this to enable a combined file which has all data (in addition to the files that are split apart
    // based on the number of lines).
    // parser->Duplicate_To_Combined_File(true);

    // Set up the format for the output CSV file. These are the order of the arguments and what they do:
    //
    // First arg: The column number in the CSV file. Column numbers start at zero (first column is 0, second column is 1, etc.)
    // Second arg: The header for the column that will be printed out in the first row of the CSV file
    // Third arg: The structure that was saved via CANDEMUX. This will usually be a telemetry structure or something similar.
    // Fourth arg: The variable inside the structure (from the third arg) that will be saved in this column.
    // Fifth arg: The type of the variable (the fourth arg) -- F32, U32, BOOLEAN, etc.

__MCP_PARSER_END__
    return parser;
}
    
__ADP_PARSER_BEGIN__
static Parser_Alias * Create_ADP_Telemetry_Parser(const std::string & filename)
{    
    Parser<TELEMETRY_LOG_STRUCT_ADP> * parser = new Parser<TELEMETRY_LOG_STRUCT_ADP>(filename);
    parser->Duplicate_To_Combined_File(true);

    parser->Set_Lines_Per_File(25000);


__ADP_PARSER_END__
    return parser;
}

