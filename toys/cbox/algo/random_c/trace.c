#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

/*  ========================================================================
    \fn strcat
    \brief private version of string concatenation which appends 2nd string
        to the end of the first.

    \Parameter[in] string1 char - destination string to be updated.
    \Parameter[in] string2 const char - source string for append.

    \return char * - text string which has been appended.

    \nonflight
    ======================================================================== */
char *mystrcat(char *string1, char *string2)
{
   char       *s1 = string1;
   const char *s2 = string2;

   while (*s1) s1++; /* find end of string   */
   do
   {
       *s1++ = *s2++;
   }
   while (*s2 != 0); /* append second string */
   return string1;
   
} // strcat

/** ===================================================================================================================
    Function Description
        Converts a signed integer to a string, based on the radix.

    \Parameter[in] value, signed integer.
    \Parameter[out] sp, char buffer to contain the result of the conversion.
    \Parameter[in] radix, base of the integer (2, 10, 16)
    
    \return        length of the conversion string, sp, not including the terminator.
    
    \nonflight
====================================================================================================================*/
int myitoa(int value, char *sp, int radix)
{
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign) 
    {
        v = -value;
    } 
    else 
    {
        v = (unsigned) value;
    }

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
        {
            *tp++ = i+'0';
        }
        else
        {
            *tp++ = i + 'a' - 10;
        }
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
    {
        *sp++ = *--tp;
    }
    sp = '\0';

    return len;
}

/** ===================================================================================================================
    Function Description
        Converts a float to a string.

    \Parameter[in] f, single precision floating number.
    \Parameter[in] buf, char buffer to contain the result of the conversion.
    \Parameter[out] none

    \return        void
    
    \nonflight
====================================================================================================================*/
void myftoa(float f, char *buf)
{
    int pos=0, ix, dp, num;
    if ( f < 0.0f)
    {
        buf[pos++] = '-';
        f = -f;
    }
    dp = 0;
    while ( f >= 10.0f) 
    {
        f=f/10.0f;
        dp++;
    } 
    for (ix = 1; ix < 8; ix++)
    {
        num = f;
        f=f-num;
        if (num>9)
            buf[pos++]='#';
        else
            buf[pos++]='0'+num;
        if (dp==0) buf[pos++]='.';
        f=f*10.0f;
        dp--;
    }
}

#define PHASER_STOP(msg) \
{ \
    if (frame/10 % 100 == 0) { \
    	char buf[256] = {0}; \
        char tmp[32] = {0}; \
        mystrcat(buf, "\r\n");  \
        strncpy(buf, msg, strlen(msg)); \
        myftoa(profiling_time_elapsed, tmp);        \
        mystrcat((char *) buf, (char *) ": ");      \
        mystrcat(buf, tmp);      \
        mystrcat(buf, "\r\n\0");  \
        puts(buf); \
    } \
}

#define TRACER_0(msg) \
{ \
    	char buf[256] = {0}; \
        char tmp[32] = {0}; \
        mystrcat(buf, "\r\n");  \
        strncpy(buf, msg, strlen(msg)); \
        myftoa(profiling_time_elapsed, tmp);        \
        mystrcat((char *) buf, (char *) ": ");      \
        mystrcat(buf, tmp);      \
        mystrcat(buf, "\r\n\0");  \
        puts(buf); \
}

#define PRINTF_BUFFER_SIZE (1024)
static char printf_buffer[PRINTF_BUFFER_SIZE] = {0};

void Debug_Support_Printf(char * format, ...)
{
   // pointer to the variadic parameters
    va_list argptr = {0};

    // get the pointer to the variadic parameters
    va_start(argptr, format);

    // use vsprintf() to generated a formated string based on the format string and variadic parameters
    // Note - there is no protection against printf_buffer[] from being overflowed
    vsprintf(printf_buffer, format, argptr);

    // commit the string to STDIO
    // no checks are made to ensure there is room in the stream's buffer to hold the string
    // this is safe as the stream guards against over-flows, but data may be lost
    puts(printf_buffer);

} // Debug_Support_Printf()

struct {
    char type;
    union {
        float f;
        int   i;
    } u;
} pair [4] = 
{
    {0,0},
    {0,0},
    {0,0},
    {0,0},
};
char types[7] = {'d','d','d','d','d','d','d'};

