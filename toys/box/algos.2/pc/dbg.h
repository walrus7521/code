#ifndef _DBG_H_
#define _DBG_H_

#include <stdio.h>
#include <stdarg.h>

//#define dprintf printf
#define dprintf(...)

unsigned short PRIO_HIGH    = 0x0001;
unsigned short PRIO_NORMAL  = 0x0002;
unsigned short PRIO_LOW     = 0x0004;
int PRIO_LOG = 0; //0xffff;
int dbg_log(int priority, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    if (priority & PRIO_LOG)
        vprintf(format, args);
    va_end(args);
    return 0;
}

void hexdump(unsigned char *buff, int length)
{
    char offsetbuf[10];
    int laststart = 0, i, k, j;
    printf("hexdump: %p - %d\n", buff, length);
    for ( i = 0 ; i < length ; i++ ) {
        if ( i % 16 == 0  ) {
            sprintf( (char *)offsetbuf, "%03x", i );
            printf( "%4s:", offsetbuf );
        }
        if ( i % 4 == 0 ) {
            printf( " " );
        }
        printf( "%02x ", buff[i] );
        if ( i % 16 == 15 || i == length-1 ) {
            if ( i == length-1 ) {
                for ( k = i % 16 ; k < 15 ; k++ ) {
                     printf( "   " );
                     if ( k % 4 == 3 && k % 16 != 0 ) {
                         printf( " " );
                     }
                }
            }
            printf( "|" );
            for ( j = laststart ; j <= i ; j++ ) {
                if ( j % 4 == 0 ) {
                    printf( " " );
                }
                if ( buff[j] > 31 && buff[j] < 127 ) {
                    printf( "%c", buff[j] );
                } else {
                    printf( "." );
                }
            }
            if ( i == length-1 ) {
                printf( "\n" );
                break;
            }
            printf( "\n" );
            laststart += 16;
        }
    }
}

#endif
