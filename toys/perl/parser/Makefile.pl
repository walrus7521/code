#!/usr/bin/perl

$path = "..\\..\\..";

$cmd = "c:\\llvm\\bin\\clang -v -S -I$path\\MCP\\Header -I$path\\Common\\Header -I$path\\Model\\Common\\Header -I$path\\Model\\Inner_Loop\\Header -I$path\\Model\\OuterLoop\\Header -I$path\\Lib\\Stellaris_CM3\\Include\\Stellarisware\\inc -I$path\\Tools\\COTS_Libraries\\Stellarisware -I$path\\Tools\\Non_Flight_Code\\Header -Xclang -fdump-record-layouts main_MCP.c > mcp.ast";
system($cmd);

$cmd = "c:\\llvm\\bin\\clang -v -S -I$path\\ADP\\Header -I$path\\Common\\Header -I$path\\Model\\Common\\Header -I$path\\Model\\Outer_Loop\\Header -I$path\\Model\\OuterLoop\\Header -I$path\\Lib\\Stellaris_CM3\\Include\\Stellarisware\\inc -I$path\\Tools\\COTS_Libraries\\Stellarisware -Xclang -fdump-record-layouts main_ADP.c > adp.ast";
system($cmd);


$cmd = ".\\isolate_records.pl < .\\mcp.ast > .\\mcp.recs";
system($cmd);

$cmd = ".\\isolate_records.pl < .\\adp.ast > .\\adp.recs";
system($cmd);

$cmd = "python3 .\\recdec.py -i adp.recs -s TELEMETRY_LOG_STRUCT_ADP < .\\adp.recs > .\\telemetry.parse.adp";
system($cmd);

$cmd = "python3 .\\recdec.py -i adp.recs -s ADP_CLAW_COEFF_STRUCT < .\\adp.recs > .\\coeff.parse.adp";
system($cmd);

$cmd = "python3 .\\recdec.py -i adp.recs -s CONFIG_ADP_STRUCT < .\\adp.recs > .\\config.parse.adp";
system($cmd);

$cmd = "python3 .\\recdec.py -i mcp.recs -s TELEMETRY_LOG_STRUCT < .\\mcp.recs > .\\telemetry.parse.mcp";
system($cmd);

$cmd = "python3 .\\recdec.py -i mcp.recs -s MCP_COEFF_STRUCT < .\\mcp.recs > .\\coeff.parse.mcp";
system($cmd);

$cmd = "python3 .\\recdec.py -i mcp.recs -s CONFIG_MCP_STRUCT < .\\mcp.recs > .\\config.parse.mcp";
system($cmd);

# make binaries for NVRAM
#
$cmd = ".\\struct_to_bin.pl .\\telemetry.parse.adp .\\telemetry.parse.adp.bin";
system($cmd);

$cmd = ".\\struct_to_bin.pl .\\telemetry.parse.mcp .\\telemetry.parse.mcp.bin";
system($cmd);
##

$cmd = "python3 .\\build_coeff_dumper.py < .\\coeff.parse.mcp  > .\\mcp_dump_coeffs.cpp";
system($cmd);

$cmd = "python3 .\\build_mcp_parser.py < .\\telemetry.parse.mcp  > .\\main_mcp.cpp";
system($cmd);

$cmd = "python3 .\\build_adp_parser.py < .\\telemetry.parse.adp  > .\\main_adp.cpp";
system($cmd);

$cmd = "python3 .\\build_attind_parser.py < .\\telemetry.parse.mcp  > .\\ParsedData.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_defs.py < .\\telemetry.parse.mcp  > .\\FlagsDispParseDefs.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_init.py < .\\telemetry.parse.mcp  > .\\FlagsDispParseInit.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_array.py < .\\telemetry.parse.mcp  > .\\FlagsDispParseArray.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_data.py < .\\telemetry.parse.mcp  > .\\FlagsDispParseData.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_defs_adp.py < .\\telemetry.parse.adp  > .\\FlagsDispParseDefsADP.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_init_adp.py < .\\telemetry.parse.adp  > .\\FlagsDispParseInitADP.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_array_adp.py < .\\telemetry.parse.adp  > .\\FlagsDispParseArrayADP.cs";
system($cmd);

$cmd = "python3 .\\build_flagsdisp_parser_data_adp.py < .\\telemetry.parse.adp  > .\\FlagsDispParseDataADP.cs";
system($cmd);

$cmd = "python3 .\\build_plotter.py < .\\telemetry.parse.mcp  > .\\fieldnames.py";
system($cmd);


$cmd = "type .\\boilerplate.cpp > .\\main.cpp";
system($cmd);

$cmd = "type .\\main_mcp.cpp >> .\\main.cpp";
system($cmd);

$cmd = "type .\\main_adp.cpp >> .\\main.cpp";
system($cmd);

$cmd = "type .\\parser_gen.hpp > .\\ParserGen.h";
system($cmd);

$cmd = "type .\\main_mcp.cpp >> .\\ParserGen.h";
system($cmd);

$cmd = "type .\\main_adp.cpp >> .\\ParserGen.h";
system($cmd);

$cmd = "type .\\parser_gen_foot.hpp >> .\\ParserGen.h";
system($cmd);


$cmd = ".\\to_xml.pl < .\\mcp.parse > .\\telemetry.xml";
system($cmd);

$cmd = ".\\calc_sha.pl > .\\telemetry.xml.sha256";
system($cmd);

$cmd = "xcopy /Y .\\main.cpp ..\\FlightTestParser";
system($cmd);

$cmd = "xcopy /Y .\\ParserGen.h ..\\..\\In_Flight_Tools\\CAN_DEMUX\\src";
system($cmd);

$cmd = "xcopy /Y .\\telemetry.xml ..\\..\\In_Flight_Tools\\MaintenanceDisplay";
system($cmd);

$cmd = "xcopy /Y .\\telemetry.xml.sha256 ..\\..\\In_Flight_Tools\\MaintenanceDisplay";
system($cmd);

$cmd = "xcopy /Y .\\ParsedData.cs ..\\..\\In_Flight_Tools\\AttitudeIndicator\\AttitudeIndicator";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseDefs.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseInit.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseArray.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseData.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseDefsADP.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseInitADP.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseArrayADP.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\FlagsDispParseDataADP.cs ..\\..\\In_Flight_Tools\\FlagsDisplay\\FlagsDisplay";
system($cmd);

$cmd = "xcopy /Y .\\fieldnames.py ..\\..\\In_Flight_Tools\\CSV_Plotter";
system($cmd);

$cmd = "xcopy /Y .\\fieldnames.py ..\\..\\In_Flight_Tools\\CAN_DEMUX";
system($cmd);

