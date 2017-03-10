#include <stdio.h>
#include "mcpdefs.h"
#include "mcp25625.h"

extern "C" {
    extern unsigned int baudRate;
    extern HANDLE hDev;
    void mcpShowError(int err);

}

extern void hexdump(FILE *file, const unsigned char *buffer, int length);

typedef int (__stdcall *fnMcp2210_GetLibraryVersion)(wchar_t *version);

/* API for getting access to the USB device */
typedef int   (__stdcall *fnMcp2210_GetLastError)();
typedef int   (__stdcall *fnMcp2210_GetConnectedDevCount)(unsigned short vid, unsigned short pid);
typedef void* (__stdcall *fnMcp2210_OpenByIndex)(unsigned short vid, unsigned short pid, unsigned int index, wchar_t *devPath, unsigned long *devPathsize);
typedef void* (__stdcall *fnMcp2210_OpenBySN)(unsigned short vid, unsigned short pid, wchar_t *serialNo, wchar_t *devPath, unsigned long *devPathsize);
typedef int   (__stdcall *fnMcp2210_Close)(void *handle);
typedef int   (__stdcall *fnMcp2210_Reset)(void *handle);

/* USB settings */
typedef int (__stdcall *fnMcp2210_GetUsbKeyParams)(void *handle, unsigned short *pvid, unsigned short *ppid,
                                                         unsigned char *ppwrSrc, unsigned char *prmtWkup, unsigned short *pcurrentLd);
typedef int (__stdcall *fnMcp2210_SetUsbKeyParams)(void *handle, unsigned short vid, unsigned short pid,
                                                         unsigned char pwrSrc, unsigned char rmtWkup, unsigned short currentLd);
typedef int (__stdcall *fnMcp2210_GetManufacturerString)(void *handle, wchar_t *manufacturerStr);
typedef int (__stdcall *fnMcp2210_SetManufacturerString)(void *handle, wchar_t *manufacturerStr);
typedef int (__stdcall *fnMcp2210_GetProductString)(void *handle, wchar_t *productStr);
typedef int (__stdcall *fnMcp2210_SetProductString)(void *handle, wchar_t *productStr);
typedef int (__stdcall *fnMcp2210_GetSerialNumber)(void *handle, wchar_t *serialStr);

/* API to access GPIO settings and values */
typedef int (__stdcall *fnMcp2210_GetGpioPinDir)(void *handle, unsigned int *pgpioDir);
typedef int (__stdcall *fnMcp2210_SetGpioPinDir)(void *handle, unsigned int gpioSetDir);
typedef int (__stdcall *fnMcp2210_GetGpioPinVal)(void *handle, unsigned int *pgpioPinVal);
typedef int (__stdcall *fnMcp2210_SetGpioPinVal)(void *handle, unsigned int gpioSetVal, unsigned int *pgpioPinVal);
typedef int (__stdcall *fnMcp2210_GetGpioConfig)(void *handle, unsigned char cfgSelector, unsigned char *pGpioPinDes, unsigned int *pdfltGpioOutput,
                                                       unsigned int *pdfltGpioDir, unsigned char *prmtWkupEn, unsigned char *pintPinMd, unsigned char *pspiBusRelEn);
typedef int (__stdcall *fnMcp2210_SetGpioConfig)(void *handle, unsigned char cfgSelector, unsigned char *pGpioPinDes, unsigned int dfltGpioOutput,
                                                       unsigned int dfltGpioDir, unsigned char rmtWkupEn, unsigned char intPinMd, unsigned char spiBusRelEn);
typedef int (__stdcall *fnMcp2210_GetInterruptCount)(void *handle, unsigned int *pintCnt, unsigned char reset);

/* API to control SPI transfer */
typedef int (__stdcall *fnMcp2210_GetSpiConfig)(void *handle, unsigned char cfgSelector, unsigned int *pbaudRate, unsigned int *pidleCsVal,
                                                      unsigned int *pactiveCsVal, unsigned int *pCsToDataDly, unsigned int *pdataToCsDly,
                                                      unsigned int *pdataToDataDly, unsigned int *ptxferSize, unsigned char *pspiMd);
