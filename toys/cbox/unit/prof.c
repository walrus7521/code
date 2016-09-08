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

