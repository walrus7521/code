#!/usr/bin/perl

$path = "..\\..\\..";

$cmd = "c:\\llvm\\bin\\clang -v -S -I$path\\MCP\\Header -I$path\\Common\\Header -I$path\\Model\\Common\\Header -I$path\\Model\\Inner_Loop\\Header -I$path\\Model\\OuterLoop\\Header -I$path\\Lib\\Stellaris_CM3\\Include\\Stellarisware\\inc -I$path\\Tools\\COTS_Libraries\\Stellarisware -Xclang -fdump-record-layouts main_MCP.c > mcp.ast";
system($cmd);

$cmd = ".\\isolate_records.pl < .\\mcp.ast > .\\mcp.recs";
system($cmd);

$cmd = ".\\parse_records.pl < .\\mcp.recs > .\\mcp.parse";
system($cmd);

$cmd = ".\\gen_telemetry.pl < .\\mcp.parse > .\\telemetry.parse.mcp";
system($cmd);

$cmd = ".\\to_xml.pl < .\\mcp.parse > .\\telemetry.xml";
system($cmd);

$cmd = ".\\calc_sha.pl > .\\telemetry.xml.sha256";
system($cmd);

