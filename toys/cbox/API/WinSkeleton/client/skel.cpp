// skel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "..\server\skeleton.h"

typedef int(CALLBACK* LPFNDLLFUNC1)(char *);

int LoadAndCallSomeFunction(DWORD dwParam1, UINT * puParam2)
{
    HINSTANCE hDLL;               // Handle to DLL
    LPFNDLLFUNC1 lpfnDllFunc1;    // Function pointer
    int hrReturnVal;

    hDLL = LoadLibrary(L"skeleton.dll");
    if (NULL != hDLL)
    {
        lpfnDllFunc1 = (LPFNDLLFUNC1)GetProcAddress(hDLL, "dude");
        if (NULL != lpfnDllFunc1)
        {
            // call the function
            hrReturnVal = lpfnDllFunc1("wusup");
        }
        else
        {
            // report the error
            hrReturnVal = ERROR_DELAY_LOAD_FAILED;
        }
        FreeLibrary(hDLL);
    }
    else
    {
        hrReturnVal = ERROR_DELAY_LOAD_FAILED;
    }
    return hrReturnVal;
}

int _tmain(int argc, _TCHAR* argv[])
{
    LoadAndCallSomeFunction(0, NULL);
	return 0;
}

