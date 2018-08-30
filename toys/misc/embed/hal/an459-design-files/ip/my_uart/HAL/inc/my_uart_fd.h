/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2008 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

#ifndef __MY_UART_FD_H__
#define __MY_UART_FD_H__

#include "sys/alt_dev.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
 * Externally referenced routines
 */
extern int my_uart_read_fd (alt_fd* fd, char* ptr, int len);
extern int my_uart_write_fd (alt_fd* fd, const char* ptr,
  int len);

/*
 * Device structure definition. This is needed by alt_sys_init in order to 
 * reserve memory for the device instance.
 */
typedef struct my_uart_dev_s
{
  alt_dev        dev;
  my_uart_state state;
} my_uart_dev;

#if defined(ALT_USE_SMALL_DRIVERS) || defined(MY_UART_SMALL)

/*
 * Macros used by alt_sys_init when the ALT file descriptor facility is used.
 */

#define MY_UART_DEV_INSTANCE(name, d)    \
  static my_uart_dev d =                 \
    {                                               \
      {                                             \
        ALT_LLIST_ENTRY,                            \
        name##_NAME,                                \
        NULL, /* open */                            \
        NULL, /* close */                           \
        my_uart_read_fd,                 \
        my_uart_write_fd,                \
        NULL, /* lseek */                           \
        NULL, /* fstat */                           \
        NULL, /* ioctl */                           \
      },                                            \
      {                                             \
        name##_BASE,                                \
      }                                             \
    }

#define MY_UART_DEV_INIT(name, d) alt_dev_reg (&d.dev)

#else /* use fast version of the driver */

extern int my_uart_ioctl_fd (alt_fd* fd, int req, void* arg);

#ifdef MY_UART_USE_IOCTL
#define MY_UART_IOCTL_FD my_uart_ioctl_fd
#else
#define MY_UART_IOCTL_FD NULL
#endif

#define MY_UART_DEV_INSTANCE(name, d)       \
  static my_uart_dev d =                    \
   {                                                   \
     {                                                 \
       ALT_LLIST_ENTRY,                                \
       name##_NAME,                                    \
       NULL, /* open */                                \
       NULL, /* close */                               \
       my_uart_read_fd,                     \
       my_uart_write_fd,                    \
       NULL, /* lseek */                               \
       NULL, /* fstat */                               \
       MY_UART_IOCTL_FD,                    \
     },                                                \
     {                                                 \
       (void*) name##_BASE,                            \
       0,                                              \
       0,                                              \
       0,                                              \
       0,                                              \
       0,                                              \
       MY_UART_TERMIOS(name##_STOP_BITS,    \
                               (name##_PARITY == 'N'), \
                               (name##_PARITY == 'O'), \
                               name##_DATA_BITS,       \
                               name##_USE_CTS_RTS,     \
                               name##_BAUD)            \
       MY_UART_FREQ(name)                   \
       (name##_FIXED_BAUD ? MY_UART_FB : 0) |  \
         (name##_USE_CTS_RTS ? MY_UART_FC : 0) \
     }                                                 \
   }

#define MY_UART_DEV_INIT(name, d)           \
  {                                                    \
    MY_UART_STATE_INIT(name, d.state);      \
                                                       \
    /* make the device available to the system */      \
    alt_dev_reg(&d.dev);                               \
  }

#endif /* fast driver */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MY_UART_FD_H__ */
