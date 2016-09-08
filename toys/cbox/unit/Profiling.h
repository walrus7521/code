/**  ========================================================================
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

    \File Profiling.h

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
#ifndef PROFILING_H
#define PROFILING_H

/*  ========================================================================
                                Include Files
    ======================================================================== */

#include "Target_Software_Defs_MCP.h"

/*  ========================================================================
                                 Definitions
    ======================================================================== */

#include "prof.h"

#if PROFILING


/*  ========================================================================
                                Function Prototypes
    ======================================================================== */

void Profiling_Start();
void Profiling_Stop();
void Phase_Profile_Init();
void Phase_Profile_Start(int phase_num);
void Phase_Profile_Stop();
void Phase_Profile_Monitor(int phase_num);
void Phase_Profile_Monitor_All();
void Phase_Profile_Dump();

/*  ========================================================================
    \def PROFILING_START
    \brief PROFILING_START is a macro that wraps the function call to start profiling.
    \nonflight
    ======================================================================== */
#define PROFILING_START() { Profiling_Start(); }

/*  ========================================================================
    \def PROFILING_STOP
    \brief PROFILING_STOP is a macro that wraps the function call to stop profiling.
    \nonflight
    ======================================================================== */
#define PROFILING_STOP() { Profiling_Stop(); }

/*  ========================================================================
    \def PHASE_PROFILE_INIT
    \brief PHASE_PROFILE_INIT is a macro that wraps the function call to init phase profiling.
    \nonflight
    ======================================================================== */
#define PHASE_PROFILE_INIT() { Phase_Profile_Init(); }

/*  ========================================================================
    \def PHASE_PROFILE_START
    \brief PHASE_PROFILE_START is a macro that wraps the function call to start phase profiling.
    \nonflight
    ======================================================================== */
#define PHASE_PROFILE_START(p) { Phase_Profile_Start(p); }

/*  ========================================================================
    \def PHASE_PROFILE_STOP
    \brief PHASE_PROFILE_STOP is a macro that wraps the function call to stop phase profiling.
    \nonflight
    ======================================================================== */
#define PHASE_PROFILE_STOP(p) { Phase_Profile_Stop(p); }

/*  ========================================================================
    \def PHASE_PROFILE_MONITOR
    \brief PHASE_PROFILE_MONITOR is a macro that wraps the function call to monitor a selected 
           phase profiles.
    \nonflight
    ======================================================================== */
#define PHASE_PROFILE_MONITOR(p) { Phase_Profile_Monitor(p); }

/*  ========================================================================
    \def PHASE_PROFILE_MONITOR_ALL
    \brief PHASE_PROFILE_MONITOR_ALL is a macro that wraps the function call to monitor all phase profiles.
    \nonflight
    ======================================================================== */
#define PHASE_PROFILE_MONITOR_ALL() { Phase_Profile_Monitor_All(); }

/*  ========================================================================
    \def PHASE_PROFILE_DUMP
    \brief PHASE_PROFILE_DUMP is a macro that wraps the function call to stream phase profiling data.
    \nonflight
    ======================================================================== */
#define PHASE_PROFILE_DUMP() { Phase_Profile_Dump(); }

#else

#define PROFILING_START()
#define PROFILING_STOP()

#define PHASE_PROFILE_INIT()
#define PHASE_PROFILE_START(p)
#define PHASE_PROFILE_STOP(p)
#define PHASE_PROFILE_MONITOR(p)
#define PHASE_PROFILE_MONITOR_ALL()
#define PHASE_PROFILE_DUMP()

#endif // PROFILING

#endif // PROFILING_H
