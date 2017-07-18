#include <stdio.h>
#include <windows.h>
#include "windll.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch(message) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}  

__stdcall int WINAPI CreateWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //HINSTANCE hInstance = NULL;
    MSG msg          = {0};
    WNDCLASS wc      = {0}; 
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = (LPCSTR) L"minwindowsapp";

    hInstance = (HINSTANCE)GetModuleHandle(NULL);
    printf("hinstance: %x\n", hInstance);

    if( !RegisterClass(&wc) ) return 1;

    if( !CreateWindow(wc.lpszClassName,
                   (LPCSTR) L"Minimal Windows Application",
                   WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                   0,0,640,480,0,0,hInstance,NULL)) {
        return 2;
    }

    while( GetMessage( &msg, NULL, 0, 0 ) > 0 ) DispatchMessage( &msg );

    return 0;
    
}

__stdcall void hello(const char *s)
{
        printf("Hello %s\n", s);
}
int Double(int x)
{
        return 2 * x;
}
void CppFunc(void)
{
        puts("CppFunc");
}
void MyClass::func(void)
{
        puts("MyClass.func()");
}