typedef int (__stdcall *fnMcp2210_SetSpiConfig)(void *handle, unsigned char cfgSelector, unsigned int *pbaudRate, unsigned int *pidleCsVal,
                                                      unsigned int *pactiveCsVal, unsigned int *pCsToDataDly, unsigned int *pdataToCsDly,
                                                      unsigned int *pdataToDataDly, unsigned int *ptxferSize, unsigned char *pspiMd);

typedef int (__stdcall *fnMcp2210_xferSpiData)(void *handle, unsigned char *pdataTx, unsigned char *pdataRx,
                                                     unsigned int *pbaudRate, unsigned int *ptxferSize, unsigned int csmask);

typedef int (__stdcall *fnMcp2210_xferSpiDataEx)(void *handle, unsigned char *pdataTx, unsigned char *pdataRx,
                                                       unsigned int *pbaudRate, unsigned int *ptxferSize, unsigned int csmask,
                                                       unsigned int *pidleCsVal, unsigned int *pactiveCsVal, unsigned int *pCsToDataDly,
                                                       unsigned int *pdataToCsDly, unsigned int *pdataToDataDly, unsigned char *pspiMd);

typedef int (__stdcall *fnMcp2210_CancelSpiTxfer)(void *handle, unsigned char *pspiExtReqStat, unsigned char *pspiOwner);
typedef int (__stdcall *fnMcp2210_RequestSpiBusRel)(void *handle, unsigned char ackPinVal);
typedef int (__stdcall *fnMcp2210_GetSpiStatus)(void *handle, unsigned char *pspiExtReqStat, unsigned char *pspiOwner, unsigned char *pspiTxferStat);

/* EEPROM read/write API */
typedef int (__stdcall *fnMcp2210_ReadEEProm)(void *handle, unsigned char address, unsigned char *pcontent);
typedef int (__stdcall *fnMcp2210_WriteEEProm)(void *handle, unsigned char address, unsigned char content);

/* Access control API */
typedef int (__stdcall *fnMcp2210_GetAccessCtrlStatus)(void *handle, unsigned char *pAccessCtrl, unsigned char *pPasswdAttemptCnt, unsigned char *pPasswdAccepted);
typedef int (__stdcall *fnMcp2210_EnterPassword)(void *handle, char *passwd);
typedef int (__stdcall *fnMcp2210_SetAccessControl)(void *handle, unsigned char accessConfig, char *currentPasswd, char *newPasswd);
typedef int (__stdcall *fnMcp2210_SetPermanentLock)(void *handle);

fnMcp2210_GetLibraryVersion         pmcpGetLibraryVersion;
fnMcp2210_GetLastError              pmcpGetLastError;
fnMcp2210_GetConnectedDevCount      pmcpGetConnectedDevCount;
fnMcp2210_OpenByIndex               pmcpOpenByIndex;
fnMcp2210_OpenBySN                  pmcpOpenBySN;
fnMcp2210_Close                     pmcpClose;
fnMcp2210_Reset                     pmcpReset;
fnMcp2210_GetUsbKeyParams           pmcpGetUsbKeyParams;
fnMcp2210_SetUsbKeyParams           pmcpSetUsbKeyParams;
fnMcp2210_GetManufacturerString     pmcpGetManufacturerString;
fnMcp2210_SetManufacturerString     pmcpSetManufacturerString;
fnMcp2210_GetProductString          pmcpGetProductString;
fnMcp2210_SetProductString          pmcpSetProductString;
fnMcp2210_GetSerialNumber           pmcpGetSerialNumber;
fnMcp2210_GetGpioPinDir             pmcpGetGpioPinDir;
fnMcp2210_SetGpioPinDir             pmcpSetGpioPinDir;
fnMcp2210_GetGpioPinVal             pmcpGetGpioPinVal;
fnMcp2210_SetGpioPinVal             pmcpSetGpioPinVal;
fnMcp2210_GetGpioConfig             pmcpGetGpioConfig;
fnMcp2210_SetGpioConfig             pmcpSetGpioConfig;
fnMcp2210_GetInterruptCount         pmcpGetInterruptCount;
fnMcp2210_GetSpiConfig              pmcpGetSpiConfig;
fnMcp2210_SetSpiConfig              pmcpSetSpiConfig;
fnMcp2210_xferSpiData               pmcpxferSpiData;
fnMcp2210_xferSpiDataEx             pmcpxferSpiDataEx;
fnMcp2210_CancelSpiTxfer            pmcpCancelSpiTxfer;
fnMcp2210_RequestSpiBusRel          pmcpRequestSpiBusRel;
fnMcp2210_GetSpiStatus              pmcpGetSpiStatus;
fnMcp2210_ReadEEProm                pmcpReadEEProm;
fnMcp2210_WriteEEProm               pmcpWriteEEProm;
fnMcp2210_GetAccessCtrlStatus       pmcpGetAccessCtrlStatus;
fnMcp2210_EnterPassword             pmcpEnterPassword;
fnMcp2210_SetAccessControl          pmcpSetAccessControl;
fnMcp2210_SetPermanentLock          pmcpSetPermanentLock;

