#!/usr/bin/perl

$path = "..\\..\\..";

$cmd = "gcc.exe -I$path\\ADP\\Header -I$path\\Common\\Header -I$path\\Model\\Common\\Header -I$path\\Model\\Inner_Loop\\Header -I$path\\Model\\OuterLoop\\Header -I$path\\Lib\\Stellaris_CM3\\Include\\Stellarisware\\inc -I$path\\Tools\\COTS_Libraries\\Stellarisware main_ADP.c -S -fdump-translation-unit";
system($cmd);

$cmd = "gcc.exe -I$path\\MCP\\Header -I$path\\Common\\Header -I$path\\Model\\Common\\Header -I$path\\Model\\Inner_Loop\\Header -I$path\\Model\\OuterLoop\\Header -I$path\\Lib\\Stellaris_CM3\\Include\\Stellarisware\\inc -I$path\\Tools\\COTS_Libraries\\Stellarisware main_MCP.c -S -fdump-translation-unit";
system($cmd);


$cmd = ".\\meld_AST_lines.pl < .\\main_ADP.c.001t.tu > .\\meld_ADP.tu";
system($cmd);

$cmd = ".\\meld_AST_lines.pl < .\\main_MCP.c.001t.tu > .\\meld_MCP.tu";
system($cmd);

$cmd = "parse_gcc_ast.pl TELEMETRY_LOG_STRUCT_ADP meld_ADP.tu > telemetry.parse.adp";
system($cmd);

$cmd = "parse_gcc_ast.pl TELEMETRY_LOG_STRUCT meld_MCP.tu > telemetry.parse.mcp";
system($cmd);

$cmd = ".\\build_adp_parser.pl < .\\telemetry.parse.adp  > .\\main_adp.cpp";
system($cmd);

$cmd = ".\\build_mcp_parser.pl < .\\telemetry.parse.mcp  > .\\main_mcp.cpp";
system($cmd);

$cmd = "type .\\boilerplate.cpp > .\\main.cpp";
system($cmd);

$cmd = "type .\\main_mcp.cpp >> .\\main.cpp";
system($cmd);

$cmd = "type .\\main_adp.cpp >> .\\main.cpp";
system($cmd);

$cmd = "xcopy /Y .\\main.cpp ..\\FlightTestParser";
system($cmd);

$cmd = "type .\\parser_gen.hpp > .\\ParserGen.h";
system($cmd);

$cmd = "type .\\main_mcp.cpp >> .\\ParserGen.h";
system($cmd);

$cmd = "type .\\parser_gen_foot.hpp >> .\\ParserGen.h";
system($cmd);

$cmd = "xcopy /Y .\\ParserGen.h ..\\..\\In_Flight_Tools\\CAN_DEMUX_LIVE\\src";
system($cmd);

