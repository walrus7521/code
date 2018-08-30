#include <stdio.h>
#include <Windows.h>
#include <string>

using std::string;

// useful tool for printing debug traces to DebugView from APPs or DLLs
void trace(string msg)
{
    OutputDebugString(msg.c_str());
}