HINSTANCE m_hMcpDll;

int mcp2210_DLL_Init()
{
    m_hMcpDll = LoadLibrary("mcp2210_dll_um_x86");


    if (NULL == m_hMcpDll)
    {
        printf("Error: Unable to find the DLL PCANBasic.dll!\n");
        return -1;
    }

    pmcpGetLibraryVersion       = (fnMcp2210_GetLibraryVersion) GetProcAddress(m_hMcpDll, "Mcp2210_GetLibraryVersion");
    pmcpGetLastError            = (fnMcp2210_GetLastError) GetProcAddress(m_hMcpDll, "Mcp2210_GetLastError");
    pmcpGetConnectedDevCount    = (fnMcp2210_GetConnectedDevCount) GetProcAddress(m_hMcpDll, "Mcp2210_GetConnectedDevCount");
    pmcpOpenByIndex             = (fnMcp2210_OpenByIndex) GetProcAddress(m_hMcpDll, "Mcp2210_OpenByIndex");
    pmcpOpenBySN                = (fnMcp2210_OpenBySN) GetProcAddress(m_hMcpDll, "Mcp2210_OpenBySN");
    pmcpClose                   = (fnMcp2210_Close) GetProcAddress(m_hMcpDll, "Mcp2210_Close");
    pmcpReset                   = (fnMcp2210_Reset) GetProcAddress(m_hMcpDll, "Mcp2210_Reset");
    pmcpGetUsbKeyParams         = (fnMcp2210_GetUsbKeyParams) GetProcAddress(m_hMcpDll, "Mcp2210_GetUsbKeyParams");
    pmcpSetUsbKeyParams         = (fnMcp2210_SetUsbKeyParams) GetProcAddress(m_hMcpDll, "Mcp2210_SetUsbKeyParams");
    pmcpGetManufacturerString   = (fnMcp2210_GetManufacturerString) GetProcAddress(m_hMcpDll, "Mcp2210_GetManufacturerString");
    pmcpSetManufacturerString   = (fnMcp2210_SetManufacturerString) GetProcAddress(m_hMcpDll, "Mcp2210_SetManufacturerString");
    pmcpGetProductString        = (fnMcp2210_GetProductString) GetProcAddress(m_hMcpDll, "Mcp2210_GetProductString");
    pmcpSetProductString        = (fnMcp2210_SetProductString) GetProcAddress(m_hMcpDll, "Mcp2210_SetProductString");
    pmcpGetSerialNumber         = (fnMcp2210_GetSerialNumber) GetProcAddress(m_hMcpDll, "Mcp2210_GetSerialNumber");
    pmcpGetGpioPinDir           = (fnMcp2210_GetGpioPinDir) GetProcAddress(m_hMcpDll, "Mcp2210_GetGpioPinDir");
    pmcpSetGpioPinDir           = (fnMcp2210_SetGpioPinDir) GetProcAddress(m_hMcpDll, "Mcp2210_SetGpioPinDir");
    pmcpGetGpioPinVal           = (fnMcp2210_GetGpioPinVal) GetProcAddress(m_hMcpDll, "Mcp2210_GetGpioPinVal");
    pmcpSetGpioPinVal           = (fnMcp2210_SetGpioPinVal) GetProcAddress(m_hMcpDll, "Mcp2210_SetGpioPinVal");
    pmcpGetGpioConfig           = (fnMcp2210_GetGpioConfig) GetProcAddress(m_hMcpDll, "Mcp2210_GetGpioConfig");
    pmcpSetGpioConfig           = (fnMcp2210_SetGpioConfig) GetProcAddress(m_hMcpDll, "Mcp2210_SetGpioConfig");
    pmcpGetInterruptCount       = (fnMcp2210_GetInterruptCount) GetProcAddress(m_hMcpDll, "Mcp2210_GetInterruptCount");
    pmcpGetSpiConfig            = (fnMcp2210_GetSpiConfig) GetProcAddress(m_hMcpDll, "Mcp2210_GetSpiConfig");
    pmcpSetSpiConfig            = (fnMcp2210_SetSpiConfig) GetProcAddress(m_hMcpDll, "Mcp2210_SetSpiConfig");
    pmcpxferSpiData             = (fnMcp2210_xferSpiData) GetProcAddress(m_hMcpDll, "Mcp2210_xferSpiData");
    pmcpxferSpiDataEx           = (fnMcp2210_xferSpiDataEx) GetProcAddress(m_hMcpDll, "Mcp2210_xferSpiDataEx");
    pmcpCancelSpiTxfer          = (fnMcp2210_CancelSpiTxfer) GetProcAddress(m_hMcpDll, "Mcp2210_CancelSpiTxfer");
    pmcpRequestSpiBusRel        = (fnMcp2210_RequestSpiBusRel) GetProcAddress(m_hMcpDll, "Mcp2210_RequestSpiBusRel");
    pmcpGetSpiStatus            = (fnMcp2210_GetSpiStatus) GetProcAddress(m_hMcpDll, "Mcp2210_GetSpiStatus");
    pmcpReadEEProm              = (fnMcp2210_ReadEEProm) GetProcAddress(m_hMcpDll, "Mcp2210_ReadEEProm");
    pmcpWriteEEProm             = (fnMcp2210_WriteEEProm) GetProcAddress(m_hMcpDll, "Mcp2210_WriteEEProm");
    pmcpGetAccessCtrlStatus     = (fnMcp2210_GetAccessCtrlStatus) GetProcAddress(m_hMcpDll, "Mcp2210_GetAccessCtrlStatus");
    pmcpEnterPassword           = (fnMcp2210_EnterPassword) GetProcAddress(m_hMcpDll, "Mcp2210_EnterPassword");
    pmcpSetAccessControl        = (fnMcp2210_SetAccessControl) GetProcAddress(m_hMcpDll, "Mcp2210_SetAccessControl");
    pmcpSetPermanentLock        = (fnMcp2210_SetPermanentLock) GetProcAddress(m_hMcpDll, "Mcp2210_SetPermanentLock");

    return 0;
}

