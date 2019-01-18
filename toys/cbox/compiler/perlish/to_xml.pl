#!/usr/bin/env perl

use Inline::Files;

$struct = "TELEMETRY_LOG_STRUCT";

# suck in mcp.parse
# spew out telemety.xml
#
$str_patt = "[a-zA-Z]+[a-zA-Z0-9_.]*";

while (<XML_BEGIN>) {
    print $_;
}

%primitive_map = {
    {"f32", 4},
};


my %primitive_mapping = (
    "f32"       => 4,
    "u32"       => 4,
    "s32"       => 4,
    "u16"       => 4,
    "s16"       => 4,
    "u8"        => 4,
    "s6"        => 4,
    "boolean"   => 1
);

sub get_size {
    $x = shift;
    foreach my $p (keys %primitive_mapping) {
        if ($x =~ /$p/i) { 
            return %primitive_mapping{$p};
        } 
    }
    return 0;
}


my $line;
while ($line = <stdin>) {
    if ($line =~ /$struct/) {
        while ($line = <stdin> and $line =~ /$str_patt/) {

            if ($line =~ /(\d+), ($str_patt), (.*)/) {

                $offset = $1;
                $type = $3;
                $name = $2;

                $size = get_size($type);

                print "    <datum>\n";
                print "        <name>$name</name>\n";
                print "        <type>$type</type>\n";
                print "        <offset>$offset</offset>\n";
                print "        <size>$size</size>\n";
                print "     </datum>\n";
            }

        }
    }

}

while (<XML_END>) {
    print $_;
}

__XML_BEGIN__
<?xml version="1.0" encoding="UTF-8"?>
<root>
    <version>
        <major>1</major>
        <minor>0</minor>
        <build>0</build>
        <revision>0</revision>
    </version>
    <telemetry>
__XML_END__
    </telemetry>
</root>

