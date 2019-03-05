// skeleton.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

__declspec(dllexport) int dude(char *msg)
{
    cout << msg << endl;
    return 42;
}