void mcpShowError(int err)
{
    switch (err)
    {
        case E_SUCCESS:
            printf("E_SUCCESS\n");
            break;
        case E_ERR_UNKOWN_ERROR:
            printf("E_ERR_UNKOWN_ERROR\n");
            break;
        case E_ERR_INVALID_PARAMETER:
            printf("E_ERR_INVALID_PARAMETER\n");
            break;
        case E_ERR_BUFFER_TOO_SMALL:
            printf("E_ERR_BUFFER_TOO_SMALL\n");
            break;

        /* memory access errors */
        case E_ERR_NULL:
            printf("E_ERR_NULL\n");
            break;
        case E_ERR_MALLOC:
            printf("E_ERR_MALLOC\n");
            break;
        case E_ERR_INVALID_HANDLE_VALUE:
            printf("E_ERR_INVALID_HANDLE_VALUE\n");
            break;

        /* errors connecting to HID device */
        case E_ERR_FIND_DEV:
            printf("E_ERR_FIND_DEV\n");
            break;
        case E_ERR_NO_SUCH_INDEX:
            printf("E_ERR_NO_SUCH_INDEX\n");
            break;
        case E_ERR_DEVICE_NOT_FOUND:
            printf("E_ERR_DEVICE_NOT_FOUND\n");
            break;
        case E_ERR_INTERNAL_BUFFER_TOO_SMALL:
            printf("E_ERR_INTERNAL_BUFFER_TOO_SMALL\n");
            break;
        case E_ERR_OPEN_DEVICE_ERROR:
            printf("E_ERR_OPEN_DEVICE_ERROR\n");
            break;
        case E_ERR_CONNECTION_ALREADY_OPENED:
            printf("E_ERR_CONNECTION_ALREADY_OPENED\n");
            break;
        case E_ERR_CLOSE_FAILED:
            printf("E_ERR_CLOSE_FAILED\n");
            break;
        case E_ERR_NO_SUCH_SERIALNR:
            printf("E_ERR_NO_SUCH_SERIALNR\n");
            break;
        case E_ERR_HID_RW_TIMEOUT:
            printf("E_ERR_HID_RW_TIMEOUT\n");
            break;
        case E_ERR_HID_RW_FILEIO:
            printf("E_ERR_HID_RW_FILEIO\n");
            break;

        /* MCP2210 device command reply errors */
        case E_ERR_CMD_FAILED:
            printf("E_ERR_CMD_FAILED\n");
            break;
        case E_ERR_CMD_ECHO:
            printf("E_ERR_CMD_ECHO\n");
            break;
        case E_ERR_SUBCMD_ECHO:
            printf("E_ERR_SUBCMD_ECHO\n");
            break;

        case E_ERR_SPI_CFG_ABORT:
            printf("E_ERR_SPI_CFG_ABORT\n");
            break;
        case E_ERR_SPI_EXTERN_MASTER:
            printf("E_ERR_SPI_EXTERN_MASTER\n");
            break;
        case E_ERR_SPI_TIMEOUT:
            printf("E_ERR_SPI_TIMEOUT\n");
            break;
        case E_ERR_SPI_RX_INCOMPLETE:
            printf("E_ERR_SPI_RX_INCOMPLETE\n");
            break;
        case E_ERR_SPI_XFER_ONGOING:
            printf("E_ERR_SPI_XFER_ONGOING\n");
            break;

        /* MCP2210 device password protection */
        case E_ERR_BLOCKED_ACCESS:
            printf("E_ERR_BLOCKED_ACCESS\n");
            break;
        case E_ERR_EEPROM_WRITE_FAIL:
            printf("E_ERR_EEPROM_WRITE_FAIL\n");
            break;

        case E_ERR_NVRAM_LOCKED:
            printf("E_ERR_NVRAM_LOCKED\n");
            break;
        case E_ERR_WRONG_PASSWD:
            printf("E_ERR_WRONG_PASSWD\n");
            break;
        case E_ERR_ACCESS_DENIED:
            printf("E_ERR_ACCESS_DENIED\n");
            break;
        case E_ERR_NVRAM_PROTECTED:
            printf("E_ERR_NVRAM_PROTECTED\n");
            break;
        case E_ERR_PASSWD_CHANGE:
            printf("E_ERR_PASSWD_CHANGE\n");
            break;

        /* MCP2210 USB descriptors */
        case E_ERR_STRING_DESCRIPTOR:
            printf("E_ERR_STRING_DESCRIPTOR\n");
            break;
        case E_ERR_STRING_TOO_LARGE:
            printf("E_ERR_STRING_TOO_LARGE\n");
            break;

        default:
            printf("Unknown error type: %x\n", err);
            break;

    }
}

