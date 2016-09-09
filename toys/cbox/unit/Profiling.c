/*  ========================================================================
    Copyright (c) 2012-2016 HeliTrak, Inc.

    All rights reserved.  This file contains confidential information, Trade secrets and other proprietary
    information of HeliTrak.  Any use, Disclosure, reproduction, modification, performance, display or transfer of
    this file or any part of its contents is prohibited, except with the Express written authorization of HeliTrak.

    Rights in this program belong to:
        HeliTrak Inc.
        1620 26th Ave NW
        Gig Harbor, WA 98335

    Project   : HAP
    Subsystem : Common

    \File Profiling.c

    Description:
        This file provides profiling functions.

    Design Details and Explanations:

    Implementation Notes:

    \nonflight

    Revision History:

    Version #:              1
    Changed By:             Sola Park
    Date:                   04/11/2016
    Reason/Description/PR#: PR 3107

    Version #:              2
    Changed By:             Bart Bartel
    Date:                   09/01/2016
    Reason/Description/PR#: PR 2509    
    
    ======================================================================== */

/*  ========================================================================
                    Local Conditional Compilation Switches
    ======================================================================== */

/*  ========================================================================
                                Include Files
    ======================================================================== */


#include "RT_Timer.h"
#include "HeliTrak_Types.h"
#include "Debug_Support.h"
#include "Stream_IO.h"
#include "Math_Utils.h"
#include "Target_Software_Defs_MCP.h"


#if PROFILING


#include "Profiling.h"
#include <string.h>
#include <stdio.h>


/*  ========================================================================
                                 Definitions
    ======================================================================== */
/*  ========================================================================
    \def PRINT_ARRAY_SIZE
    \brief Size of the array to be printed
    \nonflight
    ======================================================================== */
#define PRINT_ARRAY_SIZE            (14)

/*  ========================================================================
    \def MSG_ARRAY_SIZE
    \brief Size of the msg part of the array to be printed
    \nonflight
    ======================================================================== */
#define MSG_ARRAY_SIZE              (7)

/*  ========================================================================
    \def DECIMAL_POINT_INDEX
    \brief Index of the decimal point in the array
    \nonflight
    ======================================================================== */
#define DECIMAL_POINT_INDEX         (9)

/*  ========================================================================
    \def PERCENT_SIGN_INDEX
    \brief Index of the percent sign in the array
    \nonflight
    ======================================================================== */
#define PERCENT_SIGN_INDEX          (13)

/*  ========================================================================
    \def PROFILE_BUFFER_SIZE
    \brief Size of the profile buffer to be streamed
    \nonflight
    ======================================================================== */
#define PROFILE_ARRAY_SIZE          (512)

/*  ========================================================================
    \def PROFILE_TEMP_BUFFER_SIZE
    \brief Size of the array used for internal formatting
    \nonflight
    ======================================================================== */
#define PROFILE_TEMP_BUFFER_SIZE    (16)

/*  ========================================================================
    \def DECIMAL_MULTIPLE
    \brief Threshold, multiplier and divisor for ftoa conversion.
    \nonflight
    ======================================================================== */
#define DECIMAL_MULTIPLE            (10.0f)

/*  ========================================================================
    \def SINGLE_DIGIT_MAX
    \brief Maximum value for a given digit in a floating point number.
    \nonflight
    ======================================================================== */
#define SINGLE_DIGIT_MAX            (9)

/*  ========================================================================
    \def DECIMAL_BASE
    \brief Numveric value for base-10 integer conversion.
    \nonflight
    ======================================================================== */
#define DECIMAL_BASE                (10)

/*  ========================================================================
    \def NUM_SIGNIFICANT_DIGITS
    \brief Number of significant digits for ftoa conversion.
    \nonflight
    ======================================================================== */
#define NUM_SIGNIFICANT_DIGITS      (8)

/*  ========================================================================
    \def PROFILE_SAMPLE_SIZE
    \brief Sample length for calculating running average and sigma
    \nonflight
    ======================================================================== */
#define PROFILE_SAMPLE_SIZE         (16)

/*  ========================================================================
    \def NUM_STD_DEV_SAMPLE
    \brief Number of standard deviations to add to average for thresholding.
    \nonflight
    ======================================================================== */
#define NUM_STD_DEV_SAMPLE          (3)

#if 0
/*  ========================================================================
    \def FULL_MCP_FRAME_THRESH
    \brief Threshold for full frame profile time, seconds.
    \nonflight
    ======================================================================== */
