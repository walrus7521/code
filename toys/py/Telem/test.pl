#!/usr/bin/perl

#$cmd = "python3 .\\recdec.py -i adp.recs -s TELEMETRY_LOG_STRUCT_ADP < .\\adp.recs > .\\telemetry.parse.adp";
#system($cmd);

#$cmd = "python3 .\\build_plotter.py < .\\telemetry.parse.mcp  > .\\fieldnames.py";
#system($cmd);

#$cmd = "python3 .\\build_plotter.py < .\\telemetry.parse.mcp  > .\\fieldnames.py";
#system($cmd);

#$cmd = "python3 .\\build_mcp_parser.py < .\\telemetry.parse.mcp  > .\\main_mcp.cpp";
#system($cmd);

$cmd = "python3 .\\recdec.py -i adp.recs -s TELEMETRY_LOG_STRUCT_ADP < .\\adp.recs > .\\telemetry.parse.adp";
system($cmd);

#$cmd = "python3 .\\build_adp_parser.py < .\\telemetry.parse.adp  > .\\main_adp.cpp";
#system($cmd);


