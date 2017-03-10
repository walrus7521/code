/*******************************************************************************
* Title                 :   MCP25625 HAL
* Filename              :   MCP25625_hal.c
* Author                :   MSV
* Origin Date           :   01/02/2016
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials       Description
*  01/02/16       1.0.0             MSV        Module Created.
*
*******************************************************************************/
/**
 * @file MCP25625_hal.c
 * @brief <h2> HAL layer </h2>
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "MCP25625_hal.h"
#include "mcpdefs.h"
#include <Windows.h>
#include <stdio.h>

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
static void             ( *write_spi_p )    ( unsigned int data_out );
static unsigned int     ( *read_spi_p )     ( unsigned int buffer );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )
static void             ( *write_spi_p )    ( unsigned char data_out );
static unsigned char    ( *read_spi_p )     ( unsigned char dummy );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static void             ( *write_spi_p )    ( unsigned long data_out );
static unsigned long    ( *read_spi_p )     ( unsigned long buffer );

#endif

#if defined( __MIKROC_PRO_FOR_ARM__ )     || \
    defined( __MIKROC_PRO_FOR_AVR__ )     || \
    defined( __MIKROC_PRO_FOR_PIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )   || \
    defined( __MIKROC_PRO_FOR_8051__ )    || \
    defined( __MIKROC_PRO_FOR_FT90x__ )
extern sfr sbit MCP25625_CS;
extern sfr sbit MCP25625_RST;
extern sfr sbit MCP25625_STB;
extern sfr sbit MCP25625_TX0;
extern sfr sbit MCP25625_TX1;
extern sfr sbit MCP25625_RX0;
extern sfr sbit MCP25625_RX1;
#endif
/******************************************************************************
* Function Prototypes
*******************************************************************************/

HANDLE hDev;
unsigned int baudRate;
unsigned int txferSize;
extern void mcpShowError(int err);

/******************************************************************************
* Function Definitions
*******************************************************************************/
void MCP25625_hal_cs( int state )
{
    // this is empty because CS1 is set by SPI engine
}

void MCP25625_hal_rst( int state )
{
    // nothing to do here "yet"
}

void MCP25625_hal_stb( int state )
{
    // standby pin not used
}

void MCP25625_hal_tx0( int state )
{
    // tx0 pin not used
}

void MCP25625_hal_tx1( int state )
{
    // tx1 pin not used
}

int MCP25625_hal_rx0()
{
    // rx0 pin not used
    return 0;
}

int MCP25625_hal_rx1()
{
    // tx1 pin not used
    return 0;
}

