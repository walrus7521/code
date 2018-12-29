#!/usr/bin/perl

use Inline::Files;

my @pair;
my @full_names;

while (<ADP_PARSER_BEGIN>) {
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
        print "    parser->Set_Column_Masked(++column, \"$full_names[1]\", TELEMETRY_LOG_STRUCT_ADP, u.$full_names[0], $type, (1 << $shift));\n"
    #elsif (length(@full_names > 1)) {
    #    print "parser->Set_Column(++column, \"$full_names[1]\", TELEMETRY_LOG_STRUCT, $name, $type)\n"
    } else {
        print "    parser->Set_Column(++column, \"$name\", TELEMETRY_LOG_STRUCT_ADP, $name, $type);\n"
    }
}
print "\n";

while (<ADP_PARSER_END>) {
    print $_;
}

__ADP_PARSER_BEGIN__
static Parser_Alias * Create_ADP_Telemetry_Parser(const std::string & filename)
{    
    int column = -1;
    Parser<TELEMETRY_LOG_STRUCT_ADP> * parser = new Parser<TELEMETRY_LOG_STRUCT_ADP>(filename);
    parser->Duplicate_To_Combined_File(true);

    parser->Set_Lines_Per_File(25000);


__ADP_PARSER_END__
    return parser;
}

