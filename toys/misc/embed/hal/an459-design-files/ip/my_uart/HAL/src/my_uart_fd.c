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

#include "alt_types.h"
#include "sys/alt_dev.h"
#include "altera_avalon_uart.h"

extern int my_uart_read(my_uart_state* sp,
  char* buffer, int space, int flags);
extern int my_uart_write(my_uart_state* sp,
  const char* ptr, int count, int flags);
extern int my_uart_ioctl(my_uart_state* sp,
  int req, void* arg);

/* ----------------------------------------------------------------------- */
/* --------------------- WRAPPERS FOR ALT FD SUPPORT --------------------- */
/*
 *
 */

int 
my_uart_read_fd(alt_fd* fd, char* buffer, int space)
{
    my_uart_dev* dev = (my_uart_dev*) fd->dev; 

    return my_uart_read(&dev->state, buffer, space,
      fd->fd_flags);
}

int 
my_uart_write_fd(alt_fd* fd, const char* buffer, int space)
{
    my_uart_dev* dev = (my_uart_dev*) fd->dev; 

    return my_uart_write(&dev->state, buffer, space,
      fd->fd_flags);
}

#if !defined(ALT_USE_SMALL_DRIVERS) && !defined(MY_UART_SMALL)

/*
 * Fast driver
 */

/*
 * To reduce the code footprint of this driver, the ioctl() function is not
 * included by default. If you wish to use the ioctl features provided 
 * below, you can do so by adding the option : -DMY_UART_USE_IOCTL
 * to CPPFLAGS in the Makefile (or through the Eclipse IDE).
 */

#ifdef MY_UART_USE_IOCTL

int 
my_uart_ioctl_fd(alt_fd* fd, int req, void* arg)
{
    my_uart_dev* dev = (my_uart_dev*) fd->dev;

    return my_uart_ioctl(&dev->state, req, arg);
}

#endif /* MY_UART_USE_IOCTL */

#endif /* fast driver */
