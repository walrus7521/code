#!/usr/bin/perl

#$cmd = ".\\isolate_records.pl < .\\mcp.ast > .\\mcp.recs";
#system($cmd);

#$cmd = "./recdec.pl < telem.rec > out";
$cmd = "recdec.pl < telem.rec > out";
#-s TELEMETRY_LOG_STRUCT_ADP < .\\adp.recs > .\\telemetry.parse.adp";
system($cmd);

#$cmd = "python3 .\\recdec.py -i mcp.recs -s MCP_COEFF_STRUCT < .\\mcp.recs > .\\coeff.parse.mcp";
#system($cmd);

#$cmd = "python3 .\\recdec.py -i mcp.recs -s CONFIG_MCP_STRUCT < .\\mcp.recs > .\\config.parse.mcp";
#system($cmd);

#$cmd = ".\\isolate_records.pl < .\\adp.ast"; # > .\\adp.recs";
#system($cmd);

#$cmd = "python3 .\\recdec.py -i adp.recs -s ADP_CLAW_COEFF_STRUCT < .\\adp.recs > .\\coeff.parse.adp";
#system($cmd);

#$cmd = "python3 .\\recdec.py -i adp.recs -s CONFIG_ADP_STRUCT < .\\adp.recs > .\\config.parse.adp";
#system($cmd);

#$cmd = ".\\struct_to_bin.pl .\\telemetry.parse.adp .\\telemetry.parse.adp.bin";
#system($cmd);

#$cmd = ".\\struct_to_bin.pl .\\telemetry.parse.mcp .\\telemetry.parse.mcp.bin";
#system($cmd);