void mcp25625Cmd(HANDLE h, unsigned char cmd)
{
    int err;
    unsigned char txData[16];
    unsigned char rxData[16];
    unsigned int xfrSize;
    unsigned int csMask = 0x02; // 0x02 => CS1

    txData[0] = cmd;
    err = mcpxferSpiData(h, txData, rxData, &baudRate, &xfrSize, csMask);
    if (!MCP_SUCCESS(err))
    {
        mcpShowError(err);
    }
}



void mcp2210SetPin(HANDLE h, unsigned int pin, unsigned int state)
{
    int err;
    unsigned int gpioPinVal;
    err = mcpGetGpioPinVal(h, &gpioPinVal);
    if (state == 1)
    {
        gpioPinVal |= (1 << pin);
    }
    else
    {
        gpioPinVal &= ~(1 << pin);
    }
    err = mcpSetGpioPinVal(h, gpioPinVal, &gpioPinVal);
}

#define MCP26625_CS 1

int mcp25625_Config()
{
    mcp25625_hw_reset();
    mcp25625_init(OPMODE_LOOP); // OPMODE_LOOP, OPMODE_NORMAL, OPMODE_LISTEN, OPMODE_SLEEP, OPMODE_CONFIG

    return 0;
}

void max6675()
{
    int err;
    unsigned int len;
    uint8_t rxData[16];
    uint8_t txData[16];
    unsigned int csMask = 0x02; // 0x02 => CS1

    MCP2211_hal_init();

    while (1)
    {
        len = 2;
        err = mcpxferSpiData(hDev, txData, rxData, &baudRate, &len, csMask);
        if (!MCP_SUCCESS(err))
        {
            mcpShowError(err);
            return;
        }
        else
        {
            hexdump(stdout, rxData, len);
            int temp = ((rxData[0] << 8) | rxData[1]) & 0xFFFF;
            temp >>= 3;
            temp &= 0x3FF;
            temp >>= 2;
            printf("temp: %d\n", temp);
        }
        Sleep(1000);
    }
}