#define FULL_MCP_FRAME_THRESH       (0.0077333f)

/*  ========================================================================
    \def FRAME_MGMT_THRESH
    \brief Threshold for Frame_Mgmt_Run profile time, seconds.
    \nonflight
    ======================================================================== */
#define FRAME_MGMT_THRESH           (0.0000504f)

/*  ========================================================================
    \def SYSTEM_LOG_WFQ_THRESH
    \brief Threshold for System_Log_Wait_For_Queued_Log_Event_Write_Completion 
           profile time, seconds.
    \nonflight
    ======================================================================== */
#define SYSTEM_LOG_WFQ_THRESH       (0.0000133f)

/*  ========================================================================
    \def IPC_SETUP_DMA_THRESH
    \brief Threshold for IPC_Setup_DMA_Ring_Data_Rx profile time, seconds.
    \nonflight
    ======================================================================== */
#define IPC_SETUP_DMA_THRESH        (0.0000472f)

/*  ========================================================================
    \def SIGNALS_IN_RUN_THRESH
    \brief Threshold for Signals_In_Run_Gather profile time, seconds.
    \nonflight
    ======================================================================== */
#define SIGNALS_IN_RUN_THRESH       (0.0022574f)

/*  ========================================================================
    \def USER_INPUT_RUN_THRESH
    \brief Threshold for User_Input_Run profile time, seconds.
    \nonflight
    ======================================================================== */
#define USER_INPUT_RUN_THRESH       (0.0000579f)

/*  ========================================================================
    \def SYSTEM_LOG_SPWR_THRESH
    \brief Threshold for System_Log_Set_Power_State profile time, seconds.
    \nonflight
    ======================================================================== */
#define SYSTEM_LOG_SPWR_THRESH      (0.0000075f)

/*  ========================================================================
    \def MCP_STATE_RUN_THRESH
    \brief Threshold for MCP_State_Run profile time, seconds.
    \nonflight
    ======================================================================== */
#define MCP_STATE_RUN_THRESH        (0.0000039f)

/*  ========================================================================
    \def SYSTEM_LOG_WSS_THRESH
    \brief Threshold for System_Log_Write_System_State profile time, seconds.
    \nonflight
    ======================================================================== */
#define SYSTEM_LOG_WSS_THRESH       (0.0001434f)

/*  ========================================================================
    \def MAIN_MCP_RUN_PRE_THRESH
    \brief Threshold for Main_MCP_Run_Preprocessing profile time, seconds.
    \nonflight
    ======================================================================== */
#define MAIN_MCP_RUN_PRE_THRESH     (0.0007805f)

/*  ========================================================================
    \def MAIN_MCP_RUN_STG_1_THRESH
    \brief Threshold for Main_MCP_Run_Stage_1 profile time, seconds.
    \nonflight
    ======================================================================== */
#define MAIN_MCP_RUN_STG_1_THRESH   (0.0008720f)

/*  ========================================================================
    \def MAIN_MCP_RUN_STG_2_THRESH
    \brief Threshold for Main_MCP_Run_Stage_2 profile time, seconds.
    \nonflight
    ======================================================================== */
#define MAIN_MCP_RUN_STG_2_THRESH   (0.0013946f)

/*  ========================================================================
    \def MAIN_MCP_RUN_STG_3_THRESH
    \brief Threshold for Main_MCP_Run_Stage_3 profile time, seconds.
    \nonflight
    ======================================================================== */
#define MAIN_MCP_RUN_STG_3_THRESH   (0.0007823f)

/*  ========================================================================
    \def MAIN_MCP_RUN_STG_4_THRESH
    \brief Threshold for Main_MCP_Run_Stage_4 profile time, seconds.
    \nonflight
    ======================================================================== */
#define MAIN_MCP_RUN_STG_4_THRESH   (0.0007107f)

/*  ========================================================================
    \def MAIN_MCP_RUN_STG_5_THRESH
    \brief Threshold for Main_MCP_Run_Stage_5 profile time, seconds.
    \nonflight
    ======================================================================== */
#define MAIN_MCP_RUN_STG_5_THRESH   (0.0005943f)
#endif

/*  ========================================================================
    \def PROFILER_FRAME_COUNT
    \brief Threshold for controlling rate of profiler stream output.
    \nonflight
    ======================================================================== */
#define PROFILER_FRAME_COUNT        (300)

/*  ========================================================================
    \var frame_count
    \brief A frame counter for controlling output rate of profiler stream output.
    \nonflight
    ======================================================================== */
