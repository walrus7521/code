#ifndef _PROF_H_
#define _PROF_H_

/** ========================================================================
    \enum PHASE_INDEX
    \brief The PHASE_INDEX enumeration is a list of the software phases to profile.
    \nonflight
    ======================================================================== */
enum PHASE_INDEX {
    FULL_MCP_FRAME,
    FRAME_MGMT,
    SYSTEM_LOG_WFQ,
    IPC_SETUP_DMA,
    SIGNALS_IN_RUN,
    USER_INPUT_RUN,
    SYSTEM_LOG_SPWR,
    MCP_STATE_RUN,
    SYSTEM_LOG_WSS,
    MAIN_MCP_RUN_PRE,
    MAIN_MCP_RUN_STG_1,
    MAIN_MCP_RUN_STG_2,
    MAIN_MCP_RUN_STG_3,
    MAIN_MCP_RUN_STG_4,
    MAIN_MCP_RUN_STG_5,
    PHASE_INDEX_LAST_ENTRY
};

#if PROFILING

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

#endif // PROFILING

#endif // _PROF_H_