int mcp2210_Config()
{

    mcp25625_Config();
    //max6675();
#if 0
    if( mcp25625_filter_config( RXF_0, 0x07FF, 0, true )     || 
        mcp25625_filter_config( RXF_1, 0x0001, 0, true )     || 
        mcp25625_filter_config( RXF_2, 0, 0x1FFFFFFF, true ) || 
        mcp25625_filter_config( RXF_3, 0, 0x00000000, true ) || 
        mcp25625_filter_config( RXF_4, 0, 0x00000001, true ) || 
        mcp25625_filter_config( RXF_5, 0, 0x0000000F, true ) )
        printf( " - Filter Config Error\n" );
    else
        printf( " - Filter Config Done\n" );

    if( mcp25625_mask_config( RXB0, 0x07FF, 0x1FFFFFFF ) || 
        mcp25625_mask_config( RXB1, 0x07FF, 0x1FFFFFFF ) )
        printf( " - Mask Config Error\n" );
    else
        printf( " - Mask Config Done\n" );

    if( mcp25625_rx_config( RXB0, RX_MODE_SID, false, false ) || 
        mcp25625_rx_config( RXB1, RX_MODE_EID, false, false ) )
        printf( " - RX Configuration Error\n" );
    else
        printf( " - RX Config Done\n" );
#endif

    uint32_t EID = 0;
    uint32_t rEID = 0;
    while (1)
    {
        bool rdy;
        int err;
        bool RX_IDE, RX_RTR;
        uint8_t count;
        uint8_t tx_test[8] = { 'M', 'S', 'G', '\0' };
        uint8_t rx_test[8] = { 0 };

#if 1
        EID = 0;
        if (!mcp25625_msg_load(TXB0, tx_test, 4, EID, true, false) &&
            !mcp25625_msg_send(TXB0))
        {
            printf("TXB0 sent...\n");
        }
        else
        {
            printf("TXB0 error sending...\n");
        }

        EID = 1;
        if (!mcp25625_msg_load(TXB1, tx_test, 4, EID, true, false) &&
            !mcp25625_msg_send(TXB1))
        {
            printf("TXB1 sent...\n");
        }
        else
        {
            printf("TXB1 error sending...\n");
        }
#endif

        rdy = mcp25625_msg_ready(RXB0);
        if (true == rdy) 
        {           
            //printf("ready on RXB0\n");
            EID = rEID;
            err = mcp25625_msg_read(RXB0, rx_test, &count, &EID, &RX_IDE, &RX_RTR);

            if (MCP25625_OK == err && count > 0)
            {
                //printf("buffer: %s\n", message);
                hexdump(stdout, rx_test, count);
            }

        }
        rdy = mcp25625_msg_ready(RXB1);
        if (true == rdy) 
        {
            //printf("ready on RXB1\n");
            //EID = 1;
            err = mcp25625_msg_read(RXB1, rx_test, &count, &EID, &RX_IDE, &RX_RTR);
            if (MCP25625_OK == err && count > 0)
            {
                //printf("buffer: %s\n", rx_test);
                hexdump(stdout, rx_test, count);
            }
        }
        rEID++;
        if (EID > 256) rEID = 0;
    }

    return 0;
}

