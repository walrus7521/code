// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <stdio.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        printf("proc attach\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("thread attach\n");
        break;
    case DLL_THREAD_DETACH:
        printf("thread detach\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("proc detach\n");
        break;
    }
    return TRUE;
}