static U32 frame_count;

/*  ========================================================================
    \var profiling_timer
    \brief A timer to be used for profiling
    \nonflight
    ======================================================================== */
static TIMESTAMP profiling_timer;

/*  ========================================================================
    \var print_array
    \brief Array to be printed
    \nonflight
    ======================================================================== */
static char print_array[PRINT_ARRAY_SIZE] = {0};

/*  ========================================================================
    \var msg_array
    \brief Message part of the array to be printed
    \nonflight
    ======================================================================== */
static char * msg_array = "usage: ";

#if 0
/** ========================================================================
    \struct _phase
    \brief Defines the values for a given phase.
    \nonflight
    ======================================================================== */
struct _phase {
    int num;
    F32 avg;
    F32 stdev;
    F32 expect; // 3 sigma allowance
    char name[64];
    TIMESTAMP timer;
}; 

struct _phase phases[] = {
    /* index               avg   dev  expect                     name  */
    {FULL_MCP_FRAME,       0.0f, 0.0, FULL_MCP_FRAME_THRESH,     "Full_Mcp_Frame\0"},
    {FRAME_MGMT,           0.0f, 0.0, FRAME_MGMT_THRESH,         "Frame_Mgmt\0"},
    {SYSTEM_LOG_WFQ,       0.0f, 0.0, SYSTEM_LOG_WFQ_THRESH,     "System_Log_Wait_For_Queued_Log_Event_Write_Completion\0"},
    {IPC_SETUP_DMA,        0.0f, 0.0, IPC_SETUP_DMA_THRESH,      "IPC_Setup_DMA\0"},
    {SIGNALS_IN_RUN,       0.0f, 0.0, SIGNALS_IN_RUN_THRESH,     "Signals_In_Run_Gather\0"},
    {USER_INPUT_RUN,       0.0f, 0.0, USER_INPUT_RUN_THRESH,     "User_Input_Run\0"},
    {SYSTEM_LOG_SPWR,      0.0f, 0.0, SYSTEM_LOG_SPWR_THRESH,    "System_Log_Set_Power_State\0"},
    {MCP_STATE_RUN,        0.0f, 0.0, MCP_STATE_RUN_THRESH,      "MCP_State_Run\0"},
    {SYSTEM_LOG_WSS,       0.0f, 0.0, SYSTEM_LOG_WSS_THRESH,     "System_Log_Write_System_State\0"},
    {MAIN_MCP_RUN_PRE,     0.0f, 0.0, MAIN_MCP_RUN_PRE_THRESH,   "Main_MCP_Run_Preprocessing\0"},
    {MAIN_MCP_RUN_STG_1,   0.0f, 0.0, MAIN_MCP_RUN_STG_1_THRESH, "Main_MCP_Run_Stage_1\0"},
    {MAIN_MCP_RUN_STG_2,   0.0f, 0.0, MAIN_MCP_RUN_STG_2_THRESH, "Main_MCP_Run_Stage_2\0"},
    {MAIN_MCP_RUN_STG_3,   0.0f, 0.0, MAIN_MCP_RUN_STG_3_THRESH, "Main_MCP_Run_Stage_3\0"},
    {MAIN_MCP_RUN_STG_4,   0.0f, 0.0, MAIN_MCP_RUN_STG_4_THRESH, "Main_MCP_Run_Stage_4\0"},
    {MAIN_MCP_RUN_STG_5,   0.0f, 0.0, MAIN_MCP_RUN_STG_5_THRESH, "Main_MCP_Run_Stage_5\0"}
};
#endif


/*  ========================================================================
                           Private Function Prototypes
    ======================================================================== */

/** ===================================================================================================================
    Function Description
        Converts a signed integer to a string, based on the radix.

    \Parameter[in] value, signed integer.
    \Parameter[out] sp, char buffer to contain the result of the conversion.
    \Parameter[in] radix, base of the integer (2, 10, 16)
    
    \return        length of the conversion string, sp, not including the terminator.
    
    \nonflight
====================================================================================================================*/
int itoa(int value, char *sp, int radix)
{
    char tmp[16];       // string buffer for result
    char *tp = tmp;     // pointer to string buffer
    int i;              // decimal place value
    int len;            // length of string returned
    unsigned int v;     // radix variable


    int sign = (radix == DECIMAL_BASE && value < 0);    
    if (sign) 
    {
        v = -value;
    } 
    else 
    {
        v = (unsigned int) value;
    }

    // string is populated in reverse
    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < DECIMAL_BASE)
        {
            // decimal or hex numeric digit
            *tp++ = i + '0';
        }
        else
        {
            // hex alpha digit
            *tp++ = i + 'a' - DECIMAL_BASE;
        }
    }

    len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    // reverse the string
    while (tp > tmp)
    {
        *sp++ = *--tp;
    }
    *sp = '\0'; // null terminate

    return len;
}