int mcpGetLibraryVersion(wchar_t *version)
{
    return pmcpGetLibraryVersion(version);
}

/* API for getting access to the USB device */
int mcpGetLastError()
{
    return pmcpGetLastError();
}

int mcpGetConnectedDevCount(unsigned short vid, unsigned short pid)
{
    return pmcpGetConnectedDevCount(vid, pid);
}

void* mcpOpenByIndex(unsigned short vid, unsigned short pid, unsigned int index, wchar_t *devPath, unsigned long *devPathsize)
{
    return pmcpOpenByIndex(vid, pid, index, devPath, devPathsize);
}

void* mcpOpenBySN(unsigned short vid, unsigned short pid, wchar_t *serialNo, wchar_t *devPath, unsigned long *devPathsize)
{
    return pmcpOpenBySN(vid, pid, serialNo, devPath, devPathsize);
}

int mcpClose(void *handle)
{
    return pmcpClose(handle);
}

int mcpReset(void *handle)
{
    return pmcpReset(handle);
}

/* USB settings */
int mcpGetUsbKeyParams(void *handle, unsigned short *pvid, unsigned short *ppid,
    unsigned char *ppwrSrc, unsigned char *prmtWkup, unsigned short *pcurrentLd)
{
    return pmcpGetUsbKeyParams(handle, pvid, ppid, ppwrSrc, prmtWkup, pcurrentLd);
}

int mcpSetUsbKeyParams(void *handle, unsigned short vid, unsigned short pid,
    unsigned char pwrSrc, unsigned char rmtWkup, unsigned short currentLd)
{
    return pmcpSetUsbKeyParams(handle, vid, pid, pwrSrc, rmtWkup, currentLd);
}

int mcpGetManufacturerString(void *handle, wchar_t *manufacturerStr)
{
    return pmcpGetManufacturerString(handle, manufacturerStr);
}

int mcpSetManufacturerString(void *handle, wchar_t *manufacturerStr)
{
    return pmcpSetManufacturerString(handle, manufacturerStr);
}

int mcpGetProductString(void *handle, wchar_t *productStr)
{
    return pmcpGetProductString(handle, productStr);
}

int mcpSetProductString(void *handle, wchar_t *productStr)
{
    return pmcpSetProductString(handle, productStr);
}

int mcpGetSerialNumber(void *handle, wchar_t *serialStr)
{
    return pmcpGetSerialNumber(handle, serialStr);
}

/* API to access GPIO settings and values */
int mcpGetGpioPinDir(void *handle, unsigned int *pgpioDir)
{
    return pmcpGetGpioPinDir(handle, pgpioDir);
}

int mcpSetGpioPinDir(void *handle, unsigned int gpioSetDir)
{
    return pmcpSetGpioPinDir(handle, gpioSetDir);
}

int mcpGetGpioPinVal(void *handle, unsigned int *pgpioPinVal)
{
    return pmcpGetGpioPinVal(handle, pgpioPinVal);
}

int mcpSetGpioPinVal(void *handle, unsigned int gpioSetVal, unsigned int *pgpioPinVal)
{
    return pmcpSetGpioPinVal(handle, gpioSetVal, pgpioPinVal);
}

int mcpGetGpioConfig(void *handle, unsigned char cfgSelector, unsigned char *pGpioPinDes, unsigned int *pdfltGpioOutput,
    unsigned int *pdfltGpioDir, unsigned char *prmtWkupEn, unsigned char *pintPinMd, unsigned char *pspiBusRelEn)
{
    return pmcpGetGpioConfig(handle, cfgSelector, pGpioPinDes, pdfltGpioOutput, pdfltGpioDir, prmtWkupEn, pintPinMd, pspiBusRelEn);
}

int mcpSetGpioConfig(void *handle, unsigned char cfgSelector, unsigned char *pGpioPinDes, unsigned int dfltGpioOutput,
    unsigned int dfltGpioDir, unsigned char rmtWkupEn, unsigned char intPinMd, unsigned char spiBusRelEn)
{
    return pmcpSetGpioConfig(handle, cfgSelector, pGpioPinDes, dfltGpioOutput, dfltGpioDir, rmtWkupEn, intPinMd, spiBusRelEn);
}

