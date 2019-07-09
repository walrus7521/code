#!/usr/bin/perl

$cmd = "python3 .\\recdec.py -i adp.recs -s TELEMETRY_LOG_STRUCT_ADP < .\\adp.recs > .\\telemetry.parse.adp";
system($cmd);

