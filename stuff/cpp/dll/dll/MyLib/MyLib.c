// MyLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MyLib.h"


// This is an example of an exported variable
MYLIB_API int nMyLib=0;



// This is an example of an exported function.
MYLIB_API char *get_stuff(int id)
{
    return "stuff";
}

// This is the constructor of a class that has been exported.
// see MyLib.h for the class definition
//CMyLib::CMyLib()
//{
//	return;
//}