int extract(char *fmt)
{
    int count = 0;
    char *ptr = fmt;
    while((ptr = strchr(ptr, '%')) != NULL) {
        types[count] = ptr[0];
        printf("type: %c\n", ptr[1]);
        count++;
        ptr++;
    }
    return count;
}

void Trace_Support_1(char *fmt, float val)
{
    char *pch, type, *valu;
    int dec;
    float flt;
    strtok(fmt, "%");
    pch = strtok(NULL, "%");
    type = pch[0];
    //strtok(pch, ",");
    //valu = strtok(NULL, ",");
    //printf("%s -> %c => %s\n", pch, type, val);
    switch (type) {
        case 's': 
            printf("str: %s\n", val); 
            break;
        case 'd': 
            dec = (int) floor(val);
            printf("dec: %d\n", dec); 
            break;
        case 'f': 
            printf("flt: %f\n", val); 
            break;
    }
    return;
    while (pch != NULL) {
        printf ("%s\n", pch);
        pch = strtok(NULL, " %");
    }
}

#define TRACE_0(_format_str)                               Debug_Support_Printf(_format_str)
#define TRACE_1(_format_str, _x1)                          Debug_Support_Printf(_format_str, _x1)
#define TRACE_2(_format_str, _x1, _x2)                     Debug_Support_Printf(_format_str, _x1, _x2)
#define TRACE_3(_format_str, _x1, _x2, _x3)                Debug_Support_Printf(_format_str, _x1, _x2, _x3)
#define TRACE_4(_format_str, _x1, _x2, _x3, _x4)           Debug_Support_Printf(_format_str, _x1, _x2, _x3, _x4)
#define TRACE_5(_format_str, _x1, _x2, _x3, _x4, _x5)      Debug_Support_Printf(_format_str, _x1, _x2, _x3, _x4, _x5)
#define TRACE_6(_format_str, _x1, _x2, _x3, _x4, _x5, _x6) Debug_Support_Printf(_format_str, _x1, _x2, _x3, _x4, _x5, _x6)
#define TRACE_7(_format_str, _x1, _x2, _x3, _x4, _x5, _x6, _x7) Debug_Support_Printf(_format_str, _x1, _x2, _x3, _x4, _x5, _x6, _x7)
#define TRACE_8(_format_str, _x1, _x2, _x3, _x4, _x5, _x6, _x7, _x8) Debug_Support_Printf(_format_str, _x1, _x2, _x3, _x4, _x5, _x6, _x7, _x8)



// Stream_IO_Write(strlen(buf), buf, STREAM_STDIO);

void serial_num()
{
    char buf[256] = "\r\n\r\nProject Test - ";
    puts(buf);
    strcpy(buf,"\r\n");
    puts(buf);
    strcpy(buf, " " __DATE__ " " __TIME__  "- CRC: ");
    puts(buf);
    strcpy(buf, "\r\n");
    puts(buf);
}

int main()
{
#if 0
    int frame = 1000;
    float profiling_time_elapsed;
    profiling_time_elapsed = 42.0f;
    PHASER_STOP("Pre");
    TRACE_0("yo sup dawg");
    serial_num();
    char s[] = "sup %s, dawg.\n";
    char d[] = "sup %d, hook.\n";
#endif

    char f1[] = "sup %f, homi.\n";
    char f2[] = "sup %f, %d homi.\n";
    char f3[] = "sup %f, %d %f homi.\n";
    char f4[] = "sup %f, %d %f %d homi.\n";
    char f5[] = "sup %f, %d %f %d %f homi.\n";
    char f6[] = "sup %f, %d %f %d %f %d homi.\n";
    char f7[] = "sup %f, %d %f %d %f %d %f homi.\n";
    int num = extract(f1);
    printf("extracted %d from %s\n", num, f1);
    num = extract(f2);
    printf("extracted %d from %s\n", num, f2);
    num = extract(f3);
    printf("extracted %d from %s\n", num, f3);
    num = extract(f4);
    printf("extracted %d from %s\n", num, f4);
    num = extract(f5);
    printf("extracted %d from %s\n", num, f5);
    num = extract(f6);
    printf("extracted %d from %s\n", num, f6);
    num = extract(f7);
    printf("extracted %d from %s\n", num, f7);

#if 0
    char v[] = "homi";
    //int i = 42;
    float x = 3.14;
    float i = 42.0;
    //Trace_Support_1(s, (float) v);
    Trace_Support_1(f, x);
    Trace_Support_1(d, i);
#endif
}