/* the HAL is the MCP2210 interface */
void MCP2211_hal_init()
{
    unsigned short vid;
    unsigned short pid;
    int dev_count;
    wchar_t mfgr[100];
    int err;

    vid = 0x04d8;
    pid = 0x00de;
    dev_count = mcpGetConnectedDevCount(vid, pid);

    hDev = mcpOpenByIndex(vid, pid, 0, NULL, 0);

    err = mcpGetManufacturerString(hDev, mfgr);
    if (MCP_SUCCESS(err))
    {
        printf("detected %d device(s): %ws\n", dev_count, mfgr);
    }

    /* MCP2210 GPIO configuration */
    unsigned char cfgSelector = MCP2210_VM_CONFIG;
    unsigned int gpioOutput;
    unsigned int gpioDir;
    unsigned char rmtWkupEn;
    unsigned char intPinMd;
    unsigned char spiBusRelEn;
    unsigned char gpioPinDes[MCP2210_GPIO_NR];

    err = mcpGetGpioConfig(hDev, cfgSelector, gpioPinDes,
        &gpioOutput, &gpioDir, &rmtWkupEn,
        &intPinMd, &spiBusRelEn);

    for (int i = 0; i < MCP2210_GPIO_NR; i++)
    {
        gpioPinDes[i] = MCP2210_PIN_DES_CS;
    }

    gpioDir = MCP2210_GPIO_DIRECTION_OUTPUT;
    gpioOutput = 1;

    err = mcpSetGpioConfig(hDev, cfgSelector, gpioPinDes,
        gpioOutput, gpioDir, rmtWkupEn,
        intPinMd, spiBusRelEn);

    /* MCP2210 SPI configuration */
    unsigned int idleCsVal; 
    unsigned int activeCsVal;
    unsigned int csToDataDly;
    unsigned int dataToCsDly;
    unsigned int dataToDataDly;
    unsigned char spiMd;

    err = mcpGetSpiConfig(hDev, cfgSelector, &baudRate, 
        &idleCsVal, &activeCsVal, &csToDataDly, 
        &dataToCsDly, &dataToDataDly, &txferSize, 
        &spiMd);

    if (MCP_SUCCESS(err))
    {
        printf("fetch\n");
        printf("   baud rate: %d\n", baudRate);
        printf("   idle:      %x\n", idleCsVal);
        printf("   active:    %x\n", activeCsVal);
        printf("   cs2data:   %x\n", csToDataDly);
        printf("   data2cs:   %x\n", dataToCsDly);
        printf("   d2d:       %x\n", dataToDataDly);
        printf("   tx sz:     %d\n", txferSize);
        printf("   mode:      %d\n", spiMd);
        printf("\n");
    }

    activeCsVal = 0xfffd;
    idleCsVal = 0xffff;
    baudRate = 1000000;
    //baudRate = 50000l;
    txferSize = 4;

    if (MCP_SUCCESS(err))
    {
        printf("tweak\n");
        printf("   baud rate: %d\n", baudRate);
        printf("   idle:      %x\n", idleCsVal);
        printf("   active:    %x\n", activeCsVal);
        printf("   cs2data:   %x\n", csToDataDly);
        printf("   data2cs:   %x\n", dataToCsDly);
        printf("   d2d:       %x\n", dataToDataDly);
        printf("   tx sz:     %d\n", txferSize);
        printf("   mode:      %d\n", spiMd);
        printf("\n");
    }

    err = mcpSetSpiConfig(hDev, cfgSelector, &baudRate, 
        &idleCsVal, &activeCsVal, &csToDataDly, 
        &dataToCsDly, &dataToDataDly, &txferSize, 
        &spiMd);

    if (MCP_SUCCESS(err))
    {
        printf("verify\n");
        printf("   baud rate: %d\n", baudRate);
        printf("   idle:      %x\n", idleCsVal);
        printf("   active:    %x\n", activeCsVal);
        printf("   cs2data:   %x\n", csToDataDly);
        printf("   data2cs:   %x\n", dataToCsDly);
        printf("   d2d:       %x\n", dataToDataDly);
        printf("   tx sz:     %d\n", txferSize);
        printf("   mode:      %d\n", spiMd);
        printf("\n");
    }

    //mcpClose(hDev);

}

void MCP25625_hal_cmd( uint8_t cmd )
{
    int err;
    unsigned char txData[16];
    unsigned char rxData[16];
    unsigned int xfrSize = 1;
    unsigned int csMask = 0x02; // 0x02 => CS1

    txData[0] = (unsigned char) cmd;
    err = mcpxferSpiData(hDev, txData, rxData, &baudRate, &xfrSize, csMask);
    if (!MCP_SUCCESS(err))
    {
        mcpShowError(err);
    }
}

void MCP25625_hal_write( uint8_t *buffer,
                         uint16_t count )
{
    int err;
    int i;
    int txIndex;
    int len;
    uint8_t txData[16];
    uint8_t rxData[16];
    unsigned int csMask = 0x02; // 0x02 => CS1

    i = 0;
    txIndex = 0;
    while (count > 0)
    {
        len = MIN(count, txferSize);
        for (i = 0; i < len; i++)
        {
            txData[i] = (unsigned char) buffer[txIndex++];
        }
        err = mcpxferSpiData(hDev, txData, rxData, &baudRate, &len, csMask);
        if (!MCP_SUCCESS(err))
        {
            mcpShowError(err);
            return;
        }
        count -= len;
    }

}

void MCP25625_hal_read( uint8_t *buffer,
                        uint16_t count )
{
    int err;
    int i;
    int rxIndex;
    int len;
    uint8_t txData[16];
    uint8_t rxData[16];
    unsigned int csMask = 0x02; // 0x02 => CS1

    i = 0;
    rxIndex = 0;
    while (count > 0)
    {
        len = MIN(count, txferSize);
        err = mcpxferSpiData(hDev, txData, rxData, &baudRate, &len, csMask);
        if (!MCP_SUCCESS(err))
        {
            mcpShowError(err);
            return;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                buffer[rxIndex++] = rxData[i];
            }
        }
        count -= len;
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/