/** ===================================================================================================================
    Function Description
        Converts a float to a string.

    \Parameter[in] f, single precision floating number.
    \Parameter[in] significant, number of significant digits minus one.
    \Parameter[out] buf, char buffer to contain the result of the conversion.

    \return        void
    
    \nonflight
====================================================================================================================*/
static int ftoa(float f, int significant, char *buf)
{
    int pos = 0; // initial buffer position
    int ix;      // loop index
    int dp;      // digit counter
    int num;     // integer value of a float digit
    int len;     // length of resultant string

    if ( f < 0)
    {
        buf[pos++] = '-';
        f = -f;
    }

    dp = 0; // set number of decimals to zero
    // force all but single digit left of decimal
    // and accumulate the number of places shifted
    while ( f >= DECIMAL_MULTIPLE) 
    {
        f = f / DECIMAL_MULTIPLE;
        dp++;
    }
    // dp now contains the number of decimals shifted
    // left such that f > 0.0 and < 10.0
    // f will be of the form w.xyz...
    for (ix = 1; ix < significant; ix++)
    {
        // peel off leading digit
        num = f;
        // remove leading digit, 
        // next digit will be shifted over below
        f = f - num;
        if (num > SINGLE_DIGIT_MAX) // invalid digit
        {
            buf[pos++] = '#'; // NaN
        }
        else
        {
            buf[pos++] = '0' + num; // number to char conversion
        }
        if (dp == 0) // finished processing digits to left of decimal place
        {            // remaining digits will be right of decimal
            buf[pos++] = '.';
        }
        f = f * DECIMAL_MULTIPLE; // shift next digit over
        dp--;
    }
    len = pos;
    return len;
}


/*  ========================================================================
    \def Format_Float_Profile
    \brief Function to format integers for phase profiler.
    \nonflight
    ======================================================================== */
static int Format_Float_Profile(char *b, char *tb, int off, float n)
{ 
    int len, rem;
    int i, j;
    memset(tb, '\0', PROFILE_TEMP_BUFFER_SIZE);
    memset(b+off, '\0', PROFILE_TEMP_BUFFER_SIZE);
    len = ftoa(n, NUM_SIGNIFICANT_DIGITS, tb);
    for (i = off, j = 0; j < len; ++i, ++j) {
        b[i] = tb[j];
    }
    rem = off+len;
    b[rem++] = ',';
    b[rem++] = ' ';
    b[rem] = '\0';
    len += 2;
    return len;
}                           

/*  ========================================================================
    \def Format_Int_Profile
    \brief Function to format integers for phase profiler.
    \nonflight
    ======================================================================== */
static int Format_Int_Profile(char *b, char *tb, int off, int n, int base)
{
    int len, rem;
    int i, j;
    memset(tb, '\0', PROFILE_TEMP_BUFFER_SIZE);
    memset(b+off, '\0', PROFILE_TEMP_BUFFER_SIZE);
    len = itoa(n, tb, base);
    for (i = off, j = 0; j < len; ++i, ++j) {
        b[i] = tb[j];
    }
    rem = off+len;
    b[rem++] = ',';
    b[rem++] = ' ';
    b[rem] = '\0';
    len += 2;
    return len;
}

/*  ========================================================================
    \def Format_String_Profile
    \brief Function to format strings for phase profiler.
    \nonflight
    ======================================================================== */
static int Format_String_Profile(char *b, int off, char *str)
{
    int len, rem;
    int i, j;
    len = strlen(str);
    for (i = off, j = 0; j < len; ++i, ++j) {
        b[i] = str[j];
    }
    rem = off+len;
    b[rem++] = ',';
    b[rem++] = ' ';
    b[rem] = '\0';
    len += 2;
    return len;
}

/*  ========================================================================
                                 Public Functions
    ======================================================================== */

/** ========================================================================
    Function Description:
        Starts profiling.

    \Return None

    \nonflight
    ======================================================================== */
void Profiling_Start()
{

    // gets the profiling time stamp to begin counting time
    RT_Timer_Get_Timestamp(&profiling_timer);
}


