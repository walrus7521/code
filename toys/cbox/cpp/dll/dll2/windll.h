#ifndef WIN_DLL_H
#define WIN_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_WIN_DLL
#define WIN_DLL __declspec(dllexport)
#else
#define WIN_DLL __declspec(dllimport)
#endif

void __stdcall WIN_DLL hello(const char *s);
int __stdcall WIN_DLL CreateWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

int WIN_DLL Double(int x);

#ifdef __cplusplus
}
#endif

// NOTE: this function is not declared extern "C"
void WIN_DLL CppFunc(void);

// NOTE: this class must not be declared extern "C"
class WIN_DLL MyClass
{
public:
        MyClass() {};
        virtual ~MyClass() {};
        void func(void);
};

#endif  // WIN_DLL_H

