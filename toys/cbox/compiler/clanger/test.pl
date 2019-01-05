#!/usr/bin/perl

$path = "C:\\Helitrak\\Servo200_FLT\\SwDev";

$cmd = "c:\\llvm\\bin\\clang -I$path\\MCP\\Header -I$path\\Common\\Header -I$path\\Model\\Common\\Header -I$path\\Model\\Inner_Loop\\Header -I$path\\Model\\OuterLoop\\Header -I$path\\Lib\\Stellaris_CM3\\Include\\Stellarisware\\inc -I$path\\Tools\\COTS_Libraries\\Stellarisware -Xclang -ast-dump -fsyntax-only -E main_MCP.c > mcp.ast";
system($cmd);

exit;

