#include <windows.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>

extern "C"{
#include "..\..\Common\GetOptLib\optlist-0.3\optlist.h"
}

using namespace std;

bool ListFiles(wstring path, wstring mask, vector<wstring>& files) {
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    wstring spec;
    stack<wstring> directories;

    directories.push(path);
    files.clear();

    while (!directories.empty()) {
        path = directories.top();
        spec = path + L"\\" + mask;
        directories.pop();

        hFind = FindFirstFile(spec.c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE)  {
            return false;
        } 

        do {
            if (wcscmp(ffd.cFileName, L".") != 0 && 
                wcscmp(ffd.cFileName, L"..") != 0) {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    directories.push(path + L"\\" + ffd.cFileName);
                }
                else {
                    files.push_back(path + L"\\" + ffd.cFileName);
                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES) {
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
    }

    return true;
}

void usage()
{
    cout << "usage: " << endl;
}

int main(int argc, char* argv[])
{
    option_t *optList;    // Parse Command-Line Options
    option_t *thisOpt;    // Parse Command-Line Options

    /* get list of command line options and their arguments */
    optList = NULL;
    optList = GetOptList(argc, argv, "b:c:dg?");

    if (NULL == optList)
    {
        // no command-line options, so use defaults
        usage();
    }
    else
    {
        /* display results of parsing */
        while (optList != NULL)
        {
            thisOpt = optList;
            optList = optList->next;

            if ('?' == thisOpt->option)
            {
                usage();
                FreeOptList(thisOpt);   /* free the rest of the list */
                return EXIT_SUCCESS;

            } // ?help

            switch (thisOpt->option)
            {
                case 'b':   // set the beginning frame number
                if ((NULL == thisOpt->argument) || (1 > (int)strtol(thisOpt->argument, (char **)NULL, 10)))
                {
                    printf("Invalid or missing argument for -b option.  Specify beginning frame number.\n");
                    FreeOptList(thisOpt);   /* free the rest of the list */
                    usage();
                }
                else
                {
                    cout << "beginFrame = (int)strtol(thisOpt->argument, (char **)NULL, 10);" << endl;
                }
                break;

                case 'c':   // Coefficient filename
                if (NULL == thisOpt->argument)
                {
                    printf("Invalid or missing argument for -c option.  Specify Coefficient filename.\n");
                    FreeOptList(thisOpt);   /* free the rest of the list */
                    usage();
                }
                else
                {
                    cout << "calibrationFilename = thisOpt->argument" << endl;
                }
                break;

                case 'd':   // Debug
 					cout << "debugMode = true" << endl;
                break;
                
                case 'g':   // Run unattended?
                    cout << "unattended = true;" << endl;
                break;

                default:
                printf("Unknown Option\n");
                FreeOptList(thisOpt);   /* free the rest of the list */
                usage();
                break;

            } // switch option

            free(thisOpt);    /* done with this item, free it */

        } // while more options

    } // cmd-line options found

    return 0;







    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }
    return 0;

    vector<wstring> files;

    if (ListFiles(L"H:\\helitrak\\CPD", L"*", files)) {
        cout << "ok got all the files: " << endl;
        for (vector<wstring>::iterator it = files.begin(); 
             it != files.end(); 
             ++it) {
            wcout << it->c_str() << endl;
        }
    }
    return 0;
}
