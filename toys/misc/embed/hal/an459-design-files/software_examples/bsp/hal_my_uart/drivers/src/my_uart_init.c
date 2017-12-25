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

#include <fcntl.h>

#include "sys/alt_dev.h"
#include "sys/alt_irq.h"
#include "sys/ioctl.h"
#include "sys/alt_errno.h"

#include "altera_avalon_uart.h"
#include "my_uart_regs.h"

#if !defined(ALT_USE_SMALL_DRIVERS) && !defined(MY_UART_SMALL)

/* ----------------------------------------------------------- */
/* ------------------------- FAST DRIVER --------------------- */
/* ----------------------------------------------------------- */

/*
 * my_uart_init() is called by the auto-generated function 
 * alt_sys_init() in order to initialize a particular instance of this device.
 * It is responsible for configuring the device and associated software 
 * constructs.
 */
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void my_uart_irq(void* context);
#else
static void my_uart_irq(void* context, alt_u32 id);
#endif

static void my_uart_rxirq(my_uart_state* sp,
  alt_u32 status);
static void my_uart_txirq(my_uart_state* sp,
  alt_u32 status);

void 
my_uart_init(my_uart_state* sp, alt_u32 irq)
{
  void* base = sp->base;
  int error;

  /* 
   * Initialise the read and write flags and the semaphores used to 
   * protect access to the circular buffers when running in a multi-threaded
   * environment.
   */

  error = ALT_FLAG_CREATE (&sp->events, 0)    || 
          ALT_SEM_CREATE (&sp->read_lock, 1)  ||
          ALT_SEM_CREATE (&sp->write_lock, 1);

  if (!error)
  {
    /* enable interrupts at the device */

    sp->ctrl = MY_UART_CONTROL_RTS_MSK  |
                MY_UART_CONTROL_RRDY_MSK |
                MY_UART_CONTROL_DCTS_MSK;

    IOWR_MY_UART_CONTROL(base, sp->ctrl); 
  
    /* register the interrupt handler */

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
    alt_ic_isr_register (0, irq, my_uart_irq, sp, 0x0);
#else
    alt_irq_register (irq, sp, my_uart_irq);
#endif
  }
}

/*
 * my_uart_irq() is the interrupt handler registered at configuration
 * time for processing UART interrupts. It vectors interrupt requests to
 * either my_uart_rxirq() (for incoming data), or
 * my_uart_txirq() (for outgoing data).
 */

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void my_uart_irq(void* context)
#else
static void my_uart_irq(void* context, alt_u32 id)
#endif
{
  alt_u32 status;

  my_uart_state* sp = (my_uart_state*) context;
  void* base               = sp->base;

  /*
   * Read the status register in order to determine the cause of the
   * interrupt.
   */

  status = IORD_MY_UART_STATUS(base);

  /* Clear any error flags set at the device */

  IOWR_MY_UART_STATUS(base, 0);

  /* process a read irq */
 
  if (status & MY_UART_STATUS_RRDY_MSK)
  {
    my_uart_rxirq(sp, status);
  }

  /* process a write irq */

  if (status & (MY_UART_STATUS_TRDY_MSK | 
                  MY_UART_STATUS_DCTS_MSK))
  {
    my_uart_txirq(sp, status);
  }
}

/*
 * my_uart_rxirq() is called by my_uart_irq() to process a
 * receive interrupt. It transfers the incoming character into the receive
 * circular buffer, and sets the apropriate flags to indicate that there is
 * dat ready to be processed.
 */

static void 
my_uart_rxirq(my_uart_state* sp, alt_u32 status)
{
  alt_u32 next;

  /*
   * In a multi-threaded environment, set the read event flag to indicate
   * that there is data ready. This is only done if the circular buffer was
   * previously empty.
   */

  if (sp->rx_end == sp->rx_start)
  {
    ALT_FLAG_POST (sp->events, MY_UART_READ_RDY, OS_FLAG_SET);
  }

  /* Determine which slot to use next in the circular buffer */

  next = (sp->rx_end + 1) & MY_UART_BUF_MSK;

  /* Transfer data from the device to the circular buffer */

  sp->rx_buf[sp->rx_end] = IORD_MY_UART_RXDATA(sp->base);

  /* If there was an error, discard the data */

  if (status & (MY_UART_STATUS_PE_MSK | 
                  MY_UART_STATUS_FE_MSK))
  {
    return;
  }

  sp->rx_end = next;

  next = (sp->rx_end + 1) & MY_UART_BUF_MSK;

  /*
   * If the cicular buffer was full, disable interrupts. Interrupts will be
   * re-enabled when data is removed from the buffer.
   */

  if (next == sp->rx_start)
  {
    sp->ctrl &= ~MY_UART_CONTROL_RRDY_MSK;
    IOWR_MY_UART_CONTROL(sp->base, sp->ctrl); 
  }   
}

/*
 * my_uart_txirq() is called by my_uart_irq() to process a
 * transmit interrupt. It transfers data from the transmit buffer to the
 * device, and sets the apropriate flags to indicate that there is
 * data ready to be processed.
 */

static void 
my_uart_txirq(my_uart_state* sp, alt_u32 status)
{
  /* Transfer data if there is some ready to be transfered */

  if (sp->tx_start != sp->tx_end)
  {
    /* 
     * If the device is using flow control (i.e. RTS/CTS), then the
     * transmitter is required to throttle if CTS is high.
     */

    if (!(sp->flags & MY_UART_FC) ||
      (status & MY_UART_STATUS_CTS_MSK))
    { 

      /*
       * In a multi-threaded environment, set the write event flag to indicate
       * that there is space in the circular buffer. This is only done if the
       * buffer was previously empty.
       */

      if (sp->tx_start == ((sp->tx_end + 1) & MY_UART_BUF_MSK))
      { 
        ALT_FLAG_POST (sp->events, 
                       MY_UART_WRITE_RDY,
                       OS_FLAG_SET);
      }

      /* Write the data to the device */

      IOWR_MY_UART_TXDATA(sp->base, sp->tx_buf[sp->tx_start]);

      sp->tx_start = (++sp->tx_start) & MY_UART_BUF_MSK;

      /*
       * In case the tranmit interrupt had previously been disabled by 
       * detecting a low value on CTS, it is reenabled here.
       */ 

      sp->ctrl |= MY_UART_CONTROL_TRDY_MSK;
    }
    else
    {
      /*
       * CTS is low and we are using flow control, so disable the transmit
       * interrupt while we wait for CTS to go high again. This will be 
       * detected using the DCTS interrupt.
       *
       * There is a race condition here. "status" may indicate that 
       * CTS is low, but it actually went high before DCTS was cleared on 
       * the last write to the status register. To avoid this resulting in
       * deadlock, it's necessary to re-check the status register here
       * before throttling.
       */
 
      status = IORD_MY_UART_STATUS(sp->base); 

      if (!(status & MY_UART_STATUS_CTS_MSK))
      {
        sp->ctrl &= ~MY_UART_CONTROL_TRDY_MSK;
      }
    }
  }

  /*
   * If the circular buffer is empty, disable the interrupt. This will be
   * re-enabled when new data is placed in the buffer.
   */

  if (sp->tx_start == sp->tx_end)
  {
    sp->ctrl &= ~(MY_UART_CONTROL_TRDY_MSK |
                    MY_UART_CONTROL_DCTS_MSK);
  }

  IOWR_MY_UART_CONTROL(sp->base, sp->ctrl);
}

#endif /* fast driver */