/** ========================================================================
    Function Description:
        Stops profiling.

    \Return None

    \nonflight
    ======================================================================== */
void Profiling_Stop()
{
    U8 i; // loop counter

    // get the elapsed time to measure how much time has passed since profiling began
    F32 profiling_time_elapsed = RT_Timer_Get_Elapsed_Time(&profiling_timer);

    // The operations per frame is expected to be completed within 0.01 seconds max.
    // So we calculate and display (actual time/expected time) * 100 (percentage) to show
    // the time main loop takes to complete the operations repeated per frame.
    F32 usage = BOUND(0, (profiling_time_elapsed/0.01f), 1);

    // copy the msg "main loop usage" part to the array to be printed
    memcpy(print_array, msg_array, MSG_ARRAY_SIZE);

    // loop through the array to store the string we're going to print
    for(i = MSG_ARRAY_SIZE; i < PRINT_ARRAY_SIZE; i++)
    {
        if (DECIMAL_POINT_INDEX == i)
        {
            print_array[i] = '.';
        }
        else if (PERCENT_SIGN_INDEX == i)
        {
            print_array[i] = '%';
        }
        else
        {
            // increment the usage ratio by 10 and cast to int to get the next digit.
            usage = 10 * usage;
            // store a matching char of the digit number we're interested in.
            print_array[i] = (U8)usage + '0';
            // move to the next digit.
            usage = usage - (U8)usage;
        }
    }

    // write to the telemetry port
    Stream_IO_Write(PRINT_ARRAY_SIZE, print_array, STREAM_STDIO);

} // Profiling_Stop()


/** ===================================================================================================================
    Function Description
        Prints the CSV header for profiler.

    \Parameter[in] none
    \Parameter[out] none

    \return        void
    
    \nonflight
====================================================================================================================*/
void Phase_Profile_Init()
{
    char buf[PROFILE_ARRAY_SIZE] = {0};
    int offset = 0;

    // initialize frame counter to zero
    frame_count = 0;
    
    offset += Format_String_Profile(buf, offset, phases[FULL_MCP_FRAME].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[FRAME_MGMT].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[SYSTEM_LOG_WFQ].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[IPC_SETUP_DMA].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[SIGNALS_IN_RUN].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[USER_INPUT_RUN].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[SYSTEM_LOG_SPWR].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[MCP_STATE_RUN].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[SYSTEM_LOG_WSS].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[MAIN_MCP_RUN_PRE].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[MAIN_MCP_RUN_STG_1].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[MAIN_MCP_RUN_STG_2].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[MAIN_MCP_RUN_STG_3].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[MAIN_MCP_RUN_STG_4].name);
    offset += Format_String_Profile(buf, offset, "stdev");
    offset += Format_String_Profile(buf, offset, phases[MAIN_MCP_RUN_STG_5].name);
    offset += Format_String_Profile(buf, offset, "stdev");

    buf[offset++] = '\r';
    buf[offset++] = '\n';
    buf[offset]   = '\0';

    Stream_IO_Write(strlen(buf), buf, STREAM_MX);
}

/** ===================================================================================================================
    Function Description
        Starts the profile timer for a given phase.

    \Parameter[in] phase_num, the phase number.
    \Parameter[out] none

    \return        void
    
    \nonflight
====================================================================================================================*/
void Phase_Profile_Start(int phase_num)
{
    RT_Timer_Get_Timestamp(&phases[phase_num].timer);
}

/** ===================================================================================================================
    Function Description
        Stops the profile timer for a given phase and calculates the running average and standard 
        deviation for the phase.

    \Parameter[in] phase_num, the phase number.
    \Parameter[out] none

    \return        void
    
    \nonflight
====================================================================================================================*/
void Phase_Profile_Stop(int phase_num)
{
    F32 avg;
    F32 stdev;
    F32 new_stdev;
    F32 new_sample = RT_Timer_Get_Elapsed_Time(&phases[phase_num].timer);
    avg = phases[phase_num].avg;
    if (avg != 0) {
        avg -= avg / PROFILE_SAMPLE_SIZE;
    }
    avg += new_sample / PROFILE_SAMPLE_SIZE;
    phases[phase_num].avg = avg;

    stdev = phases[phase_num].stdev;
    if (stdev != 0) {
        stdev -= stdev / PROFILE_SAMPLE_SIZE;
    }
    new_stdev = fabsf(avg - new_sample);
    stdev += new_stdev / PROFILE_SAMPLE_SIZE;
    phases[phase_num].stdev = stdev;

}

