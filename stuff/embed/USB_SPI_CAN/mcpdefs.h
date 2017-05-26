#ifndef __MCPDEFS_H__
#define __MCPDEFS_H__

#include "mcp2210_dll_um.h"
#include <Windows.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _WIN32
#  define __cdecl    /* nothing */
#  define __stdcall  /* nothing */
#  define __fastcall /* nothing */
#endif /* _WIN32 */

#define MCP_SUCCESS(status) ((status) == E_SUCCESS)

int mcp2210_DLL_Init();
int mcp25625_Config();
int mcp2210_Config();

/* MCP2210 UM DLL API definition */
int mcpGetLibraryVersion(wchar_t *version);

/* API for getting access to the USB device */
int   mcpGetLastError();
int   mcpGetConnectedDevCount(unsigned short vid, unsigned short pid);
void* mcpOpenByIndex(unsigned short vid, unsigned short pid, unsigned int index, wchar_t *devPath, unsigned long *devPathsize);
void* mcpOpenBySN(unsigned short vid, unsigned short pid, wchar_t *serialNo, wchar_t *devPath, unsigned long *devPathsize);
int   mcpClose(void *handle);
int   mcpReset(void *handle);

/* USB settings */
int mcpGetUsbKeyParams(void *handle, unsigned short *pvid, unsigned short *ppid,
                                                         unsigned char *ppwrSrc, unsigned char *prmtWkup, unsigned short *pcurrentLd);
int mcpSetUsbKeyParams(void *handle, unsigned short vid, unsigned short pid,
                                                         unsigned char pwrSrc, unsigned char rmtWkup, unsigned short currentLd);
int mcpGetManufacturerString(void *handle, wchar_t *manufacturerStr);
int mcpSetManufacturerString(void *handle, wchar_t *manufacturerStr);
int mcpGetProductString(void *handle, wchar_t *productStr);
int mcpSetProductString(void *handle, wchar_t *productStr);
int mcpGetSerialNumber(void *handle, wchar_t *serialStr);

/* API to access GPIO settings and values */
int mcpGetGpioPinDir(void *handle, unsigned int *pgpioDir);
int mcpSetGpioPinDir(void *handle, unsigned int gpioSetDir);
int mcpGetGpioPinVal(void *handle, unsigned int *pgpioPinVal);
int mcpSetGpioPinVal(void *handle, unsigned int gpioSetVal, unsigned int *pgpioPinVal);
int mcpGetGpioConfig(void *handle, unsigned char cfgSelector, unsigned char *pGpioPinDes, unsigned int *pdfltGpioOutput,
                                                       unsigned int *pdfltGpioDir, unsigned char *prmtWkupEn, unsigned char *pintPinMd, unsigned char *pspiBusRelEn);
int mcpSetGpioConfig(void *handle, unsigned char cfgSelector, unsigned char *pGpioPinDes, unsigned int dfltGpioOutput,
                                                       unsigned int dfltGpioDir, unsigned char rmtWkupEn, unsigned char intPinMd, unsigned char spiBusRelEn);
int mcpGetInterruptCount(void *handle, unsigned int *pintCnt, unsigned char reset);

/* API to control SPI transfer */
int mcpGetSpiConfig(void *handle, unsigned char cfgSelector, unsigned int *pbaudRate, unsigned int *pidleCsVal,
                                                      unsigned int *pactiveCsVal, unsigned int *pCsToDataDly, unsigned int *pdataToCsDly,
                                                      unsigned int *pdataToDataDly, unsigned int *ptxferSize, unsigned char *pspiMd);
int mcpSetSpiConfig(void *handle, unsigned char cfgSelector, unsigned int *pbaudRate, unsigned int *pidleCsVal,
                                                      unsigned int *pactiveCsVal, unsigned int *pCsToDataDly, unsigned int *pdataToCsDly,
                                                      unsigned int *pdataToDataDly, unsigned int *ptxferSize, unsigned char *pspiMd);

int mcpxferSpiData(void *handle, unsigned char *pdataTx, unsigned char *pdataRx,
                                                     unsigned int *pbaudRate, unsigned int *ptxferSize, unsigned int csmask);

int mcpxferSpiDataEx(void *handle, unsigned char *pdataTx, unsigned char *pdataRx,
                                                       unsigned int *pbaudRate, unsigned int *ptxferSize, unsigned int csmask,
                                                       unsigned int *pidleCsVal, unsigned int *pactiveCsVal, unsigned int *pCsToDataDly,
                                                       unsigned int *pdataToCsDly, unsigned int *pdataToDataDly, unsigned char *pspiMd);

int mcpCancelSpiTxfer(void *handle, unsigned char *pspiExtReqStat, unsigned char *pspiOwner);
int mcpRequestSpiBusRel(void *handle, unsigned char ackPinVal);
int mcpGetSpiStatus(void *handle, unsigned char *pspiExtReqStat, unsigned char *pspiOwner, unsigned char *pspiTxferStat);

/* EEPROM read/write API */
int mcpReadEEProm(void *handle, unsigned char address, unsigned char *pcontent);
int mcpWriteEEProm(void *handle, unsigned char address, unsigned char content);

/* Access control API */
int mcpGetAccessCtrlStatus(void *handle, unsigned char *pAccessCtrl, unsigned char *pPasswdAttemptCnt, unsigned char *pPasswdAccepted);
int mcpEnterPassword(void *handle, char *passwd);
int mcpSetAccessControl(void *handle, unsigned char accessConfig, char *currentPasswd, char *newPasswd);
int mcpSetPermanentLock(void *handle);

#ifdef __cplusplus
}
#endif

#endif // __MCPDEFS_H__
