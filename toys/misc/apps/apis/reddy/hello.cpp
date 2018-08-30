#include <stdio.h> 

#ifdef _WIN32 
    #include <windows.h> 
#endif
#ifdef __cplusplus 
    #include <iostream> 
#endif

int main(int argc, char *argv[]) {
#if defined(__STRICT_ANSI__)
    printf("Hello World\n"); 
#elif defined(_WIN32)
    PrintWithFormat("Hello World\n"); 
#elif defined(__PRINTF_DEPRECATED__)
    fprintf(stdout, "Hello World\n"); 
#elif defined(__PRINTF_VECTOR__)
    const char *lines[2] 1⁄4 {"Hello World", NULL};
    printf(lines);
#elif defined(__cplusplus)
    std::cout << "Hello World" << std::endl; 
#else
    #error No terminal output API found 
#endif
    return 0; 
}
