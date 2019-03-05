// skeleton.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


__declspec(dllexport)
int dude(char *msg)
{
    cout << msg << endl;
    return 42;
}

#ifdef __cplusplus
}
#endif // __cplusplus