int mcpGetInterruptCount(void *handle, unsigned int *pintCnt, unsigned char reset)
{
    return pmcpGetInterruptCount(handle, pintCnt, reset);
}

/* API to control SPI transfer */
int mcpGetSpiConfig(void *handle, unsigned char cfgSelector, unsigned int *pbaudRate, unsigned int *pidleCsVal,
    unsigned int *pactiveCsVal, unsigned int *pCsToDataDly, unsigned int *pdataToCsDly,
    unsigned int *pdataToDataDly, unsigned int *ptxferSize, unsigned char *pspiMd)
{
    return pmcpGetSpiConfig(handle, cfgSelector, pbaudRate, pidleCsVal, pactiveCsVal, pCsToDataDly, pdataToCsDly, pdataToDataDly, ptxferSize, pspiMd);
}

int mcpSetSpiConfig(void *handle, unsigned char cfgSelector, unsigned int *pbaudRate, unsigned int *pidleCsVal,
    unsigned int *pactiveCsVal, unsigned int *pCsToDataDly, unsigned int *pdataToCsDly,
    unsigned int *pdataToDataDly, unsigned int *ptxferSize, unsigned char *pspiMd)

{
    return pmcpSetSpiConfig(handle, cfgSelector, pbaudRate, pidleCsVal, pactiveCsVal, pCsToDataDly, pdataToCsDly, pdataToDataDly, ptxferSize, pspiMd);
}

int mcpxferSpiData(void *handle, unsigned char *pdataTx, unsigned char *pdataRx,
    unsigned int *pbaudRate, unsigned int *ptxferSize, unsigned int csmask)
{
    return pmcpxferSpiData(handle, pdataTx, pdataRx, pbaudRate, ptxferSize, csmask);
}

int mcpxferSpiDataEx(void *handle, unsigned char *pdataTx, unsigned char *pdataRx,
    unsigned int *pbaudRate, unsigned int *ptxferSize, unsigned int csmask,
    unsigned int *pidleCsVal, unsigned int *pactiveCsVal, unsigned int *pCsToDataDly,
    unsigned int *pdataToCsDly, unsigned int *pdataToDataDly, unsigned char *pspiMd)
{
    return pmcpxferSpiDataEx(handle, pdataTx, pdataRx, pbaudRate, ptxferSize, csmask, pidleCsVal, pactiveCsVal, pCsToDataDly, pdataToCsDly, pdataToDataDly, pspiMd);
}

int mcpCancelSpiTxfer(void *handle, unsigned char *pspiExtReqStat, unsigned char *pspiOwner)
{
    return pmcpCancelSpiTxfer(handle, pspiExtReqStat, pspiOwner);
}

int mcpRequestSpiBusRel(void *handle, unsigned char ackPinVal)
{
    return pmcpRequestSpiBusRel(handle, ackPinVal);
}

int mcpGetSpiStatus(void *handle, unsigned char *pspiExtReqStat, unsigned char *pspiOwner, unsigned char *pspiTxferStat)
{
    return pmcpGetSpiStatus(handle, pspiExtReqStat, pspiOwner, pspiTxferStat);
}

/* EEPROM read/write API */
int mcpReadEEProm(void *handle, unsigned char address, unsigned char *pcontent)
{
    return pmcpReadEEProm(handle, address, pcontent);
}

int mcpWriteEEProm(void *handle, unsigned char address, unsigned char content)
{
    return pmcpWriteEEProm(handle, address, content);
}

/* Access control API */
int mcpGetAccessCtrlStatus(void *handle, unsigned char *pAccessCtrl, unsigned char *pPasswdAttemptCnt, unsigned char *pPasswdAccepted)
{
    return pmcpGetAccessCtrlStatus(handle, pAccessCtrl, pPasswdAttemptCnt, pPasswdAccepted);
}

int mcpEnterPassword(void *handle, char *passwd)
{
    return pmcpEnterPassword(handle, passwd);
}

int mcpSetAccessControl(void *handle, unsigned char accessConfig, char *currentPasswd, char *newPasswd)
{
    return pmcpSetAccessControl(handle, accessConfig, currentPasswd, newPasswd);
}

int mcpSetPermanentLock(void *handle)
{
    return pmcpSetPermanentLock(handle);
}