/** ===================================================================================================================
    Function Description
        Watches the timing for a given phase, and outputs phase number, measured timing, and expected timing
        if expected value is exeeded.

    \Parameter[in] phase_num, the phase number.
    \Parameter[out] none

    \return        void
    
    \nonflight
====================================================================================================================*/
void Phase_Profile_Monitor(int phase_num)
{
    char buf[PROFILE_ARRAY_SIZE] = {0};
    char tmp[PROFILE_TEMP_BUFFER_SIZE] = {0};
    F32 measured;
    F32 expected;
    int offset = 0;

    measured = phases[phase_num].avg + (NUM_STD_DEV_SAMPLE*phases[phase_num].stdev);
    expected = phases[phase_num].expect;
    if (measured > expected) {
        memset(buf,  '\0', PROFILE_ARRAY_SIZE);

        offset += Format_Int_Profile(buf, tmp, offset, phase_num, DECIMAL_BASE);
        offset += Format_Float_Profile(buf, tmp, offset, measured);
        offset += Format_Float_Profile(buf, tmp, offset, expected);

        buf[offset++] = '\r';
        buf[offset++] = '\n';
        buf[offset]   = '\0';

        Stream_IO_Write(strlen(buf), buf, STREAM_MX);
    }
}

/** ===================================================================================================================
    Function Description
        Watches the timing for all phases, and outputs phase number, measured timing, and expected timing
        for phases that exceed the expected value.

    \Parameter[in] none
    \Parameter[out] none

    \return        void
    
    \nonflight
====================================================================================================================*/
void Phase_Profile_Monitor_All()
{
    char buf[PROFILE_ARRAY_SIZE] = {0};
    char tmp[PROFILE_TEMP_BUFFER_SIZE] = {0};
    F32 measured;
    F32 expected;
    int offset = 0;
    int i;

    for (i = FULL_MCP_FRAME; i < PHASE_INDEX_LAST_ENTRY; ++i) {
        measured = phases[i].avg + (NUM_STD_DEV_SAMPLE*phases[i].stdev);
        expected = phases[i].expect;
        if (measured > expected) {
            memset(buf, 0, PROFILE_ARRAY_SIZE);

            offset += Format_Int_Profile(buf, tmp, offset, i, DECIMAL_BASE);
            offset += Format_Float_Profile(buf, tmp, offset, measured);
            offset += Format_Float_Profile(buf, tmp, offset, expected);

            buf[offset++] = '\r';
            buf[offset++] = '\n';
            buf[offset]   = '\0';

            Stream_IO_Write(strlen(buf), buf, STREAM_MX);
        }
    }
}

/** ===================================================================================================================
    Function Description
        Streams the CSV formatted profile data collected.

    \Parameter[in] none
    \Parameter[out] none

    \return        void
    
    \nonflight
====================================================================================================================*/
void Phase_Profile_Dump()
{
    char buf[PROFILE_ARRAY_SIZE] = {0};
    char tmp[PROFILE_TEMP_BUFFER_SIZE] = {0};
    int offset = 0;

    if (0 == frame_count % PROFILER_FRAME_COUNT)
    {

        offset += Format_Float_Profile(buf, tmp, offset, phases[FULL_MCP_FRAME].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[FULL_MCP_FRAME].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[FRAME_MGMT].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[FRAME_MGMT].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SYSTEM_LOG_WFQ].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SYSTEM_LOG_WFQ].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[IPC_SETUP_DMA].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[IPC_SETUP_DMA].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SIGNALS_IN_RUN].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SIGNALS_IN_RUN].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[USER_INPUT_RUN].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[USER_INPUT_RUN].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SYSTEM_LOG_SPWR].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SYSTEM_LOG_SPWR].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MCP_STATE_RUN].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MCP_STATE_RUN].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SYSTEM_LOG_WSS].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[SYSTEM_LOG_WSS].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_PRE].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_PRE].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_1].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_1].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_2].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_2].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_3].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_3].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_4].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_4].stdev);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_5].avg);
        offset += Format_Float_Profile(buf, tmp, offset, phases[MAIN_MCP_RUN_STG_5].stdev);

        buf[offset++] = '\r';
        buf[offset++] = '\n';
        buf[offset]   = '\0';

        Stream_IO_Write(strlen(buf), buf, STREAM_MX);

    }

    // increment frame counter
    frame_count++;

}


#endif // PROFILING

