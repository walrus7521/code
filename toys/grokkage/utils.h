#ifndef _UTILS_H_
#define _UTILS_H_

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exchg(A, B) { int t = A; A = B; B = t; } 

#define GE(x, y) ((x) >= (y))
#define LE(x, y) ((x) <= (y))
#define LT(x, y) ((x) < (y))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define exchg2(X, Y) { \
    (X) = (X) ^ (Y);   \
    (Y) = (Y) ^ (X);   \
    (X) = (X) ^ (Y); }

#define cmpexchg(A, B) if (less(B, A)) exchg(A, B)

#if defined(_WIN64) || defined(_WIN32)
int getline(char **lineptr, size_t *n, FILE *stream)
{
    return 0;

    static char line[256];
    char *ptr;
    unsigned int len;
    if (lineptr == NULL || n == NULL) {
        //errno = -1; //EINVAL;
        return -1;
    }
    if (ferror (stream)) return -1;
    if (feof(stream)) return -1;
    fgets(line,256,stream);
    ptr = strchr(line,'\n');   
    if (ptr) *ptr = '\0';
    len = strlen(line);
    if ((len+1) < 256) {
        ptr = realloc(*lineptr, 256);
        if (ptr == NULL) return(-1);
        *lineptr = ptr;
        *n = 256;
    }
    strcpy(*lineptr,line); 
    return(len);
}
#elif __APPLE__
    #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
    #elif TARGET_OS_IPHONE
    #else
        #define TARGET_OS_OSX 1
    #endif
#elif __linux
#elif __unix // all unices not caught above
#elif __posix
#endif



#endif // _UTILS_H_
