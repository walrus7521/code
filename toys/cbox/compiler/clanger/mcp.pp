# 1 "main_MCP.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 331 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "main_MCP.c" 2



# 1 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h" 1
# 47 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h"
# 1 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h" 1
# 42 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
# 1 "..\\..\\..\\Common\\Header/HeliTrak_Constants.h" 1
# 41 "..\\..\\..\\Common\\Header/HeliTrak_Constants.h"
# 1 "..\\..\\..\\Common\\Header/HeliTrak_Natural_Constants.h" 1
# 42 "..\\..\\..\\Common\\Header/HeliTrak_Constants.h" 2
# 43 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h" 2








typedef unsigned char U8, u8;
# 61 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef signed char S8, s8;
# 71 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef unsigned short U16, u16;
# 81 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef signed short S16, s16;
# 91 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef unsigned long UL32, ul32, U32, u32;
# 101 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef signed long SL32, sl32, S32, s32;
# 111 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef unsigned long long UL64, ul64, U64, u64;
# 121 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef signed long long SL64, sl64, S64, s64;
# 131 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef float F32, f32;
# 141 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef u8 BOOLEAN;
# 163 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef void (*FUNCTION_PTR)(void);







typedef union
{
    void * generic_ptr;
    U32 unsigned_32;
    U32 * unsigned_32_ptr;
    U16 unsigned_16;
    U16 * unsigned_16_ptr;
    U8 unsigned_8;
    U8 * unsigned_8_ptr;
    S32 signed_32;
    S32 * signed_32_ptr;
    S16 signed_16;
    S16 * signed_16_ptr;
    S8 signed_8;
    S8 * signed_8_ptr;
    BOOLEAN boolean;
    BOOLEAN * boolean_ptr;
} STANDARD_TYPES_UNION;







typedef struct
{
    F32 X;
    F32 Y;
    F32 Z;
} VECTOR3;







typedef struct
{
    VECTOR3 row1;
    VECTOR3 row2;
    VECTOR3 row3;
} MATRIX3X3;







typedef struct
{
    F32 phi;
    F32 theta;
    F32 psi;
} EULER_ANGLES;







typedef struct
{
    F32 phi_dot;
    F32 theta_dot;
    F32 psi_dot;
} EULER_RATES;







typedef enum
{
    HAP_SUCCESS,
    HAP_FAIL = 1,
    HAP_GENERAL_ERROR = 1,
    HAP_INIT_ERROR,
    HAP_DIVIDE_BY_ZERO,


    HAP_LAST_ERROR



} RETURN_TYPE;
# 281 "..\\..\\..\\Common\\Header\\HeliTrak_Types.h"
typedef struct
{
    S16 X;
    S16 Y;
    S16 Z;
} SENSOR_ADC_SAMPLE_STRUCT;







typedef struct
{
    U8 num_samples;
    SENSOR_ADC_SAMPLE_STRUCT samples[(32)];
    SENSOR_ADC_SAMPLE_STRUCT average;
 } SENSOR_DATA_STRUCT;







typedef enum
{
    ST_BIAS_NONE,
    ST_BIAS_POSITIVE,
    ST_BIAS_NEGATIVE
} SELF_TEST_BIAS_TYPE;







typedef struct
{
    F32 roll;
    F32 pitch;
} CYCLIC_STRUCT;
# 48 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "..\\..\\..\\Common\\Header\\User_Input.h" 1
# 65 "..\\..\\..\\Common\\Header\\User_Input.h"
# 1 "..\\..\\..\\Common\\Header/Signals.h" 1
# 55 "..\\..\\..\\Common\\Header/Signals.h"
# 1 "..\\..\\..\\MCP\\Header\\Target_Signals.h" 1
# 107 "..\\..\\..\\MCP\\Header\\Target_Signals.h"
typedef enum
{
    SENSOR_GYRO0,
    SENSOR_ACCEL0,
    SENSOR_ACCEL_REMOTE,
    SENSOR_OAT_REMOTE,
    SENSOR_MAG_REMOTE,
    SENSOR_ADC0,
    SENSOR_ADC1,
    SIGNAL_CPD0,

    SENSOR_TOTAL
} SENSOR_SIGNALS_ENUM;
# 56 "..\\..\\..\\Common\\Header/Signals.h" 2
# 1 "..\\..\\..\\Common\\Header/Stream_IO.h" 1
# 83 "..\\..\\..\\Common\\Header/Stream_IO.h"
typedef enum
{
    STREAM_NULL,
    STREAM_MCP_SELF,
    STREAM_MCP_LEFT,
    STREAM_MCP_RIGHT,
    STREAM_MCPA,
    STREAM_MCPB,
    STREAM_MCPC,
    STREAM_ADP0,
    STREAM_GPS_RS232,
    STREAM_NVRAM0,
    STREAM_NVRAM1,
    STREAM_TELEM,
    STREAM_STDIO,
    STREAM_MX,
    STREAM_COEFF_FILE,
    STREAM_MFG_FILE,
    STREAM_INSTALL_FILE,
    STREAM_SYS_STATUS,
    STREAM_EVENT_LOG,
    STREAM_RAM,
    STREAM_ROM,
    STREAM_FRAM,
    STREAM_EEPROM,
    STREAM_REGISTER,
    STREAM_XPLANE,
    STREAM_NVRAM_REMOTE,

    STREAM_COUNT
} STREAM_ENUM;
# 122 "..\\..\\..\\Common\\Header/Stream_IO.h"
typedef enum
{
    IOCTL_TX_DISABLE,
    IOCTL_TX_ENABLE,
    IOCTL_RX_DISABLE,
    IOCTL_RX_ENABLE,
    IOCTL_TX_IS_BUSY,
    IOCTL_ENABLE_HW_FIFO,
    IOCTL_FLUSH_RX_BUFFER
# 145 "..\\..\\..\\Common\\Header/Stream_IO.h"
} IOCTL_ENUM;







typedef void (*STREAM_RX_HOOK_PTR)(U8 rx_byte);
typedef void (*STREAM_TX_HOOK_PTR)(U8 tx_byte);




typedef void (*DEVICE_CALLBACK)(void * context);

void Stream_IO_Initialize(void);
void Stream_IO_Set_Position(U32 address_in, STREAM_ENUM stream_in);
U32 Stream_IO_Read(U32 size, U8 * data_in, STREAM_ENUM stream_in);
U32 Stream_IO_Write(U32 size, U8 * data_out, STREAM_ENUM stream_out);
U32 Stream_IO_Write_Async(U32 size, U8 *data_out, STREAM_ENUM stream_out, DEVICE_CALLBACK callback, void *context);
U32 Stream_IO_Rx_Bytes_Available(STREAM_ENUM stream_in);
U32 Stream_IO_Tx_Space_Available(STREAM_ENUM stream_in);
U32 Stream_IO_IOCTL(IOCTL_ENUM IOCTL_enum, STANDARD_TYPES_UNION * param1, STREAM_ENUM stream_in);


struct _I2C_DEVICE_STRUCT;
struct _I2C_DEVICE_STRUCT *Stream_IO_Get_Device(STREAM_ENUM stream_enum);
# 57 "..\\..\\..\\Common\\Header/Signals.h" 2
# 1 "..\\..\\..\\Common\\Header/Debug_Support.h" 1
# 52 "..\\..\\..\\Common\\Header/Debug_Support.h"
# 1 "..\\..\\..\\Common\\Header/Target_Software_Defs_Common.h" 1
# 53 "..\\..\\..\\Common\\Header/Debug_Support.h" 2
# 63 "..\\..\\..\\Common\\Header/Debug_Support.h"
extern U8 printf_buffer[(1024)];

int stream_puts(const STREAM_ENUM stream, U8 *buf);

char *mystrcat(char *string1, char *string2);
void stream_itoa(const STREAM_ENUM stream, int value, U8 *sp, int radix);
void stream_ftoa(const STREAM_ENUM stream, float value, U8 *sp);
void stream_btoa(const STREAM_ENUM stream, int value, U8 *sp, int bits);


U8 *itoa(int value, U8 *sp, int radix);





    extern BOOLEAN dbg_print_enable;







    typedef enum
    {
        DEBUG_PRINT_COLUMN_NAMES,
        DEBUG_PRINT_STATE

    } DEBUG_PRINT_CMD;
    void DEBUG_Print(DEBUG_PRINT_CMD cmd);
# 253 "..\\..\\..\\Common\\Header/Debug_Support.h"
        extern void _assert(int, const char *);
        extern void _abort_msg(const char *);
# 58 "..\\..\\..\\Common\\Header/Signals.h" 2

# 1 "..\\..\\..\\Common\\Header/Signals_GPIO_CM3.h" 1
# 54 "..\\..\\..\\Common\\Header/Signals_GPIO_CM3.h"
typedef struct
{
    U32 port;

    U8 pin;

} PIN_GPIO_HW_STRUCT;






typedef void (*INTERRUPT_CALLBACK_PTR)(void * instance_ID);
# 105 "..\\..\\..\\Common\\Header/Signals_GPIO_CM3.h"
void Signals_Initialize(void);
RETURN_TYPE Signals_Run(void);
void Signals_GPIO_Initialize(void);
void Signals_GPIO_Run_Gather_Synchronized(void);
void Signals_GPIO_Run_Commit_Synchronized(void);
void Signals_GPIO_Set_Pin_Type_Input_Synchronized(PIN_GPIO_HW_STRUCT const * GPIO_ptr);
void Signals_GPIO_Set_Pin_Type_Async_Output(PIN_GPIO_HW_STRUCT const * GPIO_ptr);
void Signals_GPIO_Set_Pin_Type_Output_Synchronized(PIN_GPIO_HW_STRUCT const * GPIO_ptr);
void Signals_GPIO_Set_State_Synchronized(PIN_GPIO_HW_STRUCT const * GPIO_ptr, BOOLEAN value);
BOOLEAN Signals_GPIO_Get_State_Synchronized(PIN_GPIO_HW_STRUCT const * GPIO_ptr);
void Signals_GPIO_Register_Interrupt_Handler(PIN_GPIO_HW_STRUCT const * GPIO_ptr,
        INTERRUPT_CALLBACK_PTR callback_ptr, void * instance_ID);
# 60 "..\\..\\..\\Common\\Header/Signals.h" 2
# 1 "..\\..\\..\\Common\\Header/Signals_ADC_CM3.h" 1
# 55 "..\\..\\..\\Common\\Header/Signals_ADC_CM3.h"
typedef enum
{
    SIGNALS_ADC_CHANNEL_0,
    SIGNALS_ADC_CHANNEL_1,
    SIGNALS_ADC_CHANNEL_2,
    SIGNALS_ADC_CHANNEL_3,
    SIGNALS_ADC_CHANNEL_4,
    SIGNALS_ADC_CHANNEL_5,
    SIGNALS_ADC_CHANNEL_6,
    SIGNALS_ADC_CHANNEL_7,
    SIGNALS_ADC_CHANNEL_8,
    SIGNALS_ADC_CHANNEL_9,
    SIGNALS_ADC_CHANNEL_10,
    SIGNALS_ADC_CHANNEL_11,
    SIGNALS_ADC_CHANNEL_12,
    SIGNALS_ADC_CHANNEL_13,
    SIGNALS_ADC_CHANNEL_14,
    SIGNALS_ADC_CHANNEL_15,

    SIGNALS_ADC_TEMPERATURE_SENSOR,

    SIGNALS_ADC_CHANNEL_NUM_OF

} SIGNALS_ADC_CHANNEL_ENUM;







typedef struct
{
    F32 gain;

    F32 bias;

} SIGNAL_ADC_COEFF_STRUCT;







typedef struct
{
    U32 port;

    U8 pin;

    SIGNALS_ADC_CHANNEL_ENUM channel;

} PIN_ADC_HW_STRUCT;







void Signals_ADC_Initialize(void);
RETURN_TYPE Signals_ADC_Run_Gather(void);
void Signals_ADC_Configure_Pin(PIN_ADC_HW_STRUCT const * ADC_ptr,
        SIGNAL_ADC_COEFF_STRUCT const * coeff_ptr);
F32 Signals_ADC_Get_Analog_Sample(PIN_ADC_HW_STRUCT const * ADC_ptr);
U32 Signals_ADC_Get_Conversion_Faults_Count(void);
void Signals_ADC_Reset_Conversion_Faults_Count(void);
# 61 "..\\..\\..\\Common\\Header/Signals.h" 2
# 83 "..\\..\\..\\Common\\Header/Signals.h"
typedef enum
{
    SIGNALS_PWM_UNIT_0,
    SIGNALS_PWM_UNIT_1,
    SIGNALS_PWM_UNIT_2,
    SIGNALS_PWM_UNIT_3,

    SIGNALS_PWM_UNIT_NUM_OF,

    SIGNALS_PWM_NULL

} SIGNALS_PWM_UNIT_ENUM;
# 103 "..\\..\\..\\Common\\Header/Signals.h"
typedef struct
{
    U32 port;

    U8 pin;

    U32 pin_config;

} PIN_PERIPH_HW_STRUCT;







typedef struct
{
    PIN_PERIPH_HW_STRUCT GPIO;

    U32 pwm_out_bits;

} PIN_PWM_HW_STRUCT;





void Signals_Initialize_Old(void);
void Signals_In_Run_Gather(void);
BOOLEAN Signals_Next_IO(int bus_num);
# 66 "..\\..\\..\\Common\\Header\\User_Input.h" 2

# 1 "..\\..\\..\\Model\\Common\\Header\\Momentary_Switch.h" 1
# 42 "..\\..\\..\\Model\\Common\\Header\\Momentary_Switch.h"
# 1 "..\\..\\..\\Model\\Common\\Header/Persistent1Shot.h" 1
# 53 "..\\..\\..\\Model\\Common\\Header/Persistent1Shot.h"
typedef struct
{
    U32 P;
    BOOLEAN ic;
    BOOLEAN rising_edge;
    BOOLEAN falling_edge;

} PERSISTENT1SHOT_COEFF_STRUCT;







typedef struct
{
    BOOLEAN input;
    BOOLEAN reset;

} PERSISTENT1SHOT_INPUT_STRUCT;







typedef struct
{
    BOOLEAN output;

} PERSISTENT1SHOT_OUTPUT_STRUCT;







typedef struct
{
    BOOLEAN init;
    U32 iteration;
    BOOLEAN prev_input;

} PERSISTENT1SHOT_STATE_STRUCT;







typedef struct
{
    PERSISTENT1SHOT_COEFF_STRUCT *coeff_ptr;
    PERSISTENT1SHOT_STATE_STRUCT state;
    PERSISTENT1SHOT_INPUT_STRUCT input;
    PERSISTENT1SHOT_OUTPUT_STRUCT output;

} PERSISTENT1SHOT_STRUCT;





void Persistent1Shot_Initialize(PERSISTENT1SHOT_STRUCT *st_ptr, PERSISTENT1SHOT_COEFF_STRUCT *coeff_ptr);
void Persistent1Shot_Set_Input(PERSISTENT1SHOT_STRUCT *st_ptr, BOOLEAN input);
void Persistent1Shot_Set_Reset(PERSISTENT1SHOT_STRUCT *st_ptr, BOOLEAN reset);
void Persistent1Shot_Run(PERSISTENT1SHOT_STRUCT *st_ptr);
BOOLEAN Persistent1Shot_Get_Output(PERSISTENT1SHOT_STRUCT *st_ptr);
# 43 "..\\..\\..\\Model\\Common\\Header\\Momentary_Switch.h" 2
# 53 "..\\..\\..\\Model\\Common\\Header\\Momentary_Switch.h"
typedef struct
{
    U32 debounce_threshold;
    U32 sustain_threshold;

    PERSISTENT1SHOT_COEFF_STRUCT switch_opened_one_shot_coeff;

} MOMENTARY_SWITCH_COEFF_STRUCT;







typedef struct
{
    BOOLEAN input;

} MOMENTARY_SWITCH_INPUT_STRUCT;







typedef struct
{
    BOOLEAN output_pulsed;
    BOOLEAN output_sustained;

} MOMENTARY_SWITCH_OUTPUT_STRUCT;







typedef struct
{
    U32 counter;

    PERSISTENT1SHOT_STRUCT switch_opened_one_shot;

} MOMENTARY_SWITCH_STATE_STRUCT;







typedef struct
{
    MOMENTARY_SWITCH_COEFF_STRUCT *coeff_ptr;
    MOMENTARY_SWITCH_STATE_STRUCT state;
    MOMENTARY_SWITCH_INPUT_STRUCT input;
    MOMENTARY_SWITCH_OUTPUT_STRUCT output;

} MOMENTARY_SWITCH_STRUCT;





void Momentary_Switch_Initialize(MOMENTARY_SWITCH_STRUCT *st_ptr, MOMENTARY_SWITCH_COEFF_STRUCT *coeff_ptr);
void Momentary_Switch_Set_Input(MOMENTARY_SWITCH_STRUCT *st_ptr, BOOLEAN input);
void Momentary_Switch_Run(MOMENTARY_SWITCH_STRUCT *st_ptr);
BOOLEAN Momentary_Switch_Get_Output(MOMENTARY_SWITCH_STRUCT *st_ptr);
BOOLEAN Momentary_Switch_Get_Output_Pulsed(MOMENTARY_SWITCH_STRUCT *st_ptr);
BOOLEAN Momentary_Switch_Get_Output_Sustained(MOMENTARY_SWITCH_STRUCT *st_ptr);
# 68 "..\\..\\..\\Common\\Header\\User_Input.h" 2
# 1 "..\\..\\..\\Common\\Header/User_Input_HW.h" 1
# 77 "..\\..\\..\\Common\\Header/User_Input_HW.h"
typedef struct
{
    PIN_ADC_HW_STRUCT PCI_1;
    PIN_ADC_HW_STRUCT PCI_2;

} PCI_HW_STRUCT;







typedef enum
{
    LOOP_A,
    LOOP_B,


    LOOP_COUNT

} LOOP_ENUM;







typedef U8 USER_INPUT_FLAGS;
# 166 "..\\..\\..\\Common\\Header/User_Input_HW.h"
USER_INPUT_FLAGS User_Input_Run_HW(void);
void User_Input_Show_Flags(USER_INPUT_FLAGS cmdflags, char *tag);
# 69 "..\\..\\..\\Common\\Header\\User_Input.h" 2
# 81 "..\\..\\..\\Common\\Header\\User_Input.h"
typedef struct
{
    MOMENTARY_SWITCH_COEFF_STRUCT momentary_switch;

    MOMENTARY_SWITCH_COEFF_STRUCT momentary_switch_eng_dis;

} USER_INPUT_COEFF_STRUCT;







typedef enum
{
    UI_CMD_NONE,
    UI_CMD_MODE_CHANGE,
    UI_CMD_TRIM_DOWN,
    UI_CMD_TRIM_UP,
    UI_CMD_TRIM_RIGHT,
    UI_CMD_TRIM_LEFT,
    UI_CMD_ENGAGE_LOOP_1,
    UI_CMD_ENGAGE_LOOP_2,


    UI_NUMBER_OF_CMDS,


    UI_CMD_ERROR = 0x80

} USER_INPUT_CMD_ENUM;





void User_Input_Initialize(USER_INPUT_COEFF_STRUCT * user_input_coeff);
void User_Input_Run(void);
USER_INPUT_FLAGS User_Input_Get_Debounced_Cmd_Bitflags(void);
USER_INPUT_FLAGS User_Input_Get_Median_Cmd_Bitflags(void);
void User_Input_Set_Median_Cmd_Bitflags(USER_INPUT_FLAGS median);
USER_INPUT_FLAGS Median_Cmd_Bitflags(USER_INPUT_FLAGS button_left,
                                     USER_INPUT_FLAGS button_my,
                                     USER_INPUT_FLAGS button_right);
# 49 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "..\\..\\..\\Common\\Header\\Target.h" 1
# 74 "..\\..\\..\\Common\\Header\\Target.h"
typedef enum
{
    TARGET_MCPA,
    TARGET_MCPB,
    TARGET_MCPC,
    TARGET_ADPA,
    TARGET_ADPB,
    TARGET_ADPC,
    TARGET_PC,
    TARGET_REMOTE_NVRAM,
    TARGET_UNDEF

} TARGET_ID_ENUM;
# 95 "..\\..\\..\\Common\\Header\\Target.h"
typedef struct
{
    PIN_GPIO_HW_STRUCT bit_0;

    PIN_GPIO_HW_STRUCT bit_1;

} TARGET_ID_HW_STRUCT;
# 110 "..\\..\\..\\Common\\Header\\Target.h"
typedef union
{
    struct
    {

        PIN_GPIO_HW_STRUCT pwr_path_test;
        PIN_GPIO_HW_STRUCT brake_pwr_test;

    } schematic;

    struct
    {

        PIN_GPIO_HW_STRUCT pwr_path_BC_test_vote;
        PIN_GPIO_HW_STRUCT brake_test_vote;

    } MCPA;

    struct
    {

        PIN_GPIO_HW_STRUCT pwr_path_AC_test_vote;
        PIN_GPIO_HW_STRUCT brake_test_vote;

    } MCPB;

    struct
    {

        PIN_GPIO_HW_STRUCT pwr_path_A_test_vote;
        PIN_GPIO_HW_STRUCT pwr_path_B_test_vote;

    } MCPC;
} POST_HW_UNION;
# 154 "..\\..\\..\\Common\\Header\\Target.h"
typedef union
{
    struct
    {

        int diag_1;
        int diag_2;
        int diag_3;

    } schematic;

    struct
    {

        PIN_ADC_HW_STRUCT pwr_15V;
        PIN_ADC_HW_STRUCT pwr_3V3;
        PIN_ADC_HW_STRUCT pwr_external;

    } MCPA;

    struct
    {

        PIN_ADC_HW_STRUCT pwr_15V;
        PIN_ADC_HW_STRUCT pwr_3V3;
        PIN_ADC_HW_STRUCT pwr_external;

    } MCPB;

    struct
    {

        PIN_ADC_HW_STRUCT pwr_15V;
        PIN_ADC_HW_STRUCT pwr_3V3;
        PIN_ADC_HW_STRUCT pwr_brakes;

    } MCPC;

} TARGET_VOLTAGE_MONITORS_HW_UNION;
# 201 "..\\..\\..\\Common\\Header\\Target.h"
typedef struct
{
    TARGET_VOLTAGE_MONITORS_HW_UNION voltage_monitors;

    POST_HW_UNION self_test_enables;

    PIN_GPIO_HW_STRUCT power_failed;

    PIN_ADC_HW_STRUCT temperature_sensor;

} TARGET_MCP_HW_STRUCT;






void Target_Initialize(void);

void Target_GPIO_Initialize(void);

TARGET_ID_ENUM Target_Relative_MCP(U32 relative_location);

void Target_Set_Brake_Enable_Vote(BOOLEAN enabled);
void Target_Set_MCPA_Power_Disable_Vote(BOOLEAN enabled);
void Target_Set_MCPB_Power_Disable_Vote(BOOLEAN enabled);
void Target_Set_MCPC_Power_Disable_Vote(BOOLEAN enabled);

BOOLEAN Target_Power_Is_Good(void);

F32 Target_Get_Temperature(void);

TARGET_ID_ENUM Target_Get_Host_ID(void);
U32 Target_Get_System_Clock(void);

void Target_Halt(void);


    U8 const * Target_DEBUG_Get_Host_ID_String(void);
    U8 const * Target_DEBUG_Get_Branch_String(void);


void Target_Initialize_Clock(void);
void Target_Enable_Peripherals(void);
TARGET_ID_ENUM Target_Determine_Host_ID(void);
void Target_Enable_Interrupts(void);
# 50 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "..\\..\\..\\Common\\Header\\Messaging.h" 1
# 52 "..\\..\\..\\Common\\Header\\Messaging.h"
# 1 "..\\..\\..\\Common\\Header/Math_Utils.h" 1
# 86 "..\\..\\..\\Common\\Header/Math_Utils.h"
typedef U8 CKSUMTYPE;
# 378 "..\\..\\..\\Common\\Header/Math_Utils.h"
F32 PiRads(F32 value);
CKSUMTYPE Checksum_Compute(void * buffer, U16 length);
F32 Hex_To_Float(U32 hex);


F32 ZeroTo2PiRads(F32 angle);
# 53 "..\\..\\..\\Common\\Header\\Messaging.h" 2


# 1 "..\\..\\..\\Common\\Header/Fault_Mgmt.h" 1
# 84 "..\\..\\..\\Common\\Header/Fault_Mgmt.h"
# 1 "..\\..\\..\\MCP\\Header\\Fault_Defs.h" 1
# 68 "..\\..\\..\\MCP\\Header\\Fault_Defs.h"
typedef enum
{
# 81 "..\\..\\..\\MCP\\Header\\Fault_Defs.h"
    FORCE_CAUTION,
    FORCE_TONE,
    ADP_LOCKOUT,
    LOW_G,
    ACCELEROMETER_NOT_FOUND,
    ACCELEROMETER_BAD_READ,
    GYRO_NOT_FOUND,
    GYRO_BAD_READ,
    OAT_SENSOR_NOT_FOUND,
    OAT_SENSOR_BAD_READ,
    MAGNETOMETER_REMOTE_NOT_FOUND,
    MAGNETOMETER_REMOTE_BAD_READ,
    MAGNETOMETER_REMOTE_SELF_TEST,
    OVERRIDE_DETECTED,
    ROLL_RATE_MONITOR,
    PITCH_RATE_MONITOR,
    ROLL_ANGLE_MONITOR,
    PITCH_ANGLE_MONITOR,
    ROLL_ADP_COMMAND_MONITOR,
    PITCH_ADP_COMMAND_MONITOR,
    ROLL_ACTR_POSITION_MONITOR,
    PITCH_ACTR_POSITION_MONITOR,
    MCP_POST_FAULT,


    MCP_PWR_15V_NOT_OK,
    MCP_PWR_3V_NOT_OK,
    MCP_PWR_MCP_NOT_OFF,
    MCP_PWR_MCP_NOT_RESET,
    MCP_PWR_MCP_RESET_UNEXPECTED,
    MCP_PWR_MCP_C_BRAKE_VOLT_LOW,
    MCP_PWR_MCP_AB_BRAKE_VOLT_LOW,
    MCP_PWR_RESET_CHECK_FAILED,
    MCP_PWR_BRAKE_HOLD_LOW,
    MCP_PWR_MCP_A_BRAKE_NOT_LOW,
    MCP_PWR_MCP_B_BRAKE_NOT_LOW,
    MCP_PWR_MCP_A_NOT_FAILED,
    MCP_PWR_MCP_B_NOT_FAILED,
    MCP_PWR_SUPPLY_TEST,


    MCP_POST_ALARM,
    MCP_POST_ALARM_DEFAULT,
    MCP_POST_ALARM_LOWG,
    MCP_POST_ALARM_TONE,
    MCP_POST_ALARM_ADPLOCK,
    MCP_POST_ALARM_CAUTION,
    MCP_POST_ADP_OVERRIDE_ON,
    MCP_POST_ADP_OVERRIDE_OFF,


    MCP_ACT_UNKNOWN_FAULT,
    MCP_ACT_BRAKES_AH_PM1,
    MCP_ACT_BRAKES_AH_PM2,
    MCP_ACT_BRAKES_AH_RM1,
    MCP_ACT_BRAKES_AH_RM2,
    MCP_ACT_BRAKES_BH_PM1,
    MCP_ACT_BRAKES_BH_PM2,
    MCP_ACT_BRAKES_BH_RM1,
    MCP_ACT_BRAKES_BH_RM2,
    MCP_ACT_BRAKES_CH_PM1,
    MCP_ACT_BRAKES_CH_PM2,
    MCP_ACT_BRAKES_CH_RM1,
    MCP_ACT_BRAKES_CH_RM2,
    MCP_ACT_MCP_A_CIRC_AH_AL_PM1,
    MCP_ACT_MCP_A_CIRC_AH_AL_PM2,
    MCP_ACT_MCP_A_CIRC_AH_AL_RM1,
    MCP_ACT_MCP_A_CIRC_AH_AL_RM2,
    MCP_ACT_MCP_A_CIRC_AH_BL_PM1,
    MCP_ACT_MCP_A_CIRC_AH_BL_RM1,
    MCP_ACT_MCP_A_CIRC_AH_CL_PM1,
    MCP_ACT_MCP_A_CIRC_AH_CL_RM1,
    MCP_ACT_MCP_A_CIRC_AH_PM1,
    MCP_ACT_MCP_A_CIRC_AH_PM2,
    MCP_ACT_MCP_A_CIRC_AH_RM1,
    MCP_ACT_MCP_A_CIRC_AH_RM2,
    MCP_ACT_MCP_A_CIRC_AL_BH_PM1,
    MCP_ACT_MCP_A_CIRC_AL_BH_RM1,
    MCP_ACT_MCP_A_CIRC_AL_CH_PM1,
    MCP_ACT_MCP_A_CIRC_AL_CH_RM1,
    MCP_ACT_MCP_A_CIRC_AL_PM1,
    MCP_ACT_MCP_A_CIRC_AL_PM2,
    MCP_ACT_MCP_A_CIRC_AL_RM1,
    MCP_ACT_MCP_A_CIRC_AL_RM2,
    MCP_ACT_MCP_A_CIRC_BH_BL_PM1,
    MCP_ACT_MCP_A_CIRC_BH_BL_PM2,
    MCP_ACT_MCP_A_CIRC_BH_BL_RM1,
    MCP_ACT_MCP_A_CIRC_BH_BL_RM2,
    MCP_ACT_MCP_A_CIRC_BH_CL_PM1,
    MCP_ACT_MCP_A_CIRC_BH_CL_RM1,
    MCP_ACT_MCP_A_CIRC_BH_PM1,
    MCP_ACT_MCP_A_CIRC_BH_PM2,
    MCP_ACT_MCP_A_CIRC_BH_RM1,
    MCP_ACT_MCP_A_CIRC_BH_RM2,
    MCP_ACT_MCP_A_CIRC_BL_CH_PM1,
    MCP_ACT_MCP_A_CIRC_BL_CH_RM1,
    MCP_ACT_MCP_A_CIRC_BL_PM1,
    MCP_ACT_MCP_A_CIRC_BL_PM2,
    MCP_ACT_MCP_A_CIRC_BL_RM1,
    MCP_ACT_MCP_A_CIRC_BL_RM2,
    MCP_ACT_MCP_A_CIRC_CH_CL_PM1,
    MCP_ACT_MCP_A_CIRC_CH_CL_PM2,
    MCP_ACT_MCP_A_CIRC_CH_CL_RM1,
    MCP_ACT_MCP_A_CIRC_CH_CL_RM2,
    MCP_ACT_MCP_A_CIRC_CH_PM1,
    MCP_ACT_MCP_A_CIRC_CH_PM2,
    MCP_ACT_MCP_A_CIRC_CH_RM1,
    MCP_ACT_MCP_A_CIRC_CH_RM2,
    MCP_ACT_MCP_A_CIRC_CL_PM1,
    MCP_ACT_MCP_A_CIRC_CL_PM2,
    MCP_ACT_MCP_A_CIRC_CL_RM1,
    MCP_ACT_MCP_A_CIRC_CL_RM2,
    MCP_ACT_MCP_A_CIRC_NONE_PM1,
    MCP_ACT_MCP_A_CIRC_NONE_PM2,
    MCP_ACT_MCP_A_CIRC_NONE_RM1,
    MCP_ACT_MCP_A_CIRC_NONE_RM2,
    MCP_ACT_MCP_A_WIND_AH_BL_PM2,
    MCP_ACT_MCP_A_WIND_AH_BL_RM2,
    MCP_ACT_MCP_A_WIND_AH_CL_PM2,
    MCP_ACT_MCP_A_WIND_AH_CL_RM2,
    MCP_ACT_MCP_A_WIND_AL_BH_PM2,
    MCP_ACT_MCP_A_WIND_AL_BH_RM2,
    MCP_ACT_MCP_A_WIND_AL_CH_PM2,
    MCP_ACT_MCP_A_WIND_AL_CH_RM2,
    MCP_ACT_MCP_A_WIND_BH_CL_PM2,
    MCP_ACT_MCP_A_WIND_BH_CL_RM2,
    MCP_ACT_MCP_A_WIND_BL_CH_PM2,
    MCP_ACT_MCP_A_WIND_BL_CH_RM2,
    MCP_ACT_MCP_B_CIRC_AH_AL_PM1,
    MCP_ACT_MCP_B_CIRC_AH_AL_PM2,
    MCP_ACT_MCP_B_CIRC_AH_AL_RM1,
    MCP_ACT_MCP_B_CIRC_AH_AL_RM2,
    MCP_ACT_MCP_B_CIRC_AH_BL_PM2,
    MCP_ACT_MCP_B_CIRC_AH_BL_RM2,
    MCP_ACT_MCP_B_CIRC_AH_CL_PM2,
    MCP_ACT_MCP_B_CIRC_AH_CL_RM2,
    MCP_ACT_MCP_B_CIRC_AH_PM1,
    MCP_ACT_MCP_B_CIRC_AH_PM2,
    MCP_ACT_MCP_B_CIRC_AH_RM1,
    MCP_ACT_MCP_B_CIRC_AH_RM2,
    MCP_ACT_MCP_B_CIRC_AL_BH_PM2,
    MCP_ACT_MCP_B_CIRC_AL_BH_RM2,
    MCP_ACT_MCP_B_CIRC_AL_CH_PM2,
    MCP_ACT_MCP_B_CIRC_AL_CH_RM2,
    MCP_ACT_MCP_B_CIRC_AL_PM1,
    MCP_ACT_MCP_B_CIRC_AL_PM2,
    MCP_ACT_MCP_B_CIRC_AL_RM1,
    MCP_ACT_MCP_B_CIRC_AL_RM2,
    MCP_ACT_MCP_B_CIRC_BH_BL_PM1,
    MCP_ACT_MCP_B_CIRC_BH_BL_PM2,
    MCP_ACT_MCP_B_CIRC_BH_BL_RM1,
    MCP_ACT_MCP_B_CIRC_BH_BL_RM2,
    MCP_ACT_MCP_B_CIRC_BH_CL_PM2,
    MCP_ACT_MCP_B_CIRC_BH_CL_RM2,
    MCP_ACT_MCP_B_CIRC_BH_PM1,
    MCP_ACT_MCP_B_CIRC_BH_PM2,
    MCP_ACT_MCP_B_CIRC_BH_RM1,
    MCP_ACT_MCP_B_CIRC_BH_RM2,
    MCP_ACT_MCP_B_CIRC_BL_CH_PM2,
    MCP_ACT_MCP_B_CIRC_BL_CH_RM2,
    MCP_ACT_MCP_B_CIRC_BL_PM1,
    MCP_ACT_MCP_B_CIRC_BL_PM2,
    MCP_ACT_MCP_B_CIRC_BL_RM1,
    MCP_ACT_MCP_B_CIRC_BL_RM2,
    MCP_ACT_MCP_B_CIRC_CH_CL_PM1,
    MCP_ACT_MCP_B_CIRC_CH_CL_PM2,
    MCP_ACT_MCP_B_CIRC_CH_CL_RM1,
    MCP_ACT_MCP_B_CIRC_CH_CL_RM2,
    MCP_ACT_MCP_B_CIRC_CH_PM1,
    MCP_ACT_MCP_B_CIRC_CH_PM2,
    MCP_ACT_MCP_B_CIRC_CH_RM1,
    MCP_ACT_MCP_B_CIRC_CH_RM2,
    MCP_ACT_MCP_B_CIRC_CL_PM1,
    MCP_ACT_MCP_B_CIRC_CL_PM2,
    MCP_ACT_MCP_B_CIRC_CL_RM1,
    MCP_ACT_MCP_B_CIRC_CL_RM2,
    MCP_ACT_MCP_B_CIRC_NONE_PM1,
    MCP_ACT_MCP_B_CIRC_NONE_PM2,
    MCP_ACT_MCP_B_CIRC_NONE_RM1,
    MCP_ACT_MCP_B_CIRC_NONE_RM2,
    MCP_ACT_MCP_B_WIND_AH_BL_PM1,
    MCP_ACT_MCP_B_WIND_AH_BL_RM1,
    MCP_ACT_MCP_B_WIND_AH_CL_PM1,
    MCP_ACT_MCP_B_WIND_AH_CL_RM1,
    MCP_ACT_MCP_B_WIND_AL_BH_PM1,
    MCP_ACT_MCP_B_WIND_AL_BH_RM1,
    MCP_ACT_MCP_B_WIND_AL_CH_PM1,
    MCP_ACT_MCP_B_WIND_AL_CH_RM1,
    MCP_ACT_MCP_B_WIND_BH_CL_PM1,
    MCP_ACT_MCP_B_WIND_BH_CL_RM1,
    MCP_ACT_MCP_B_WIND_BL_CH_PM1,
    MCP_ACT_MCP_B_WIND_BL_CH_RM1,
    MCP_ACT_MCP_C_CIRC_AH_AL_PM1,
    MCP_ACT_MCP_C_CIRC_AH_AL_PM2,
    MCP_ACT_MCP_C_CIRC_AH_AL_RM1,
    MCP_ACT_MCP_C_CIRC_AH_AL_RM2,
    MCP_ACT_MCP_C_CIRC_AH_PM1,
    MCP_ACT_MCP_C_CIRC_AH_PM2,
    MCP_ACT_MCP_C_CIRC_AH_RM1,
    MCP_ACT_MCP_C_CIRC_AH_RM2,
    MCP_ACT_MCP_C_CIRC_AL_PM1,
    MCP_ACT_MCP_C_CIRC_AL_PM2,
    MCP_ACT_MCP_C_CIRC_AL_RM1,
    MCP_ACT_MCP_C_CIRC_AL_RM2,
    MCP_ACT_MCP_C_CIRC_BH_BL_PM1,
    MCP_ACT_MCP_C_CIRC_BH_BL_PM2,
    MCP_ACT_MCP_C_CIRC_BH_BL_RM1,
    MCP_ACT_MCP_C_CIRC_BH_BL_RM2,
    MCP_ACT_MCP_C_CIRC_BH_PM1,
    MCP_ACT_MCP_C_CIRC_BH_PM2,
    MCP_ACT_MCP_C_CIRC_BH_RM1,
    MCP_ACT_MCP_C_CIRC_BH_RM2,
    MCP_ACT_MCP_C_CIRC_BL_PM1,
    MCP_ACT_MCP_C_CIRC_BL_PM2,
    MCP_ACT_MCP_C_CIRC_BL_RM1,
    MCP_ACT_MCP_C_CIRC_BL_RM2,
    MCP_ACT_MCP_C_CIRC_CH_CL_PM1,
    MCP_ACT_MCP_C_CIRC_CH_CL_PM2,
    MCP_ACT_MCP_C_CIRC_CH_CL_RM1,
    MCP_ACT_MCP_C_CIRC_CH_CL_RM2,
    MCP_ACT_MCP_C_CIRC_CH_PM1,
    MCP_ACT_MCP_C_CIRC_CH_PM2,
    MCP_ACT_MCP_C_CIRC_CH_RM1,
    MCP_ACT_MCP_C_CIRC_CH_RM2,
    MCP_ACT_MCP_C_CIRC_CL_PM1,
    MCP_ACT_MCP_C_CIRC_CL_PM2,
    MCP_ACT_MCP_C_CIRC_CL_RM1,
    MCP_ACT_MCP_C_CIRC_CL_RM2,
    MCP_ACT_MCP_C_CIRC_NONE_PM1,
    MCP_ACT_MCP_C_CIRC_NONE_PM2,
    MCP_ACT_MCP_C_CIRC_NONE_RM1,
    MCP_ACT_MCP_C_CIRC_NONE_RM2,
    MCP_ACT_MCP_C_WIND_AH_BL_PM1,
    MCP_ACT_MCP_C_WIND_AH_BL_PM2,
    MCP_ACT_MCP_C_WIND_AH_BL_RM1,
    MCP_ACT_MCP_C_WIND_AH_BL_RM2,
    MCP_ACT_MCP_C_WIND_AH_CL_PM1,
    MCP_ACT_MCP_C_WIND_AH_CL_PM2,
    MCP_ACT_MCP_C_WIND_AH_CL_RM1,
    MCP_ACT_MCP_C_WIND_AH_CL_RM2,
    MCP_ACT_MCP_C_WIND_AL_BH_PM1,
    MCP_ACT_MCP_C_WIND_AL_BH_PM2,
    MCP_ACT_MCP_C_WIND_AL_BH_RM1,
    MCP_ACT_MCP_C_WIND_AL_BH_RM2,
    MCP_ACT_MCP_C_WIND_AL_CH_PM1,
    MCP_ACT_MCP_C_WIND_AL_CH_PM2,
    MCP_ACT_MCP_C_WIND_AL_CH_RM1,
    MCP_ACT_MCP_C_WIND_AL_CH_RM2,
    MCP_ACT_MCP_C_WIND_BH_CL_PM1,
    MCP_ACT_MCP_C_WIND_BH_CL_PM2,
    MCP_ACT_MCP_C_WIND_BH_CL_RM1,
    MCP_ACT_MCP_C_WIND_BH_CL_RM2,
    MCP_ACT_MCP_C_WIND_BL_CH_PM1,
    MCP_ACT_MCP_C_WIND_BL_CH_PM2,
    MCP_ACT_MCP_C_WIND_BL_CH_RM1,
    MCP_ACT_MCP_C_WIND_BL_CH_RM2,


    MCP_HALL_MOTOR_ROTATE_FAIL,
    MCP_HALL_MCP_SENSOR_BLOCKED,


    MCP_MISC_CHECK_FLASH_CRC,
    MCP_MISC_ACCELEROMETERS_STIM,
    MCP_MISC_GYROS_STIM,


    GYRO_SAMPLE_RATE,
    ACCEL_SAMPLE_RATE,
    MAG_SAMPLE_RATE,


    MAGNETOMETER_BAD_DATA,
    AIRSPEED_BAD_DATA,
    ALTITUDE_BAD_DATA,


    ADP_MCP_COMM,
    MCP_ADP_COMM,
    IPC_RING_L1,
    IPC_RING_L3,
    I2C_INTERRUPT_ERROR,
    UART_ERROR,


    I2C_TIMEOUT_LOG_EVENT,
    I2C_TIMEOUT_SYSTEM_STATE,
    SYSTEM_LOG_BAD_CRC,
    SYSTEM_STATE_BAD_CRC,


    SUSTAINED_MOTOR_CURRENT_PMA,
    SUSTAINED_MOTOR_CURRENT_PMB,
    SUSTAINED_MOTOR_CURRENT_RMA,
    SUSTAINED_MOTOR_CURRENT_RMB,
    HALL_SENSORS_PMA,
    HALL_SENSORS_PMB,
    HALL_SENSORS_RMA,
    HALL_SENSORS_RMB,
    POSITION_DEVIATION_ROLL,
    POSITION_DEVIATION_PITCH,
    INVALID_MOTOR_SELECT,
    TOO_MANY_BLDC_ISRS,
    HALL_TEST_PMA,
    HALL_TEST_PMB,
    HALL_TEST_RMA,
    HALL_TEST_RMB,


    CLUTCH_MOVE_TIMEOUT,
    CLUTCH_ENGAGED_INV_STATE,
    CLUTCH_DISENGAGED_INV_STATE,
    CLUTCH_MTD_INV_STATE,
    CLUTCH_MTE_INV_STATE,
    CLUTCH_READBACK_ERROR,
    CLUTCH_STATE_DISAGREEMENT,
    CLUTCH_ENGAGED_AT_STARTUP,


    USER_INPUT_BUTTON,
    USER_INPUT_LOOP_A_SHORTED,
    USER_INPUT_LOOP_A_OPEN,
    USER_INPUT_LOOP_B_SHORTED,
    USER_INPUT_LOOP_B_OPEN,


    MULTIPLE_LEVEL_THREE_FAULTS,
    IBIT_TIMEOUT_FAULT,
    IBIT_SWITCH_FAILED,
    MCP_INVALID_STATE,
    IBIT_INVALID_STATE,
    MCP_INVALID_STATE_TRANSITION,
    IBIT_INVALID_STATE_TRANSITION,
    WATCHDOG_TEST_FAIL,
    WD_RESET_OCCURED,
    FRAME_TOO_LONG,
    FRAME_TOO_SHORT,
    SIGNALS_ADC_GATHER,


    ADAHRS_NORMALIZATION,
    ADAHRS_ZERO_RATE_BIAS,
    ADAHRS_EULER_ANGLE_TRANSIENT,

    FRAM_BAD_READ,
    FRAM_BAD_WRITE,


    ADP_LEVEL_ONE,
    ADP_LEVEL_TWO,
    ADP_LEVEL_THREE,

    SUSTAINED_MOTOR_PWM_PMA,
    SUSTAINED_MOTOR_PWM_PMB,
    SUSTAINED_MOTOR_PWM_RMA,
    SUSTAINED_MOTOR_PWM_RMB,

    MCP_CRC_MISMATCH_L1,

    MCP_BRD_SERIAL_NUMBER_MISMATCH,
    ADP_BRD_SERIAL_NUMBER_MISMATCH,
    ADP_REMOTE_MAG_SERIAL_NUMBER_MISMATCH,

    NUM_FAULTS

} FAULT_ENUM;
# 85 "..\\..\\..\\Common\\Header/Fault_Mgmt.h" 2
# 108 "..\\..\\..\\Common\\Header/Fault_Mgmt.h"
typedef U8 FAULT_MGMT_STATUS;







typedef enum
{






    FAULT_LEVEL_ONE,
    FAULT_LEVEL_TWO,
    FAULT_LEVEL_THREE,

    NUM_FAULT_LEVELS

} FAULT_LEVEL_ENUM;







typedef struct
{

    FAULT_LEVEL_ENUM level;


    U8 counter_limit;


    U8 count;


    BOOLEAN cleared_on_disengage;


    BOOLEAN set;

} FAULT_DATA_STRUCT;






void Fault_Mgmt_Initialize(void);
void Fault_Mgmt_Run(void);


    void Fault_Mgmt_Set_Fault_Show_Enums(FAULT_ENUM fault_type, char *fault_name);



void Fault_Mgmt_Reset_Fault_Counter(FAULT_ENUM fault_type);
void Fault_Mgmt_Decrement_Fault_Counter(FAULT_ENUM fault_type);
U8 Fault_Mgmt_Get_Fault_Counter(FAULT_ENUM fault_type);
void Fault_Mgmt_Clear_Fault(FAULT_ENUM fault_type);
BOOLEAN Fault_Mgmt_Is_Fault_Set(FAULT_ENUM fault_type);
BOOLEAN Fault_Mgmt_Is_Fault_Level_Set(FAULT_LEVEL_ENUM fault_level);
FAULT_LEVEL_ENUM Fault_Mgmt_Get_Level_Of_Fault(FAULT_ENUM fault_type);

void Fault_Mgmt_Notify_Of_Engage_State_Change(BOOLEAN engaged);
void Fault_Mgmt_Initialize_Fault_Data_Struct(FAULT_DATA_STRUCT * fault_data,
                                             FAULT_LEVEL_ENUM fault_level,
                                             U8 counter_limit,
                                             BOOLEAN cleared_on_disengage);


void Fault_Mgmt_Initialize_Defs(void);
void Fault_Mgmt_Handle_Fault(FAULT_ENUM fault_type);
FAULT_ENUM Fault_Mgmt_Get_Most_Recent_Fault(void);
# 56 "..\\..\\..\\Common\\Header\\Messaging.h" 2
# 1 "..\\..\\..\\Common\\Header/Annunciators.h" 1
# 104 "..\\..\\..\\Common\\Header/Annunciators.h"
typedef struct
{
    F32 on_duration_seconds;
    F32 off_duration_seconds;
    U32 num_repeats;
    BOOLEAN end_state;

} ANNUNCIATORS_PATTERN_COEFF_STRUCT;
# 120 "..\\..\\..\\Common\\Header/Annunciators.h"
typedef U8 ANNUNCIATORS_MCP_DISCRETES;







typedef U8 ANNUNCIATORS_ENUM;







typedef U8 PATTERN_PRESETS_ENUM;



struct ANNUNCIATOR_EXTENSION_STRUCT;






void Annunciators_Start_Pattern_Preset(ANNUNCIATORS_ENUM annunciator, PATTERN_PRESETS_ENUM preset);
void Annunciators_Stop_Pattern(ANNUNCIATORS_ENUM annunciator);
BOOLEAN Annunciators_Is_Running_Pattern(ANNUNCIATORS_ENUM annunciator);


struct ANNUNCIATOR_EXTENSION_STRUCT * Annunciators_Get_Annunciator_Extension(ANNUNCIATORS_ENUM annunciator);
const ANNUNCIATORS_PATTERN_COEFF_STRUCT * Annunciators_Get_Pattern_Coeff(PATTERN_PRESETS_ENUM pattern);

void Annunciators_Run(void);
void Annunciators_Set_State(ANNUNCIATORS_ENUM annunciator, BOOLEAN asserted);
# 57 "..\\..\\..\\Common\\Header\\Messaging.h" 2
# 84 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef enum
    {
        MSG_ID_NULL,
        MSG_ID_ADP2MCP,
        MSG_ID_MCP2ADP,
        MSG_ID_ADP2MX,
        MSG_ID_MX2ADP,
        MSG_ID_MCP2MCP_FRAME_START,
        MSG_ID_MCP2MCP_SIGNALS,
        MSG_ID_MCP2MCP,
        MSG_ID_MCP2MX,
        MSG_ID_MX2MCP,
        MSG_ID_XP2HAP,
        MSG_ID_MCP2XP,
        MSG_ID_MCP2TELEM,
        MSG_ID_ADP2TELEM,
        MSG_ID_AP2MX,
        MSG_ID_GENERIC_FLOATS,

        MSG_ID_NUMBER
    } MSG_ID_ENUM;
# 114 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef enum
    {
        MCP2ADP_PACKET_FLIGHT_DATA,
        MCP2ADP_PACKET_POST_DATA,
        MCP2ADP_PACKET_MX_VOTE,

        MCP2ADP_PACKET_LAST

    } MCP2ADP_PACKET_TYPE;
# 132 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef enum
    {
        ADP2MCP_PACKET_FLIGHT_DATA,
        ADP2MCP_PACKET_POST_DATA,



        ADP2MCP_PACKET_LAST

    } ADP2MCP_PACKET_TYPE;
# 151 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef enum
    {



        IBIT_NEVER,
        IBIT_NONE,
        IBIT_REQUESTED,
        IBIT_GRANTED,
        IBIT_SUCCESS,
        IBIT_TIMEOUT,

        NUM_IBIT_STATE

    } IBIT_STATE_ENUM;
# 174 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef enum
    {



        MCP_NEVER,
        MCP_MX,
        MCP_STARTUP_CHECK,
        MCP_IBIT,
        MCP_IBIT_TIMEOUT,
        MCP_POST,
        MCP_RUN,

        NUM_MCP_STATE

    } MCP_STATE_ENUM;
# 199 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef struct
    {
        ADP2MCP_PACKET_TYPE packet_type;
    } PACKET_TYPE_STRUCT;
# 211 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef struct
    {
        ADP2MCP_PACKET_TYPE packet_type;
        F32 Voltage_15V_A;
        F32 Voltage_15V_B;
        F32 Voltage_15V_ORed;
        F32 Voltage_15V_Backup;
        F32 Voltage_3V3;
        F32 External_Dimmer;
        F32 Current_A;
        F32 Current_B;
        F32 Current_C;
        F32 Tone;
        BOOLEAN MCP_Force_Caution;
        BOOLEAN MCP_Force_Tone;
        BOOLEAN MCP_ADP_Lockout;
        BOOLEAN MCP_Low_G;
        BOOLEAN PWR_GOOD_TST_EN;
        BOOLEAN test_button;
        BOOLEAN IBIT_Granted;
        BOOLEAN IBIT_held_since_startup;
        U32 adp_board_serial_number0;
        U32 adp_board_serial_number1;

    } POST_DATA_STRUCT;
# 244 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef struct
    {
        MCP2ADP_PACKET_TYPE packet_type;
        U32 frame_number;
        BOOLEAN vote;
        BOOLEAN valid;

    } MSG_MX_VOTE_STRUCT;
# 260 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef struct
    {
        ADP2MCP_PACKET_TYPE packet_type;
        F32 differential_pressure[(2)];
        F32 static_pressure[(2)];
        CYCLIC_STRUCT command;
        ANNUNCIATORS_MCP_DISCRETES mcp_discretes;
        FAULT_MGMT_STATUS adp_fault_status;
        TARGET_ID_ENUM target;
        U32 frame;

    } MSG_ADP2MCP_STRUCT;
# 282 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef union
    {
        PACKET_TYPE_STRUCT packet_base;
        MSG_ADP2MCP_STRUCT flight_data;
        POST_DATA_STRUCT POST_data;
        MSG_MX_VOTE_STRUCT mx_vote;

    } MSG_ADP2MCP_UNION;
# 300 "..\\..\\..\\Common\\Header\\Messaging.h"
    typedef struct
    {
        MCP2ADP_PACKET_TYPE packet_type;
        EULER_ANGLES eulers;
        EULER_RATES euler_rates;
        F32 OAT;
        F32 IAS;
        F32 TAS;
        F32 longitudinal_accel;
        F32 altitude;
        F32 vertical_rate;
        U32 frame_number;
        ANNUNCIATORS_MCP_DISCRETES mcp_discretes;
        U32 cmd_bitflags;
        IBIT_STATE_ENUM ibit_state;
        BOOLEAN phi_valid;
        BOOLEAN theta_valid;
        BOOLEAN run_outer_loop;
        BOOLEAN force_hdg_light_on;
        BOOLEAN engaged;
        BOOLEAN power_good;
        BOOLEAN system_operational;
        BOOLEAN mx_vote;

    } MSG_MCP2ADP_STRUCT;
# 51 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "..\\..\\..\\MCP\\Header/Target_Software_Defs_MCP.h" 1
# 52 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h" 2
# 88 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h"
typedef enum
{
    MCP_FLAG_UAR_MODE = 0,
    MCP_FLAG_PILOT_OVERRIDE,
    MCP_FLAG_AUTOPILOT_ENGAGED,
    MCP_FLAG_AUTOPILOT_READY,

    MCP_FLAG_ROLL_RATE_FAIL,
    MCP_FLAG_ROLL_ADP_CMD_FAIL,
    MCP_FLAG_ROLL_ACT_POS_FAIL,
    MCP_FLAG_ROLL_ATT_FAIL,

    MCP_FLAG_PITCH_RATE_FAIL,
    MCP_FLAG_PITCH_ADP_CMD_FAIL,
    MCP_FLAG_PITCH_ACT_POS_FAIL,
    MCP_FLAG_PITCH_ATT_FAIL,

    MCP_FLAG_ROLL_SERVOLOOP_CURRSATLL,
    MCP_FLAG_ROLL_SERVOLOOP_CURRSATUL,
    MCP_FLAG_ROLL_SERVOLOOP_PLSAT,
    MCP_FLAG_ROLL_SERVOLOOP_PLINV,
    MCP_FLAG_ROLL_SERVOLOOP_RLSAT,

    MCP_FLAG_PITCH_SERVOLOOP_CURRSATLL,
    MCP_FLAG_PITCH_SERVOLOOP_CURRSATUL,
    MCP_FLAG_PITCH_SERVOLOOP_PLSAT,
    MCP_FLAG_PITCH_SERVOLOOP_PLINV,
    MCP_FLAG_PITCH_SERVOLOOP_RLSAT,

    MCP_FLAG_CPD_INPUT,
    MCP_FLAG_VIDEO_SYNC_LIGHT_OUTPUT,

    MCP_FLAG_COMBINED_FAIL_STATUS


} MCP_FLAGS_ENUM;
# 132 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h"
typedef struct
{
    U32 framenumber;


    EULER_ANGLES eulers;
    VECTOR3 mags;
    VECTOR3 rates;
    VECTOR3 accels;
    EULER_RATES euler_rates;


    CYCLIC_STRUCT actuator_positions;
    CYCLIC_STRUCT actuator_commands;
    CYCLIC_STRUCT motor_A_current;
    CYCLIC_STRUCT motor_B_current;
    CYCLIC_STRUCT actuator_mvc;
# 157 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h"
    F32 IAS;
    F32 TAS;
    F32 baro_altitude;
    F32 oat;


    U32 latest_fault;
    U8 button_states;
    union {
        U32 flags;
        struct {
            U32 UAR_Mode : 1;
            U32 Pilot_Override : 1;
            U32 Autopilot_Engaged : 1;
            U32 Autopilot_Ready : 1;

            U32 Roll_Rate_Fail : 1;
            U32 Roll_ADP_Cmd_Fail : 1;
            U32 Roll_ACT_POS_Fail : 1;
            U32 Roll_ATT_Fail : 1;

            U32 Pitch_Rate_Fail : 1;
            U32 Pitch_ADP_Cmd_Fail : 1;
            U32 Pitch_ACT_Pos_Fail : 1;
            U32 Pitch_ATT_Fail : 1;

            U32 Roll_Servoloop_CurrSatLL : 1;
            U32 Roll_Servoloop_CurrSatUL : 1;
            U32 Roll_Servoloop_PLSat : 1;
            U32 Roll_Servoloop_PLInv : 1;
            U32 Roll_Servoloop_RLSat : 1;

            U32 Pitch_Servoloop_CurrSatLL : 1;
            U32 Pitch_Servoloop_CurrSatUL : 1;
            U32 Pitch_Servoloop_PLSat : 1;
            U32 Pitch_Servoloop_PLInv : 1;
            U32 Pitch_Servoloop_RLSat : 1;

            U32 CPD_Input : 1;
            U32 Video_Sync_Light_Output : 1;

            U32 Combined_Fail_Status : 1;
        } flags1;
    } u;
    U32 flags2;

} TELEMETRY_LOG_STRUCT;
# 239 "..\\..\\..\\MCP\\Header\\Telemetry_Log.h"
RETURN_TYPE Telemetry_Log_Run(void);

TELEMETRY_LOG_STRUCT * Telemetry_Log_Get_Telem_Structure();
void Telemetry_Log_Set_IL_Monitors(U32 monitor_flags);
void Telemetry_Log_Set_Servo_Loop_Flags(U32 servo_loop_flags);
void Telemetry_Log_Set_Differential_Pressures(F32 value, U32 sensor);
void Telemetry_Log_Enable_Raw_Data(BOOLEAN enable);
# 5 "main_MCP.c" 2
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header\\MCP.h" 1
# 62 "..\\..\\..\\Model\\Inner_Loop\\Header\\MCP.h"
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header/Cyclic_Feedback.h" 1
# 63 "..\\..\\..\\Model\\Inner_Loop\\Header/Cyclic_Feedback.h"
# 1 "..\\..\\..\\Model\\Common\\Header\\Switch_2nd_Order.h" 1
# 43 "..\\..\\..\\Model\\Common\\Header\\Switch_2nd_Order.h"
# 1 "..\\..\\..\\Model\\Common\\Header/Switch_Common.h" 1
# 59 "..\\..\\..\\Model\\Common\\Header/Switch_Common.h"
typedef struct
{

    PERSISTENT1SHOT_COEFF_STRUCT transition_one_shot_coeff;

} SWITCH_COMMON_COEFF_STRUCT;







typedef struct
{
    PERSISTENT1SHOT_STRUCT transition_one_shot;
    F32 output_previous;
    F32 transition_deviation_latched;
    F32 selected_input;

} SWITCH_COMMON_STATE_STRUCT;







typedef struct
{
    SWITCH_COMMON_COEFF_STRUCT *coeff_ptr;
    SWITCH_COMMON_STATE_STRUCT state;

} SWITCH_COMMON_STRUCT;





void Switch_Common_Initialize (SWITCH_COMMON_STRUCT *st_ptr, SWITCH_COMMON_COEFF_STRUCT *coeff_ptr);
void Switch_Common_Run_Start (SWITCH_COMMON_STRUCT *st_ptr, F32 u1, F32 u2, BOOLEAN switch_flag);
F32 Switch_Common_Run_Finish (SWITCH_COMMON_STRUCT *st_ptr, F32 deviation_percentage);
BOOLEAN Switch_Common_Switch_Occurred(SWITCH_COMMON_STRUCT *st_ptr);
# 44 "..\\..\\..\\Model\\Common\\Header\\Switch_2nd_Order.h" 2
# 1 "..\\..\\..\\Model\\Common\\Header/ReIntICH.h" 1
# 53 "..\\..\\..\\Model\\Common\\Header/ReIntICH.h"
typedef struct
{
    F32 K_Ts;

} REINTICH_COEFF_STRUCT;






typedef struct
{
    F32 IC;
    F32 input;
    BOOLEAN run;
    BOOLEAN hold;

} REINTICH_INPUT_STRUCT;







typedef struct
{
    F32 output;

} REINTICH_OUTPUT_STRUCT;







typedef struct
{
    F32 delay;
    BOOLEAN reset_on_init;

} REINTICH_STATE_STRUCT;







typedef struct
{
    REINTICH_COEFF_STRUCT *coeff;
    REINTICH_STATE_STRUCT state;
    REINTICH_INPUT_STRUCT input;
    REINTICH_OUTPUT_STRUCT output;

} REINTICH_STRUCT;





void ReIntICH_Initialize(REINTICH_STRUCT *st_ptr, REINTICH_COEFF_STRUCT *coeff);
void ReIntICH_Set_Input(REINTICH_STRUCT *st_ptr, F32 input);
void ReIntICH_Set_IC(REINTICH_STRUCT *st_ptr, F32 ic);
void ReIntICH_Set_Hold(REINTICH_STRUCT *st_ptr, BOOLEAN hold);
void ReIntICH_Set_Run(REINTICH_STRUCT *st_ptr, BOOLEAN run);
F32 ReIntICH_Get_Output(REINTICH_STRUCT *st_ptr);
void ReIntICH_Run(REINTICH_STRUCT *st_ptr);
# 45 "..\\..\\..\\Model\\Common\\Header\\Switch_2nd_Order.h" 2
# 55 "..\\..\\..\\Model\\Common\\Header\\Switch_2nd_Order.h"
typedef struct
{
    SWITCH_COMMON_COEFF_STRUCT common_coeff;
    REINTICH_COEFF_STRUCT first_integrator_coeff;
    REINTICH_COEFF_STRUCT second_integrator_coeff;

} SWITCH_SECOND_ORDER_COEFF_STRUCT;







typedef struct
{
    F32 input_one;
    F32 input_two;

    BOOLEAN switch_flag;

} SWITCH_SECOND_ORDER_INPUT_STRUCT;







typedef struct
{
    F32 output;

} SWITCH_SECOND_ORDER_OUTPUT_STRUCT;







typedef struct
{
    SWITCH_COMMON_STRUCT common;
    REINTICH_STRUCT first_integrator;
    REINTICH_STRUCT second_integrator;
    F32 first_feedback_delay;
    F32 second_feedback_delay;

} SWITCH_SECOND_ORDER_STATE_STRUCT;







typedef struct
{
    SWITCH_SECOND_ORDER_COEFF_STRUCT *coeff_ptr;
    SWITCH_SECOND_ORDER_STATE_STRUCT state;
    SWITCH_SECOND_ORDER_INPUT_STRUCT input;
    SWITCH_SECOND_ORDER_OUTPUT_STRUCT output;

} SWITCH_SECOND_ORDER_STRUCT;





void Switch_Second_Order_Initialize(SWITCH_SECOND_ORDER_STRUCT *st_ptr, SWITCH_SECOND_ORDER_COEFF_STRUCT *coeff_ptr);
void Switch_Second_Order_Set_Input_One(SWITCH_SECOND_ORDER_STRUCT *st_ptr, F32 input_one);
void Switch_Second_Order_Set_Input_Two(SWITCH_SECOND_ORDER_STRUCT *st_ptr, F32 input_two);
void Switch_Second_Order_Set_Switch(SWITCH_SECOND_ORDER_STRUCT *st_ptr, BOOLEAN switch_flag);
void Switch_Second_Order_Run(SWITCH_SECOND_ORDER_STRUCT *st_ptr);
F32 Switch_Second_Order_Get_Output(SWITCH_SECOND_ORDER_STRUCT *st_ptr);
# 64 "..\\..\\..\\Model\\Inner_Loop\\Header/Cyclic_Feedback.h" 2
# 1 "..\\..\\..\\Common\\Header\\Linterp.h" 1
# 81 "..\\..\\..\\Common\\Header\\Linterp.h"
typedef struct
{
    F32 breakpoint;
    F32 value;
    F32 slope;


} LINTERP_REGION_STRUCT;
# 99 "..\\..\\..\\Common\\Header\\Linterp.h"
typedef struct
{
    U8 n_regions;
    LINTERP_REGION_STRUCT regions[10];

} LINTERP_STRUCT;





F32 Linterp_Non_Monotonically_Spaced(LINTERP_STRUCT *linterp_struct, F32 index);
# 65 "..\\..\\..\\Model\\Inner_Loop\\Header/Cyclic_Feedback.h" 2
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header/Attitude_Controller.h" 1
# 65 "..\\..\\..\\Model\\Inner_Loop\\Header/Attitude_Controller.h"
# 1 "..\\..\\..\\Model\\Common\\Header\\ReIntICHS.h" 1
# 43 "..\\..\\..\\Model\\Common\\Header\\ReIntICHS.h"
# 1 "..\\..\\..\\Model\\Common\\Header/SaturationVF.h" 1
# 53 "..\\..\\..\\Model\\Common\\Header/SaturationVF.h"
typedef struct
{
    F32 epsilon;
    F32 upper_sat_limit;
    F32 lower_sat_limit;

} SATURATIONVF_COEFF_STRUCT;







typedef struct
{
    F32 IC;
    F32 input;
    BOOLEAN reset;

} SATURATIONVF_INPUT_STRUCT;







typedef struct
{
    F32 output;
    BOOLEAN inv;
    BOOLEAN satLo;
    BOOLEAN satHi;

} SATURATIONVF_OUTPUT_STRUCT;







typedef struct
{
    F32 delay;
    BOOLEAN reset_on_init;

} SATURATIONVF_STATE_STRUCT;







typedef struct
{
    SATURATIONVF_COEFF_STRUCT *coeff;
    SATURATIONVF_STATE_STRUCT state;
    SATURATIONVF_INPUT_STRUCT input;
    SATURATIONVF_OUTPUT_STRUCT output;

} SATURATIONVF_STRUCT;





void SaturationVF_Initialize(SATURATIONVF_STRUCT *st_ptr, SATURATIONVF_COEFF_STRUCT *coeff);
void SaturationVF_Set_Input(SATURATIONVF_STRUCT *st_ptr, F32 input);
void SaturationVF_Set_IC(SATURATIONVF_STRUCT *st_ptr, F32 ic);
void SaturationVF_Set_Reset(SATURATIONVF_STRUCT *st_ptr, BOOLEAN reset);
void SaturationVF_Run(SATURATIONVF_STRUCT *st_ptr);
F32 SaturationVF_Get_Output(SATURATIONVF_STRUCT *st_ptr);
BOOLEAN SaturationVF_Get_Inverted(SATURATIONVF_STRUCT *st_ptr);
BOOLEAN SaturationVF_Get_Sat_LL(SATURATIONVF_STRUCT *st_ptr);
BOOLEAN SaturationVF_Get_Sat_UL(SATURATIONVF_STRUCT *st_ptr);
# 44 "..\\..\\..\\Model\\Common\\Header\\ReIntICHS.h" 2
# 54 "..\\..\\..\\Model\\Common\\Header\\ReIntICHS.h"
typedef struct
{
    F32 K_Ts;
    F32 Gain;
    F32 UL;
    F32 LL;
    F32 rail_bounce_divisor;
    REINTICH_COEFF_STRUCT integrator_coeff;
    SATURATIONVF_COEFF_STRUCT sat_coeff;

} REINTICHS_COEFF_STRUCT;







typedef struct
{
    F32 IC;
    F32 input;
    BOOLEAN run;
    BOOLEAN hold;

} REINTICHS_INPUT_STRUCT;






typedef struct
{
    F32 IC_delay;
    F32 rail_bounce;

    BOOLEAN prev_sat_UL;
    BOOLEAN prev_sat_LL;
    BOOLEAN prev_sat_inv;

    BOOLEAN prev_reset_int;
    BOOLEAN prev_reset_sat;

    REINTICH_STRUCT integrator;
    SATURATIONVF_STRUCT sat;

} REINTICHS_STATE_STRUCT;







typedef struct
{
    F32 output;
    BOOLEAN sat_UL;
    BOOLEAN sat_LL;
    BOOLEAN inv;

} REINTICHS_OUTPUT_STRUCT;
# 125 "..\\..\\..\\Model\\Common\\Header\\ReIntICHS.h"
typedef struct
{
    REINTICHS_COEFF_STRUCT *coeff;
    REINTICHS_STATE_STRUCT state;
    REINTICHS_INPUT_STRUCT input;
    REINTICHS_OUTPUT_STRUCT output;

} REINTICHS_STRUCT;





void ReIntICHS_Initialize(REINTICHS_STRUCT *st_ptr, REINTICHS_COEFF_STRUCT *coeff);
void ReIntICHS_Set_Input(REINTICHS_STRUCT *st_ptr, F32 input);
void ReIntICHS_Set_IC(REINTICHS_STRUCT *st_ptr, F32 ic);
void ReIntICHS_Set_Hold(REINTICHS_STRUCT *st_ptr, BOOLEAN hold);
void ReIntICHS_Set_Run(REINTICHS_STRUCT *st_ptr, BOOLEAN run);
void ReIntICHS_Run(REINTICHS_STRUCT *st_ptr);
F32 ReIntICHS_Get_Output(REINTICHS_STRUCT *st_ptr);
BOOLEAN ReIntICHS_Get_Sat_UL(REINTICHS_STRUCT *st_ptr);
BOOLEAN ReIntICHS_Get_Sat_LL(REINTICHS_STRUCT *st_ptr);
BOOLEAN ReIntICHS_Get_Inv(REINTICHS_STRUCT *st_ptr);
# 66 "..\\..\\..\\Model\\Inner_Loop\\Header/Attitude_Controller.h" 2
# 76 "..\\..\\..\\Model\\Inner_Loop\\Header/Attitude_Controller.h"
typedef struct
{
    F32 c_reintichs_IC;
    F32 c_gamma;
    F32 null_attitude;
    F32 upper_sat_limit;
    F32 lower_sat_limit;
    F32 k_rate_to_ang_accel_cross;
    F32 k_rate_to_ang_accel_uar;
    F32 k_rate_to_ang_accel_normal;
    F32 k_attitude_to_ang_accel_uar;
    F32 k_attitude_to_ang_accel_normal;
    F32 k_attitude_to_ang_accel_integral_normal;

    F32 k_compensation;
    F32 k_ang_accel_to_cyclic;

    F32 k_integrator_curve_magnitude;

    SWITCH_SECOND_ORDER_COEFF_STRUCT rate_switch;
    SWITCH_SECOND_ORDER_COEFF_STRUCT attitude_switch;
    REINTICH_COEFF_STRUCT reintich;
    REINTICHS_COEFF_STRUCT reintichs;
    SWITCH_SECOND_ORDER_COEFF_STRUCT adp_cmd_switch_coeff;

} ATTITUDE_CONTROLLER_COEFF_STRUCT;







typedef struct
{
    F32 rate_cross_axis;
    F32 rate_near_axis;
    F32 attitude_near_axis;
    F32 adp_roll_cmd;
    F32 adp_pitch_cmd;
    BOOLEAN run_mode;
    BOOLEAN uar_mode;

} ATTITUDE_CONTROLLER_INPUT_STRUCT;







typedef struct
{
    F32 output;

} ATTITUDE_CONTROLLER_OUTPUT_STRUCT;
# 140 "..\\..\\..\\Model\\Inner_Loop\\Header/Attitude_Controller.h"
typedef struct
{
    SWITCH_SECOND_ORDER_STRUCT rate_switch;
    SWITCH_SECOND_ORDER_STRUCT attitude_switch;
    REINTICH_STRUCT reintich;
    REINTICHS_STRUCT reintichs;
    BOOLEAN prev_run;


        BOOLEAN integ_sat;


} ATTITUDE_CONTROLLER_STATE_STRUCT;







typedef struct
{
    ATTITUDE_CONTROLLER_COEFF_STRUCT *coeff_ptr;
    ATTITUDE_CONTROLLER_INPUT_STRUCT input;
    ATTITUDE_CONTROLLER_OUTPUT_STRUCT output;
    ATTITUDE_CONTROLLER_STATE_STRUCT state;

} ATTITUDE_CONTROLLER_STRUCT;




void Attitude_Controller_Initialize(ATTITUDE_CONTROLLER_STRUCT *st_ptr, ATTITUDE_CONTROLLER_COEFF_STRUCT *coeff_ptr);
void Attitude_Controller_Set_Rate_Cross_Coupled_Axis(ATTITUDE_CONTROLLER_STRUCT *st_ptr, F32 rate_cross_axis);
void Attitude_Controller_Set_Rate_Near_Axis(ATTITUDE_CONTROLLER_STRUCT *st_ptr, F32 rate_near_axis);
void Attitude_Controller_Set_Attitude_Near_Axis(ATTITUDE_CONTROLLER_STRUCT *st_ptr, F32 attitude_near_axis);
void Attitude_Controller_Set_UAR_Mode(ATTITUDE_CONTROLLER_STRUCT *st_ptr, BOOLEAN uar_mode);
void Attitude_Controller_Set_SaturatedRL(ATTITUDE_CONTROLLER_STRUCT *st_ptr, BOOLEAN rate_limited);
void Attitude_Controller_Set_Run(ATTITUDE_CONTROLLER_STRUCT *st_ptr, BOOLEAN run);
void Attitude_Controller_Run(ATTITUDE_CONTROLLER_STRUCT *st_ptr);

F32 Attitude_Controller_Get_Output(ATTITUDE_CONTROLLER_STRUCT *st_ptr);
# 66 "..\\..\\..\\Model\\Inner_Loop\\Header/Cyclic_Feedback.h" 2
# 1 "..\\..\\..\\Model\\Common\\Header\\Test_Port.h" 1
# 54 "..\\..\\..\\Model\\Common\\Header\\Test_Port.h"
typedef struct
{
    F32 gain;
    F32 bias;

} TEST_PORT_COEFF_STRUCT;






typedef struct
{
    F32 input;

} TEST_PORT_INPUT_STRUCT;







typedef struct
{
    F32 output;

} TEST_PORT_OUTPUT_STRUCT;







typedef struct
{
    TEST_PORT_COEFF_STRUCT *coeff;
    TEST_PORT_INPUT_STRUCT input;
    TEST_PORT_OUTPUT_STRUCT output;

} TEST_PORT_STRUCT;





void Test_Port_Initialize(TEST_PORT_STRUCT *st_ptr, TEST_PORT_COEFF_STRUCT *coeff);
void Test_Port_Set_Input(TEST_PORT_STRUCT *st_ptr, F32 input);
void Test_Port_Set_Gain(TEST_PORT_STRUCT *st_ptr, F32 gain);
void Test_Port_Set_Bias(TEST_PORT_STRUCT *st_ptr, F32 bias);
void Test_Port_Run(TEST_PORT_STRUCT *st_ptr);
F32 Test_Port_Get_Output(TEST_PORT_STRUCT *st_ptr);
# 67 "..\\..\\..\\Model\\Inner_Loop\\Header/Cyclic_Feedback.h" 2
# 77 "..\\..\\..\\Model\\Inner_Loop\\Header/Cyclic_Feedback.h"
typedef struct
{
    F32 pitch_bias;

    F32 roll_rate_limiter_upper_limit;
    F32 roll_rate_limiter_lower_limit;

    F32 pitch_rate_limiter_upper_limit;
    F32 pitch_rate_limiter_lower_limit;

    ATTITUDE_CONTROLLER_COEFF_STRUCT Roll_AttitudeController;
    ATTITUDE_CONTROLLER_COEFF_STRUCT Pitch_AttitudeController;

    SWITCH_SECOND_ORDER_COEFF_STRUCT adp_roll_cmd_switch;
    SWITCH_SECOND_ORDER_COEFF_STRUCT adp_pitch_cmd_switch;

    TEST_PORT_COEFF_STRUCT roll_testport;
    TEST_PORT_COEFF_STRUCT pitch_testport;

    F32 K_heading_rate_to_ang_accel_uar;
    SWITCH_SECOND_ORDER_COEFF_STRUCT heading_rate_switch;

    LINTERP_STRUCT pitch_bias_linterp;

    F32 tune_mode;

} CYCLIC_FEEDBACK_COEFF_STRUCT;







typedef struct
{
    F32 adp_phi_cmd;
    F32 adp_theta_cmd;
    F32 phi;
    F32 phi_dot;
    F32 psi_dot;
    F32 theta;
    F32 theta_dot;
    F32 p;
    F32 q;

    BOOLEAN reset;
    BOOLEAN UAR_mode;
    BOOLEAN triplex_fault;

} CYCLIC_FEEDBACK_INPUT_STRUCT;







typedef struct
{
    ATTITUDE_CONTROLLER_STRUCT Roll_AttitudeController;
    ATTITUDE_CONTROLLER_STRUCT Pitch_AttitudeController;


    F32 roll_rate_limiter_previous_state;
    F32 pitch_rate_limiter_previous_state;

    SWITCH_SECOND_ORDER_STRUCT adp_roll_cmd_switch;
    SWITCH_SECOND_ORDER_STRUCT adp_pitch_cmd_switch;

    TEST_PORT_STRUCT roll_testport;
    TEST_PORT_STRUCT pitch_testport;

    BOOLEAN first_frame;


        BOOLEAN adp_roll_rate_limited;
        BOOLEAN adp_pitch_rate_limited;


    SWITCH_SECOND_ORDER_STRUCT heading_rate_switch;
    F32 switched_heading_rate;

    F32 roll_test_input;
    F32 pitch_test_input;

} CYCLIC_FEEDBACK_STATE_STRUCT;







typedef struct
{
    CYCLIC_FEEDBACK_COEFF_STRUCT *coeff;
    CYCLIC_FEEDBACK_STATE_STRUCT state;
    CYCLIC_FEEDBACK_INPUT_STRUCT input;

} CYCLIC_FEEDBACK_STRUCT;




void Cyclic_Feedback_Initialize(CYCLIC_FEEDBACK_STRUCT *st_ptr, CYCLIC_FEEDBACK_COEFF_STRUCT *coeff_ptr);

void Cyclic_Feedback_Set_Euler_Angles(CYCLIC_FEEDBACK_STRUCT *st_ptr, EULER_ANGLES * eulers);
void Cyclic_Feedback_Set_Euler_Rates(CYCLIC_FEEDBACK_STRUCT *st_ptr, const EULER_RATES *euler_rates);
void Cyclic_Feedback_Set_Body_Rates(CYCLIC_FEEDBACK_STRUCT *st_ptr, VECTOR3 * rates);
void Cyclic_Feedback_Set_UAR_Mode(CYCLIC_FEEDBACK_STRUCT *st_ptr, BOOLEAN uar_mode);
void Cyclic_Feedback_Set_SaturatedRL(CYCLIC_FEEDBACK_STRUCT *st_ptr, BOOLEAN roll_rate_limited, BOOLEAN pitch_rate_limited);
void Cyclic_Feedback_Set_ADP_Commands(CYCLIC_FEEDBACK_STRUCT *st_ptr, CYCLIC_STRUCT *adp_cmds);
void Cyclic_Feedback_Set_Reset(CYCLIC_FEEDBACK_STRUCT *st_ptr, BOOLEAN reset);
void Cyclic_Feedback_Set_Run(CYCLIC_FEEDBACK_STRUCT *st_ptr, BOOLEAN run);

void Cyclic_Feedback_Run(CYCLIC_FEEDBACK_STRUCT *st_ptr);

void Cyclic_Feedback_Get_Feedback(CYCLIC_FEEDBACK_STRUCT *st_ptr, CYCLIC_STRUCT * roll_pitch_feedback);
# 63 "..\\..\\..\\Model\\Inner_Loop\\Header\\MCP.h" 2
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header/MCP_Control_Producer.h" 1
# 63 "..\\..\\..\\Model\\Inner_Loop\\Header/MCP_Control_Producer.h"
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header/UARModeLogic.h" 1
# 46 "..\\..\\..\\Model\\Inner_Loop\\Header/UARModeLogic.h"
# 1 "..\\..\\..\\Model\\Common\\Header\\ROS_FlipFlop.h" 1
# 53 "..\\..\\..\\Model\\Common\\Header\\ROS_FlipFlop.h"
typedef struct
{
    BOOLEAN set;

    BOOLEAN reset;

} ROS_FLIPFLOP_INPUT_STRUCT;







typedef struct
{
    BOOLEAN output;

} ROS_FLIPFLOP_OUTPUT_STRUCT;







typedef struct
{
    F32 s1;

} ROS_FLIPFLOP_STATE_STRUCT;







typedef struct
{
    ROS_FLIPFLOP_STATE_STRUCT state;
    ROS_FLIPFLOP_INPUT_STRUCT input;
    ROS_FLIPFLOP_OUTPUT_STRUCT output;

} ROS_FLIPFLOP_STRUCT;





void ROS_FlipFlop_Initialize(ROS_FLIPFLOP_STRUCT *st_ptr);
void ROS_FlipFlop_Set_Reset(ROS_FLIPFLOP_STRUCT *st_ptr, BOOLEAN reset);
void ROS_FlipFlop_Set_Set(ROS_FLIPFLOP_STRUCT *st_ptr, BOOLEAN set);
void ROS_FlipFlop_Run(ROS_FLIPFLOP_STRUCT *st_ptr);
BOOLEAN ROS_FlipFlop_Get_Output(ROS_FLIPFLOP_STRUCT *st_ptr);
# 47 "..\\..\\..\\Model\\Inner_Loop\\Header/UARModeLogic.h" 2
# 56 "..\\..\\..\\Model\\Inner_Loop\\Header/UARModeLogic.h"
typedef struct
{
    F32 phi_upper_limit;
    F32 phi_lower_limit;
    F32 theta_upper_limit;
    F32 theta_lower_limit;
    F32 p_filt_upper_limit;
    F32 p_filt_lower_limit;
    F32 q_filt_upper_limit;
    F32 q_filt_lower_limit;

    PERSISTENT1SHOT_COEFF_STRUCT run_p1shot;


    PERSISTENT1SHOT_COEFF_STRUCT uar_hold_p1shot;


} UARMODELOGIC_COEFF_STRUCT;







typedef struct
{
    F32 phi;
    F32 theta;
    F32 p_filt;
    F32 q_filt;

    BOOLEAN run;
    BOOLEAN adp_fail;
    BOOLEAN disable_ADP;

} UARMODELOGIC_INPUT_STRUCT;







typedef struct
{
    BOOLEAN phi_range_valid;
    BOOLEAN theta_range_valid;
    BOOLEAN uar_mode;

} UARMODELOGIC_OUTPUT_STRUCT;







typedef struct
{
    ROS_FLIPFLOP_STRUCT uar_mode_ff;
    ROS_FLIPFLOP_STRUCT phi_range_ff;
    ROS_FLIPFLOP_STRUCT theta_range_ff;

    PERSISTENT1SHOT_STRUCT run_p1shot;
    PERSISTENT1SHOT_STRUCT uar_hold_p1shot;

} UARMODELOGIC_STATE_STRUCT;







typedef struct
{
    UARMODELOGIC_COEFF_STRUCT *coeff_ptr;
    UARMODELOGIC_INPUT_STRUCT input;
    UARMODELOGIC_OUTPUT_STRUCT output;
    UARMODELOGIC_STATE_STRUCT state;

} UARMODELOGIC_STRUCT;




void UARModeLogic_Initialize(UARMODELOGIC_STRUCT *st_ptr, UARMODELOGIC_COEFF_STRUCT *coeff_ptr);

void UARModeLogic_Set_Euler_Angles(UARMODELOGIC_STRUCT *st_ptr, EULER_ANGLES * eulers);
void UARModeLogic_Set_Rates(UARMODELOGIC_STRUCT *st_ptr, VECTOR3 * rates);
void UARModeLogic_Set_ADP_Fail(UARMODELOGIC_STRUCT *st_ptr, BOOLEAN adp_fail);
void UARModeLogic_Set_Disable_ADP(UARMODELOGIC_STRUCT *st_ptr, BOOLEAN disable_ADP);
void UARModeLogic_Set_Run(UARMODELOGIC_STRUCT *st_ptr, BOOLEAN run);

void UARModeLogic_Run(UARMODELOGIC_STRUCT *st_ptr);

BOOLEAN UARModeLogic_Get_Phi_Range_Valid(UARMODELOGIC_STRUCT *st_ptr);
BOOLEAN UARModeLogic_Get_Theta_Range_Valid(UARMODELOGIC_STRUCT *st_ptr);
BOOLEAN UARModeLogic_Get_UAR_Mode(UARMODELOGIC_STRUCT *st_ptr);
# 64 "..\\..\\..\\Model\\Inner_Loop\\Header/MCP_Control_Producer.h" 2
# 73 "..\\..\\..\\Model\\Inner_Loop\\Header/MCP_Control_Producer.h"
typedef struct
{
    CYCLIC_FEEDBACK_COEFF_STRUCT cyclic_feedback;
    UARMODELOGIC_COEFF_STRUCT uar_mode_logic;

} MCP_CONTROL_PRODUCER_COEFF_STRUCT;







typedef struct
{
    BOOLEAN run;

} MCP_CONTROL_PRODUCER_INPUT_STRUCT;







typedef struct
{
    CYCLIC_STRUCT feedback;
    BOOLEAN uar_mode;
    BOOLEAN run_adp;
    BOOLEAN phi_valid;
    BOOLEAN theta_valid;

} MCP_CONTROL_PRODUCER_OUTPUT_STRUCT;







typedef struct
{
    CYCLIC_FEEDBACK_STRUCT cyclic_feedback;
    UARMODELOGIC_STRUCT uar_mode_logic;

} MCP_CONTROL_PRODUCER_STATE_STRUCT;







typedef struct
{
    MCP_CONTROL_PRODUCER_COEFF_STRUCT *coeff_ptr;
    MCP_CONTROL_PRODUCER_INPUT_STRUCT input;
    MCP_CONTROL_PRODUCER_OUTPUT_STRUCT output;
    MCP_CONTROL_PRODUCER_STATE_STRUCT state;

} MCP_CONTROL_PRODUCER_STRUCT;




void MCP_Control_Producer_Initialize(MCP_CONTROL_PRODUCER_STRUCT *st_ptr,
                                     MCP_CONTROL_PRODUCER_COEFF_STRUCT *coeff_ptr);

void MCP_Control_Producer_Set_Euler_Angles(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, EULER_ANGLES * eulers);
void MCP_Control_Producer_Set_Euler_Rates(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, const EULER_RATES *euler_rates);
void MCP_Control_Producer_Set_Body_Rates(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, VECTOR3 * rates);
void MCP_Control_Producer_Set_ADP_Fail(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, BOOLEAN adp_fail);
void MCP_Control_Producer_Set_ADP_Commands(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, CYCLIC_STRUCT *adp_commands);
void MCP_Control_Producer_Set_SaturatedRL(MCP_CONTROL_PRODUCER_STRUCT *st_ptr,
                                          BOOLEAN roll_rate_limited,
                                          BOOLEAN pitch_rate_limited);
void MCP_Control_Producer_Set_Disable_ADP(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, BOOLEAN disable_ADP);
void MCP_Control_Producer_Set_Run(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, BOOLEAN run);

void MCP_Control_Producer_Run(MCP_CONTROL_PRODUCER_STRUCT *st_ptr);

void MCP_Control_Producer_Get_Feedback(MCP_CONTROL_PRODUCER_STRUCT *st_ptr, CYCLIC_STRUCT * roll_pitch_feedback);
BOOLEAN MCP_Control_Producer_Get_UAR_Mode(MCP_CONTROL_PRODUCER_STRUCT *st_ptr);
BOOLEAN MCP_Control_Producer_Get_Run_ADP(MCP_CONTROL_PRODUCER_STRUCT *st_ptr);
BOOLEAN MCP_Control_Producer_Get_Phi_Valid(MCP_CONTROL_PRODUCER_STRUCT *st_ptr);
BOOLEAN MCP_Control_Producer_Get_Theta_Valid(MCP_CONTROL_PRODUCER_STRUCT *st_ptr);
# 64 "..\\..\\..\\Model\\Inner_Loop\\Header\\MCP.h" 2
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header/Inner_Loop_Monitors.h" 1
# 40 "..\\..\\..\\Model\\Inner_Loop\\Header/Inner_Loop_Monitors.h"
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor.h" 1
# 40 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor.h"
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor_Command.h" 1
# 41 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor_Command.h"
# 1 "..\\..\\..\\Model\\Common\\Header\\Tenth_Order_Average.h" 1
# 45 "..\\..\\..\\Model\\Common\\Header\\Tenth_Order_Average.h"
# 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 1 3
# 11 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
# 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 1 3
# 10 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 3
# 1 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 1 3
# 45 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 3
# 1 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\sal.h" 1 3
# 2970 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\sal.h" 3
# 1 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\concurrencysal.h" 1 3
# 2971 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\sal.h" 2 3
# 46 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 2 3
# 1 "c:\\llvm\\lib\\clang\\7.0.0\\include\\vadefs.h" 1 3
# 32 "c:\\llvm\\lib\\clang\\7.0.0\\include\\vadefs.h" 3
# 1 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vadefs.h" 1 3
# 15 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vadefs.h" 3
#pragma pack(push, 8)
# 28 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vadefs.h" 3
 typedef unsigned __int64 uintptr_t;
# 39 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vadefs.h" 3
        typedef char* va_list;
# 112 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vadefs.h" 3
    void __cdecl __va_start(va_list* , ...);
# 163 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vadefs.h" 3
#pragma pack(pop)
# 33 "c:\\llvm\\lib\\clang\\7.0.0\\include\\vadefs.h" 2 3
# 47 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 2 3
# 81 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 3
#pragma pack(push, 8)
# 176 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 3
 typedef unsigned __int64 size_t;
    typedef __int64 ptrdiff_t;
    typedef __int64 intptr_t;
# 192 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 3
    typedef _Bool __vcrt_bool;
# 211 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 3
    typedef unsigned short wchar_t;
# 273 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 3
    void __cdecl __security_init_cookie(void);





        void __cdecl __security_check_cookie( uintptr_t _StackCookie);
        __declspec(noreturn) void __cdecl __report_gsfailure( uintptr_t _StackCookie);



extern uintptr_t __security_cookie;







#pragma pack(pop)
# 11 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 2 3

#pragma pack(push, 8)
# 145 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 3
 typedef _Bool __crt_bool;
# 253 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 3
             void __cdecl _invalid_parameter_noinfo(void);
         __declspec(noreturn) void __cdecl _invalid_parameter_noinfo_noreturn(void);

__declspec(noreturn)
         void __cdecl _invoke_watson(
               wchar_t const* _Expression,
               wchar_t const* _FunctionName,
               wchar_t const* _FileName,
               unsigned int _LineNo,
               uintptr_t _Reserved);
# 482 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 3
typedef int errno_t;
typedef unsigned short wint_t;
typedef unsigned short wctype_t;
typedef long __time32_t;
typedef __int64 __time64_t;

typedef struct __crt_locale_data_public
{
      unsigned short const* _locale_pctype;
                        int _locale_mb_cur_max;
               unsigned int _locale_lc_codepage;
} __crt_locale_data_public;

typedef struct __crt_locale_pointers
{
    struct __crt_locale_data* locinfo;
    struct __crt_multibyte_data* mbcinfo;
} __crt_locale_pointers;

typedef __crt_locale_pointers* _locale_t;

typedef struct _Mbstatet
{
    unsigned long _Wchar;
    unsigned short _Byte, _State;
} _Mbstatet;

typedef _Mbstatet mbstate_t;
# 523 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 3
        typedef __time64_t time_t;
# 533 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 3
    typedef size_t rsize_t;
# 1982 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt.h" 3
#pragma pack(pop)
# 12 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 2 3
# 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memory.h" 1 3
# 14 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memory.h" 3
# 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memcpy_s.h" 1 3
# 11 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memcpy_s.h" 3
# 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\errno.h" 1 3
# 13 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\errno.h" 3
#pragma pack(push, 8)




 int* __cdecl _errno(void);


             errno_t __cdecl _set_errno( int _Value);
             errno_t __cdecl _get_errno( int* _Value);

             unsigned long* __cdecl __doserrno(void);


             errno_t __cdecl _set_doserrno( unsigned long _Value);
             errno_t __cdecl _get_doserrno( unsigned long * _Value);
# 129 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\errno.h" 3
#pragma pack(pop)
# 12 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memcpy_s.h" 2 3
# 1 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime_string.h" 1 3
# 10 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime_string.h" 3
# 1 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime.h" 1 3
# 11 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime_string.h" 2 3



#pragma pack(push, 8)




 void * __cdecl memchr(
                                    void const* _Buf,
                                    int _Val,
                                    size_t _MaxCount
    );


int __cdecl memcmp(
                            void const* _Buf1,
                            void const* _Buf2,
                            size_t _Size
    );
# 40 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime_string.h" 3
void* __cdecl memcpy(
                                  void* _Dst,
                                  void const* _Src,
                                  size_t _Size
    );


         void* __cdecl memmove(
                                      void* _Dst,
                                      void const* _Src,
                                      size_t _Size
    );
# 60 "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.11.25503\\include\\vcruntime_string.h" 3
void* __cdecl memset(
                                  void* _Dst,
                                  int _Val,
                                  size_t _Size
    );


         char * __cdecl strchr(
           char const* _Str,
           int _Val
    );


         char * __cdecl strrchr(
           char const* _Str,
           int _Ch
    );


         char * __cdecl strstr(
           char const* _Str,
           char const* _SubStr
    );



         wchar_t * __cdecl wcschr(
           wchar_t const* _Str,
           wchar_t _Ch
    );


         wchar_t * __cdecl wcsrchr(
           wchar_t const* _Str,
           wchar_t _Ch
    );



         wchar_t * __cdecl wcsstr(
           wchar_t const* _Str,
           wchar_t const* _SubStr
    );



#pragma pack(pop)
# 13 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memcpy_s.h" 2 3

#pragma pack(push, 8)
# 35 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memcpy_s.h" 3
 static __inline errno_t __cdecl memcpy_s(
                                                                 void* const _Destination,
                                                                 rsize_t const _DestinationSize,
                                                                 void const* const _Source,
                                                                 rsize_t const _SourceSize
        )
    {
        if (_SourceSize == 0)
        {
            return 0;
        }

        { int _Expr_val=!!(_Destination != 0); if (!(_Expr_val)) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; } };
        if (_Source == 0 || _DestinationSize < _SourceSize)
        {
            memset(_Destination, 0, _DestinationSize);

            { int _Expr_val=!!(_Source != 0); if (!(_Expr_val)) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; } };
            { int _Expr_val=!!(_DestinationSize >= _SourceSize); if (!(_Expr_val)) { (*_errno()) = 34; _invalid_parameter_noinfo(); return 34; } };


            return 22;
        }

        memcpy(_Destination, _Source, _SourceSize);
        return 0;
    }


    static __inline errno_t __cdecl memmove_s(
                                                                 void* const _Destination,
                                                                 rsize_t const _DestinationSize,
                                                                 void const* const _Source,
                                                                 rsize_t const _SourceSize
        )
    {
        if (_SourceSize == 0)
        {
            return 0;
        }

        { int _Expr_val=!!(_Destination != 0); if (!(_Expr_val)) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; } };
        { int _Expr_val=!!(_Source != 0); if (!(_Expr_val)) { (*_errno()) = 22; _invalid_parameter_noinfo(); return 22; } };
        { int _Expr_val=!!(_DestinationSize >= _SourceSize); if (!(_Expr_val)) { (*_errno()) = 34; _invalid_parameter_noinfo(); return 34; } };

        memmove(_Destination, _Source, _SourceSize);
        return 0;
    }





#pragma pack(pop)
# 15 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memory.h" 2 3




#pragma pack(push, 8)




 int __cdecl _memicmp(
                                void const* _Buf1,
                                void const* _Buf2,
                                size_t _Size
    );


         int __cdecl _memicmp_l(
                                void const* _Buf1,
                                void const* _Buf2,
                                size_t _Size,
                                _locale_t _Locale
    );
# 78 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memory.h" 3
    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_memccpy" ". See online help for details."))
             void* __cdecl memccpy(
                                      void* _Dst,
                                      void const* _Src,
                                      int _Val,
                                      size_t _Size
        );

                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_memicmp" ". See online help for details."))
             int __cdecl memicmp(
                                    void const* _Buf1,
                                    void const* _Buf2,
                                    size_t _Size
        );
# 114 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_memory.h" 3
#pragma pack(pop)
# 13 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 2 3
# 1 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 1 3
# 16 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
#pragma pack(push, 8)
# 28 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
 errno_t __cdecl wcscat_s(
                                        wchar_t* _Destination,
             rsize_t _SizeInWords,
               wchar_t const* _Source
        );


             errno_t __cdecl wcscpy_s(
                                     wchar_t* _Destination,
             rsize_t _SizeInWords,
               wchar_t const* _Source
        );


             errno_t __cdecl wcsncat_s(
                                        wchar_t* _Destination,
                                        rsize_t _SizeInWords,
                                        wchar_t const* _Source,
                                        rsize_t _MaxCount
        );


             errno_t __cdecl wcsncpy_s(
                                     wchar_t* _Destination,
                                     rsize_t _SizeInWords,
                                     wchar_t const* _Source,
                                     rsize_t _MaxCount
        );


             wchar_t* __cdecl wcstok_s(
                                      wchar_t* _String,
                                      wchar_t const* _Delimiter,
                                      wchar_t** _Context
        );
# 79 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
         __declspec(allocator) wchar_t* __cdecl _wcsdup(
           wchar_t const* _String
    );
# 97 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
#pragma warning(push)
#pragma warning(disable: 28719)
#pragma warning(disable: 28726)
 __declspec(deprecated("This function or variable may be unsafe. Consider using " "wcscat_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl wcscat( wchar_t *_Destination, wchar_t const* _Source);




#pragma warning(pop)



 int __cdecl wcscmp(
           wchar_t const* _String1,
           wchar_t const* _String2
    );







#pragma warning(push)
#pragma warning(disable: 28719)
#pragma warning(disable: 28726)
__declspec(deprecated("This function or variable may be unsafe. Consider using " "wcscpy_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl wcscpy( wchar_t *_Destination, wchar_t const* _Source);




#pragma warning(pop)


 size_t __cdecl wcscspn(
           wchar_t const* _String,
           wchar_t const* _Control
    );


         size_t __cdecl wcslen(
           wchar_t const* _String
    );
# 150 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
         size_t __cdecl wcsnlen(
                               wchar_t const* _Source,
                               size_t _MaxCount
    );
# 166 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
    static __inline size_t __cdecl wcsnlen_s(
                                   wchar_t const* _Source,
                                   size_t _MaxCount
        )
    {
        return (_Source == 0) ? 0 : wcsnlen(_Source, _MaxCount);
    }
# 183 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
__declspec(deprecated("This function or variable may be unsafe. Consider using " "wcsncat_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl wcsncat( wchar_t *_Destination, wchar_t const* _Source, size_t _Count);
# 192 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
         int __cdecl wcsncmp(
                               wchar_t const* _String1,
                               wchar_t const* _String2,
                               size_t _MaxCount
    );
# 205 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
__declspec(deprecated("This function or variable may be unsafe. Consider using " "wcsncpy_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl wcsncpy( wchar_t *_Destination, wchar_t const* _Source, size_t _Count);
# 214 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
         wchar_t * __cdecl wcspbrk(
           wchar_t const* _String,
           wchar_t const* _Control
    );


         size_t __cdecl wcsspn(
           wchar_t const* _String,
           wchar_t const* _Control
    );

               __declspec(deprecated("This function or variable may be unsafe. Consider using " "wcstok_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
         wchar_t* __cdecl wcstok(
                                      wchar_t* _String,
                                      wchar_t const* _Delimiter,
                                      wchar_t** _Context
    );
# 243 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
#pragma warning(push)
#pragma warning(disable: 4141 4996)

 __declspec(deprecated("This function or variable may be unsafe. Consider using " "wcstok_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
    static __inline wchar_t* __cdecl _wcstok(
                      wchar_t* const _String,
                      wchar_t const* const _Delimiter
        )
    {
        return wcstok(_String, _Delimiter, 0);
    }
# 270 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
#pragma warning(pop)






 __declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcserror_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
         wchar_t* __cdecl _wcserror(
         int _ErrorNumber
    );


         errno_t __cdecl _wcserror_s(
                                     wchar_t* _Buffer,
                                     size_t _SizeInWords,
                                     int _ErrorNumber
    );
# 297 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
               __declspec(deprecated("This function or variable may be unsafe. Consider using " "__wcserror_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
         wchar_t* __cdecl __wcserror(
               wchar_t const* _String
    );

                                errno_t __cdecl __wcserror_s(
                                     wchar_t* _Buffer,
                                     size_t _SizeInWords,
                                     wchar_t const* _ErrorMessage
    );







                        int __cdecl _wcsicmp(
           wchar_t const* _String1,
           wchar_t const* _String2
    );

                        int __cdecl _wcsicmp_l(
             wchar_t const* _String1,
             wchar_t const* _String2,
             _locale_t _Locale
    );

                        int __cdecl _wcsnicmp(
                               wchar_t const* _String1,
                               wchar_t const* _String2,
                               size_t _MaxCount
    );

                        int __cdecl _wcsnicmp_l(
                               wchar_t const* _String1,
                               wchar_t const* _String2,
                               size_t _MaxCount,
                               _locale_t _Locale
    );

                            errno_t __cdecl _wcsnset_s(
                                    wchar_t* _Destination,
                                    size_t _SizeInWords,
                                    wchar_t _Value,
                                    size_t _MaxCount
    );
# 352 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcsnset_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl _wcsnset( wchar_t *_String, wchar_t _Value, size_t _MaxCount);







         wchar_t* __cdecl _wcsrev(
              wchar_t* _String
    );

                            errno_t __cdecl _wcsset_s(
                                    wchar_t* _Destination,
                                    size_t _SizeInWords,
                                    wchar_t _Value
    );







__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcsset_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl _wcsset( wchar_t *_String, wchar_t _Value);






                            errno_t __cdecl _wcslwr_s(
                                    wchar_t* _String,
                                    size_t _SizeInWords
    );






__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcslwr_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl _wcslwr( wchar_t *_String);





         errno_t __cdecl _wcslwr_s_l(
                                    wchar_t* _String,
                                    size_t _SizeInWords,
                                    _locale_t _Locale
    );







__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcslwr_s_l" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl _wcslwr_l( wchar_t *_String, _locale_t _Locale);







         errno_t __cdecl _wcsupr_s(
                             wchar_t* _String,
                             size_t _Size
    );






__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcsupr_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl _wcsupr( wchar_t *_String);





         errno_t __cdecl _wcsupr_s_l(
                             wchar_t* _String,
                             size_t _Size,
                             _locale_t _Locale
    );







__declspec(deprecated("This function or variable may be unsafe. Consider using " "_wcsupr_s_l" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) wchar_t* __cdecl _wcsupr_l( wchar_t *_String, _locale_t _Locale);
# 456 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
         size_t __cdecl wcsxfrm(
                                              wchar_t* _Destination,
                                              wchar_t const* _Source,
                                              size_t _MaxCount
    );



         size_t __cdecl _wcsxfrm_l(
                                              wchar_t* _Destination,
                                              wchar_t const* _Source,
                                              size_t _MaxCount,
                                              _locale_t _Locale
    );


         int __cdecl wcscoll(
           wchar_t const* _String1,
           wchar_t const* _String2
    );


         int __cdecl _wcscoll_l(
             wchar_t const* _String1,
             wchar_t const* _String2,
             _locale_t _Locale
    );


         int __cdecl _wcsicoll(
           wchar_t const* _String1,
           wchar_t const* _String2
    );


         int __cdecl _wcsicoll_l(
             wchar_t const* _String1,
             wchar_t const* _String2,
             _locale_t _Locale
    );


         int __cdecl _wcsncoll(
                               wchar_t const* _String1,
                               wchar_t const* _String2,
                               size_t _MaxCount
    );


         int __cdecl _wcsncoll_l(
                               wchar_t const* _String1,
                               wchar_t const* _String2,
                               size_t _MaxCount,
                               _locale_t _Locale
    );


         int __cdecl _wcsnicoll(
                               wchar_t const* _String1,
                               wchar_t const* _String2,
                               size_t _MaxCount
    );


         int __cdecl _wcsnicoll_l(
                               wchar_t const* _String1,
                               wchar_t const* _String2,
                               size_t _MaxCount,
                               _locale_t _Locale
    );
# 579 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsdup" ". See online help for details."))
             wchar_t* __cdecl wcsdup(
               wchar_t const* _String
        );
# 591 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\corecrt_wstring.h" 3
                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsicmp" ". See online help for details."))
             int __cdecl wcsicmp(
               wchar_t const* _String1,
               wchar_t const* _String2
        );

                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsnicmp" ". See online help for details."))
             int __cdecl wcsnicmp(
                                   wchar_t const* _String1,
                                   wchar_t const* _String2,
                                   size_t _MaxCount
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsnset" ". See online help for details."))

             wchar_t* __cdecl wcsnset(
                                     wchar_t* _String,
                                     wchar_t _Value,
                                     size_t _MaxCount
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsrev" ". See online help for details."))

             wchar_t* __cdecl wcsrev(
                  wchar_t* _String
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsset" ". See online help for details."))

             wchar_t* __cdecl wcsset(
                  wchar_t* _String,
                  wchar_t _Value
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcslwr" ". See online help for details."))

             wchar_t* __cdecl wcslwr(
                  wchar_t* _String
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsupr" ". See online help for details."))

             wchar_t* __cdecl wcsupr(
                  wchar_t* _String
        );

                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_wcsicoll" ". See online help for details."))
             int __cdecl wcsicoll(
               wchar_t const* _String1,
               wchar_t const* _String2
        );





#pragma pack(pop)
# 14 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 2 3




#pragma pack(push, 8)








 errno_t __cdecl strcpy_s(
                                     char* _Destination,
                                     rsize_t _SizeInBytes,
                                     char const* _Source
        );


             errno_t __cdecl strcat_s(
                                        char* _Destination,
                                        rsize_t _SizeInBytes,
                                        char const* _Source
        );


             errno_t __cdecl strerror_s(
                                     char* _Buffer,
                                     size_t _SizeInBytes,
                                     int _ErrorNumber);


             errno_t __cdecl strncat_s(
                                        char* _Destination,
                                        rsize_t _SizeInBytes,
                                        char const* _Source,
                                        rsize_t _MaxCount
        );


             errno_t __cdecl strncpy_s(
                                     char* _Destination,
                                     rsize_t _SizeInBytes,
                                     char const* _Source,
                                     rsize_t _MaxCount
        );


             char* __cdecl strtok_s(
                                      char* _String,
                                      char const* _Delimiter,
                                      char** _Context
        );



         void* __cdecl _memccpy(
                                      void* _Dst,
                                      void const* _Src,
                                      int _Val,
                                      size_t _MaxCount
    );
# 86 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
#pragma warning(push)
#pragma warning(disable: 28719)
#pragma warning(disable: 28726)
 __declspec(deprecated("This function or variable may be unsafe. Consider using " "strcat_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl strcat( char *_Destination, char const* _Source);




#pragma warning(pop)




int __cdecl strcmp(
           char const* _Str1,
           char const* _Str2
    );


         int __cdecl _strcmpi(
           char const* _String1,
           char const* _String2
    );


         int __cdecl strcoll(
           char const* _String1,
           char const* _String2
    );


         int __cdecl _strcoll_l(
             char const* _String1,
             char const* _String2,
             _locale_t _Locale
    );







#pragma warning(push)
#pragma warning(disable: 28719)
#pragma warning(disable: 28726)
__declspec(deprecated("This function or variable may be unsafe. Consider using " "strcpy_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl strcpy( char *_Destination, char const* _Source);




#pragma warning(pop)


 size_t __cdecl strcspn(
           char const* _Str,
           char const* _Control
    );







         __declspec(allocator) char* __cdecl _strdup(
               char const* _Source
    );







               __declspec(deprecated("This function or variable may be unsafe. Consider using " "_strerror_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
         char* __cdecl _strerror(
               char const* _ErrorMessage
    );


         errno_t __cdecl _strerror_s(
                                 char* _Buffer,
                                 size_t _SizeInBytes,
                                 char const* _ErrorMessage
    );
# 180 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
               __declspec(deprecated("This function or variable may be unsafe. Consider using " "strerror_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
         char* __cdecl strerror(
         int _ErrorMessage
    );
# 192 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
         int __cdecl _stricmp(
           char const* _String1,
           char const* _String2
    );


         int __cdecl _stricoll(
           char const* _String1,
           char const* _String2
    );


         int __cdecl _stricoll_l(
             char const* _String1,
             char const* _String2,
             _locale_t _Locale
    );


         int __cdecl _stricmp_l(
             char const* _String1,
             char const* _String2,
             _locale_t _Locale
    );


size_t __cdecl strlen(
           char const* _Str
    );


         errno_t __cdecl _strlwr_s(
                             char* _String,
                             size_t _Size
    );






__declspec(deprecated("This function or variable may be unsafe. Consider using " "_strlwr_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl _strlwr( char *_String);





         errno_t __cdecl _strlwr_s_l(
                             char* _String,
                             size_t _Size,
                             _locale_t _Locale
    );







__declspec(deprecated("This function or variable may be unsafe. Consider using " "_strlwr_s_l" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl _strlwr_l( char *_String, _locale_t _Locale);
# 265 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
__declspec(deprecated("This function or variable may be unsafe. Consider using " "strncat_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl strncat( char *_Destination, char const* _Source, size_t _Count);
# 274 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
         int __cdecl strncmp(
                               char const* _Str1,
                               char const* _Str2,
                               size_t _MaxCount
    );


         int __cdecl _strnicmp(
                               char const* _String1,
                               char const* _String2,
                               size_t _MaxCount
    );


         int __cdecl _strnicmp_l(
                               char const* _String1,
                               char const* _String2,
                               size_t _MaxCount,
                               _locale_t _Locale
    );


         int __cdecl _strnicoll(
                               char const* _String1,
                               char const* _String2,
                               size_t _MaxCount
    );


         int __cdecl _strnicoll_l(
                               char const* _String1,
                               char const* _String2,
                               size_t _MaxCount,
                               _locale_t _Locale
    );


         int __cdecl _strncoll(
                               char const* _String1,
                               char const* _String2,
                               size_t _MaxCount
    );


         int __cdecl _strncoll_l(
                               char const* _String1,
                               char const* _String2,
                               size_t _MaxCount,
                               _locale_t _Locale
    );

         size_t __cdecl __strncnt(
                            char const* _String,
                            size_t _Count
    );
# 337 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
__declspec(deprecated("This function or variable may be unsafe. Consider using " "strncpy_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl strncpy( char *_Destination, char const* _Source, size_t _Count);
# 354 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
         size_t __cdecl strnlen(
                               char const* _String,
                               size_t _MaxCount
    );
# 370 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
    static __inline size_t __cdecl strnlen_s(
                                   char const* _String,
                                   size_t _MaxCount
        )
    {
        return _String == 0 ? 0 : strnlen(_String, _MaxCount);
    }




         errno_t __cdecl _strnset_s(
                                    char* _String,
                                    size_t _SizeInBytes,
                                    int _Value,
                                    size_t _MaxCount
    );
# 395 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
__declspec(deprecated("This function or variable may be unsafe. Consider using " "_strnset_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl _strnset( char *_Destination, int _Value, size_t _Count);
# 404 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
         char * __cdecl strpbrk(
           char const* _Str,
           char const* _Control
    );

         char* __cdecl _strrev(
              char* _Str
    );


         errno_t __cdecl _strset_s(
                                        char* _Destination,
                                        size_t _DestinationSize,
                                        int _Value
    );







__declspec(deprecated("This function or variable may be unsafe. Consider using " "_strset_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl _strset( char *_Destination, int _Value);






         size_t __cdecl strspn(
           char const* _Str,
           char const* _Control
    );

               __declspec(deprecated("This function or variable may be unsafe. Consider using " "strtok_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details."))
         char* __cdecl strtok(
                  char* _String,
                  char const* _Delimiter
    );


         errno_t __cdecl _strupr_s(
                             char* _String,
                             size_t _Size
    );






__declspec(deprecated("This function or variable may be unsafe. Consider using " "_strupr_s" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl _strupr( char *_String);





         errno_t __cdecl _strupr_s_l(
                             char* _String,
                             size_t _Size,
                             _locale_t _Locale
    );







__declspec(deprecated("This function or variable may be unsafe. Consider using " "_strupr_s_l" " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " "See online help for details.")) char* __cdecl _strupr_l( char *_String, _locale_t _Locale);
# 482 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
         size_t __cdecl strxfrm(
                                              char* _Destination,
                                              char const* _Source,
                                              size_t _MaxCount
    );



         size_t __cdecl _strxfrm_l(
                                              char* _Destination,
                                              char const* _Source,
                                              size_t _MaxCount,
                                              _locale_t _Locale
    );
# 537 "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\\string.h" 3
                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strdup" ". See online help for details."))
             char* __cdecl strdup(
                   char const* _String
        );






                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strcmpi" ". See online help for details."))
             int __cdecl strcmpi(
               char const* _String1,
               char const* _String2
        );

                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_stricmp" ". See online help for details."))
             int __cdecl stricmp(
               char const* _String1,
               char const* _String2
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strlwr" ". See online help for details."))
             char* __cdecl strlwr(
                  char* _String
        );

                   __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strnicmp" ". See online help for details."))
             int __cdecl strnicmp(
                                   char const* _String1,
                                   char const* _String2,
                                   size_t _MaxCount
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strnset" ". See online help for details."))
             char* __cdecl strnset(
                                     char* _String,
                                     int _Value,
                                     size_t _MaxCount
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strrev" ". See online help for details."))
             char* __cdecl strrev(
                  char* _String
        );

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strset" ". See online help for details."))
    char* __cdecl strset(
                  char* _String,
                  int _Value);

    __declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C " "and C++ conformant name: " "_strupr" ". See online help for details."))
             char* __cdecl strupr(
                  char* _String
        );





#pragma pack(pop)
# 46 "..\\..\\..\\Model\\Common\\Header\\Tenth_Order_Average.h" 2
# 65 "..\\..\\..\\Model\\Common\\Header\\Tenth_Order_Average.h"
typedef struct
{
    U32 sample_interval;

} TENTH_ORDER_AVERAGE_COEFF_STRUCT;






typedef struct
{
    F32 input;
    F32 input_IC;
    BOOLEAN reset;

} TENTH_ORDER_AVERAGE_INPUT_STRUCT;







typedef struct
{
    F32 output;





} TENTH_ORDER_AVERAGE_OUTPUT_STRUCT;







typedef struct
{
    F32 regfile[10];
    U32 regfile_index;

    F32 sum;
    F32 average;





    U16 sample_interval;

    BOOLEAN do_first_frame;

} TENTH_ORDER_AVERAGE_STATE_STRUCT;







typedef struct
{
    TENTH_ORDER_AVERAGE_COEFF_STRUCT *coeff_ptr;
    TENTH_ORDER_AVERAGE_STATE_STRUCT state;
    TENTH_ORDER_AVERAGE_INPUT_STRUCT input;
    TENTH_ORDER_AVERAGE_OUTPUT_STRUCT output;

} TENTH_ORDER_AVERAGE_STRUCT;





void Tenth_Order_Average_Initialize( TENTH_ORDER_AVERAGE_STRUCT *st_ptr, TENTH_ORDER_AVERAGE_COEFF_STRUCT *coeff_ptr);
void Tenth_Order_Average_Set_Reset(TENTH_ORDER_AVERAGE_STRUCT *st_ptr, BOOLEAN reset);
void Tenth_Order_Average_Set_Input(TENTH_ORDER_AVERAGE_STRUCT *st_ptr, F32 input);
void Tenth_Order_Average_Set_Input_IC(TENTH_ORDER_AVERAGE_STRUCT *st_ptr, F32 input_IC);
void Tenth_Order_Average_Run(TENTH_ORDER_AVERAGE_STRUCT *st_ptr);
F32 Tenth_Order_Average_Get_Output(TENTH_ORDER_AVERAGE_STRUCT *st_ptr);
# 42 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor_Command.h" 2
# 1 "..\\..\\..\\Model\\Common\\Header\\FirstOrderFilter.h" 1
# 54 "..\\..\\..\\Model\\Common\\Header\\FirstOrderFilter.h"
typedef struct
{
    F32 a1;
    F32 b0;
    F32 b1;
    F32 k1;
    F32 k2;

} FIRSTORDERFILTER_COEFF_STRUCT;







typedef struct
{
    F32 input;
    F32 input_IC;
    BOOLEAN reset;

} FIRSTORDERFILTER_INPUT_STRUCT;







typedef struct
{
    F32 output;

} FIRSTORDERFILTER_OUTPUT_STRUCT;







typedef struct
{
    F32 s1;
    F32 s2;

    BOOLEAN do_first_frame;

} FIRSTORDERFILTER_STATE_STRUCT;







typedef struct
{
    FIRSTORDERFILTER_COEFF_STRUCT *coeff_ptr;
    FIRSTORDERFILTER_STATE_STRUCT state;
    FIRSTORDERFILTER_INPUT_STRUCT input;
    FIRSTORDERFILTER_OUTPUT_STRUCT output;

} FIRSTORDERFILTER_STRUCT;
# 128 "..\\..\\..\\Model\\Common\\Header\\FirstOrderFilter.h"
void FirstOrderFilter_Initialize(FIRSTORDERFILTER_STRUCT *st_ptr, FIRSTORDERFILTER_COEFF_STRUCT *coeff_ptr);
void FirstOrderFilter_Set_Input(FIRSTORDERFILTER_STRUCT *st_ptr, F32 input);
void FirstOrderFilter_Set_Input_IC(FIRSTORDERFILTER_STRUCT *st_ptr, F32 input_IC);
void FirstOrderFilter_Set_Reset(FIRSTORDERFILTER_STRUCT *st_ptr, BOOLEAN reset);
void FirstOrderFilter_Run(FIRSTORDERFILTER_STRUCT *st_ptr);
F32 FirstOrderFilter_Get_Output(FIRSTORDERFILTER_STRUCT *st_ptr);
# 43 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor_Command.h" 2
# 54 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor_Command.h"
typedef struct
{
    PERSISTENT1SHOT_COEFF_STRUCT p1shot_coeff;
    TENTH_ORDER_AVERAGE_COEFF_STRUCT toa_coeff;
    FIRSTORDERFILTER_COEFF_STRUCT wash_out_coeff;
    F32 wof_l_limit;
    F32 wof_u_limit;

} MONITOR_COMMAND_COEFF_STRUCT;







typedef struct
{
    BOOLEAN run;

} MONITOR_COMMAND_INPUT_STRUCT;







typedef struct
{
    BOOLEAN command_fail;

} MONITOR_COMMAND_OUTPUT_STRUCT;







typedef struct
{
    PERSISTENT1SHOT_STRUCT p1shot;
    TENTH_ORDER_AVERAGE_STRUCT toa;
    FIRSTORDERFILTER_STRUCT wash_out;
    ROS_FLIPFLOP_STRUCT ros_ff;

} MONITOR_COMMAND_STATE_STRUCT;







typedef struct
{
    MONITOR_COMMAND_COEFF_STRUCT *coeff_ptr;
    MONITOR_COMMAND_INPUT_STRUCT input;
    MONITOR_COMMAND_OUTPUT_STRUCT output;
    MONITOR_COMMAND_STATE_STRUCT state;

} MONITOR_COMMAND_STRUCT;




void Monitor_Command_Initialize(MONITOR_COMMAND_STRUCT *st_ptr, MONITOR_COMMAND_COEFF_STRUCT *coeff_ptr);
void Monitor_Command_Set_Command(MONITOR_COMMAND_STRUCT *st_ptr, F32 command);
void Monitor_Command_Set_Run(MONITOR_COMMAND_STRUCT *st_ptr, BOOLEAN run);
void Monitor_Command_Set_Reset(MONITOR_COMMAND_STRUCT *st_ptr, BOOLEAN reset);
void Monitor_Command_Run(MONITOR_COMMAND_STRUCT *st_ptr);
BOOLEAN Monitor_Command_Get_Output(MONITOR_COMMAND_STRUCT *st_ptr);
# 41 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor.h" 2
# 52 "..\\..\\..\\Model\\Inner_Loop\\Header/Monitor.h"
typedef struct
{
    F32 rate_l_limit;
    F32 rate_u_limit;
    F32 attitude_l_limit;
    F32 attitude_u_limit;
    MONITOR_COMMAND_COEFF_STRUCT adp_cmd_coeff;
    MONITOR_COMMAND_COEFF_STRUCT act_pos_coeff;

} MONITOR_COEFF_STRUCT;







typedef struct
{
    F32 rate;
    F32 attitude;
    BOOLEAN uar_mode;

} MONITOR_INPUT_STRUCT;







typedef struct
{
    BOOLEAN rate_fail;
    BOOLEAN attitude_fail;
    BOOLEAN adp_command_fail;
    BOOLEAN actuator_position_fail;

} MONITOR_OUTPUT_STRUCT;







typedef struct
{
    MONITOR_COMMAND_STRUCT adp_cmd;
    MONITOR_COMMAND_STRUCT act_pos;

} MONITOR_STATE_STRUCT;







typedef struct
{
    MONITOR_COEFF_STRUCT *coeff_ptr;
    MONITOR_INPUT_STRUCT input;
    MONITOR_OUTPUT_STRUCT output;
    MONITOR_STATE_STRUCT state;

} MONITOR_STRUCT;





void Monitor_Initialize(MONITOR_STRUCT *st_ptr, MONITOR_COEFF_STRUCT *coeff_ptr);
void Monitor_Set_Rate(MONITOR_STRUCT *st_ptr, F32 rate);
void Monitor_Set_ADP_Command(MONITOR_STRUCT *st_ptr, F32 adp_command);
void Monitor_Set_Actuator_Position(MONITOR_STRUCT *st_ptr, F32 actuator_position);
void Monitor_Set_Attitude(MONITOR_STRUCT *st_ptr, F32 attitude);
void Monitor_Set_UAR_Mode(MONITOR_STRUCT *st_ptr, BOOLEAN uar_mode);
void Monitor_Set_Run(MONITOR_STRUCT *st_ptr, BOOLEAN run);
void Monitor_Run(MONITOR_STRUCT *st_ptr);

BOOLEAN Monitor_Get_Rate_Fail(MONITOR_STRUCT *st_ptr);
BOOLEAN Monitor_Get_Attitude_Fail(MONITOR_STRUCT *st_ptr);
BOOLEAN Monitor_Get_ADP_Command_Fail(MONITOR_STRUCT *st_ptr);
BOOLEAN Monitor_Get_Actuator_Position_Fail(MONITOR_STRUCT *st_ptr);
# 41 "..\\..\\..\\Model\\Inner_Loop\\Header/Inner_Loop_Monitors.h" 2
# 52 "..\\..\\..\\Model\\Inner_Loop\\Header/Inner_Loop_Monitors.h"
typedef struct
{
    MONITOR_COEFF_STRUCT roll_coeff;
    MONITOR_COEFF_STRUCT pitch_coeff;
    F32 lf_l_limit;

    PERSISTENT1SHOT_COEFF_STRUCT pos_coeff;

} INNER_LOOP_MONITORS_COEFF_STRUCT;







typedef struct
{
    F32 az_filt;
    BOOLEAN run;
    BOOLEAN uar_mode;

} INNER_LOOP_MONITORS_INPUT_STRUCT;







typedef struct
{
    BOOLEAN adp_fail;
    BOOLEAN horn;
    BOOLEAN low_g;

} INNER_LOOP_MONITORS_OUTPUT_STRUCT;







typedef struct
{
    MONITOR_STRUCT roll;
    MONITOR_STRUCT pitch;

    PERSISTENT1SHOT_STRUCT pos;
    BOOLEAN unit_delay;
    ROS_FLIPFLOP_STRUCT ros_flip_flop;

} INNER_LOOP_MONITORS_STATE_STRUCT;







typedef struct
{
    INNER_LOOP_MONITORS_COEFF_STRUCT *coeff_ptr;
    INNER_LOOP_MONITORS_INPUT_STRUCT input;
    INNER_LOOP_MONITORS_OUTPUT_STRUCT output;
    INNER_LOOP_MONITORS_STATE_STRUCT state;

} INNER_LOOP_MONITORS_STRUCT;





void Inner_Loop_Monitors_Initialize(INNER_LOOP_MONITORS_STRUCT *st_ptr, INNER_LOOP_MONITORS_COEFF_STRUCT *coeff_ptr);
void Inner_Loop_Monitors_Set_ADP_Command(INNER_LOOP_MONITORS_STRUCT *st_ptr, CYCLIC_STRUCT *adp_command);
void Inner_Loop_Monitors_Set_Actuator_Positions(INNER_LOOP_MONITORS_STRUCT *st_ptr, CYCLIC_STRUCT *actuator_positions);
void Inner_Loop_Monitors_Set_Rate(INNER_LOOP_MONITORS_STRUCT *st_ptr, VECTOR3 *rate);
void Inner_Loop_Monitors_Set_Accel_Z(INNER_LOOP_MONITORS_STRUCT *st_ptr, F32 accel_z);
void Inner_Loop_Monitors_Set_Euler_Angles(INNER_LOOP_MONITORS_STRUCT *st_ptr, EULER_ANGLES *euler_angles);
void Inner_Loop_Monitors_Set_UAR_Mode(INNER_LOOP_MONITORS_STRUCT *st_ptr, BOOLEAN uar_mode);
void Inner_Loop_Monitors_Set_Run(INNER_LOOP_MONITORS_STRUCT *st_ptr, BOOLEAN run);
void Inner_Loop_Monitors_Run(INNER_LOOP_MONITORS_STRUCT *st_ptr);

BOOLEAN Inner_Loop_Monitors_Get_ADP_Fail(INNER_LOOP_MONITORS_STRUCT *st_ptr);
BOOLEAN Inner_Loop_Monitors_Get_Horn(INNER_LOOP_MONITORS_STRUCT *st_ptr);
BOOLEAN Inner_Loop_Monitors_Get_Low_G(INNER_LOOP_MONITORS_STRUCT *st_ptr);
# 65 "..\\..\\..\\Model\\Inner_Loop\\Header\\MCP.h" 2
# 1 "..\\..\\..\\Model\\Common\\Header\\ScheduledRateLimiter.h" 1
# 54 "..\\..\\..\\Model\\Common\\Header\\ScheduledRateLimiter.h"
typedef struct
{
    LINTERP_STRUCT upper_linterp;
    LINTERP_STRUCT lower_linterp;

} SCHEDULEDRATELIMITER_COEFF_STRUCT;







typedef struct
{
    F32 previous_state;

} SCHEDULEDRATELIMITER_STATE_STRUCT;







typedef struct
{
    BOOLEAN reset;
    F32 ic;
    F32 control;
    F32 input;

} SCHEDULEDRATELIMITER_INPUT_STRUCT;







typedef struct
{
    F32 output;
    BOOLEAN saturated;

} SCHEDULEDRATELIMITER_OUTPUT_STRUCT;







typedef struct
{
    SCHEDULEDRATELIMITER_COEFF_STRUCT *coeff_ptr;
    SCHEDULEDRATELIMITER_STATE_STRUCT state;
    SCHEDULEDRATELIMITER_INPUT_STRUCT input;
    SCHEDULEDRATELIMITER_OUTPUT_STRUCT output;

} SCHEDULEDRATELIMITER_STRUCT;





void ScheduledRateLimiter_Initialize(SCHEDULEDRATELIMITER_STRUCT *st_ptr, SCHEDULEDRATELIMITER_COEFF_STRUCT *coeff_ptr);
void ScheduledRateLimiter_Set_Reset(SCHEDULEDRATELIMITER_STRUCT *st_ptr, BOOLEAN reset);
void ScheduledRateLimiter_Set_IC(SCHEDULEDRATELIMITER_STRUCT *st_ptr, F32 ic);
void ScheduledRateLimiter_Set_Control(SCHEDULEDRATELIMITER_STRUCT *st_ptr, F32 control);
void ScheduledRateLimiter_Set_Input(SCHEDULEDRATELIMITER_STRUCT *st_ptr, F32 input);
void ScheduledRateLimiter_Run(SCHEDULEDRATELIMITER_STRUCT *st_ptr);
F32 ScheduledRateLimiter_Get_Output(SCHEDULEDRATELIMITER_STRUCT *st_ptr);
BOOLEAN ScheduledRateLimiter_Get_Saturated(SCHEDULEDRATELIMITER_STRUCT *st_ptr);
# 66 "..\\..\\..\\Model\\Inner_Loop\\Header\\MCP.h" 2
# 79 "..\\..\\..\\Model\\Inner_Loop\\Header\\MCP.h"
typedef struct
{
    MCP_CONTROL_PRODUCER_COEFF_STRUCT control_coeff;
    INNER_LOOP_MONITORS_COEFF_STRUCT monitors_coeff;
    SCHEDULEDRATELIMITER_COEFF_STRUCT roll_scheduledRL_coeff;
    SCHEDULEDRATELIMITER_COEFF_STRUCT pitch_scheduledRL_coeff;
    TEST_PORT_COEFF_STRUCT roll_servo_testport;
    TEST_PORT_COEFF_STRUCT pitch_servo_testport;
    TEST_PORT_COEFF_STRUCT roll_cyclic_testport_coeff;
    TEST_PORT_COEFF_STRUCT pitch_cyclic_testport_coeff;
    F32 sin_wave_frequency;
    F32 sin_wave_amplitude;

} MCP_COEFF_STRUCT;







typedef struct
{
    CYCLIC_STRUCT feedback;

} MCP_OUTPUT_STRUCT;







typedef struct
{

    MCP_CONTROL_PRODUCER_STRUCT control_producer;
    INNER_LOOP_MONITORS_STRUCT monitors;
    SCHEDULEDRATELIMITER_STRUCT roll_scheduledRL;
    SCHEDULEDRATELIMITER_STRUCT pitch_scheduledRL;
    TEST_PORT_STRUCT roll_servo_testport;
    TEST_PORT_STRUCT pitch_servo_testport;
    TEST_PORT_STRUCT roll_cyclic_testport;
    TEST_PORT_STRUCT pitch_cyclic_testport;

 BOOLEAN roll_rate_limited;
 BOOLEAN pitch_rate_limited;

    BOOLEAN adp_fail_unit_delay;

} MCP_STATE_STRUCT;







typedef struct
{
    MCP_COEFF_STRUCT *coeff_ptr;


    MCP_OUTPUT_STRUCT output;
    MCP_STATE_STRUCT state;

} MCP_STRUCT;





void MCP_Initialize(MCP_COEFF_STRUCT *coeff_ptr);

void MCP_Set_Run(BOOLEAN run);
void MCP_Set_Accel_Z(F32 accel_Z);
void MCP_Set_Attitude(EULER_ANGLES *attitude);
void MCP_Set_Actuator_Positions(CYCLIC_STRUCT *actuator_positions);
void MCP_Set_Body_Rates(VECTOR3 *rates);
void MCP_Set_Euler_Rates(const EULER_RATES *euler_rates);
void MCP_Set_ADP_Commands(CYCLIC_STRUCT *adp_commands);
void MCP_Set_Disable_ADP(BOOLEAN disable_ADP);
void MCP_Set_Triplex_Fault(BOOLEAN triplex_fault);

void MCP_Run(void);

void MCP_Get_Inner_Loop_Feedback(CYCLIC_STRUCT *feedback);
BOOLEAN MCP_Get_UAR_Mode(void);
BOOLEAN MCP_Get_Run_ADP(void);
BOOLEAN MCP_Get_Phi_Valid(void);
BOOLEAN MCP_Get_Theta_Valid(void);

void MCP_Get_Actuator_Commands(CYCLIC_STRUCT *actr_cmds);
BOOLEAN MCP_Get_Horn(void);
BOOLEAN MCP_Get_Low_G(void);
# 6 "main_MCP.c" 2
# 1 "..\\..\\..\\Model\\Inner_Loop\\Header\\Servo_Loop.h" 1
# 64 "..\\..\\..\\Model\\Inner_Loop\\Header\\Servo_Loop.h"
# 1 "..\\..\\..\\Model\\Common\\Header\\SaturationDynVF.h" 1
# 53 "..\\..\\..\\Model\\Common\\Header\\SaturationDynVF.h"
typedef struct
{
    F32 K_Ts;
    F32 epsilon;

} SATURATIONDYNVF_COEFF_STRUCT;






typedef struct
{
    F32 IC;
    F32 input;
    F32 upper_sat_limit;
    F32 lower_sat_limit;
    BOOLEAN reset;

} SATURATIONDYNVF_INPUT_STRUCT;







typedef struct
{
    F32 output;
    BOOLEAN inv;
    BOOLEAN satLo;
    BOOLEAN satHi;

} SATURATIONDYNVF_OUTPUT_STRUCT;
# 109 "..\\..\\..\\Model\\Common\\Header\\SaturationDynVF.h"
typedef struct
{
    SATURATIONDYNVF_COEFF_STRUCT *coeff;

    SATURATIONDYNVF_INPUT_STRUCT input;
    SATURATIONDYNVF_OUTPUT_STRUCT output;

} SATURATIONDYNVF_STRUCT;





void SaturationDynVF_Initialize(SATURATIONDYNVF_STRUCT *st_ptr, SATURATIONDYNVF_COEFF_STRUCT *coeff);
void SaturationDynVF_Set_Input(SATURATIONDYNVF_STRUCT *st_ptr, F32 input);
void SaturationDynVF_Set_IC(SATURATIONDYNVF_STRUCT *st_ptr, F32 ic);
void SaturationDynVF_Set_Reset(SATURATIONDYNVF_STRUCT *st_ptr, BOOLEAN reset);
void SaturationDynVF_Set_Upper_Sat_Limit(SATURATIONDYNVF_STRUCT *st_ptr, F32 upper_sat_limit);
void SaturationDynVF_Set_Lower_Sat_Limit(SATURATIONDYNVF_STRUCT *st_ptr, F32 lower_sat_limit);
void SaturationDynVF_Run(SATURATIONDYNVF_STRUCT *st_ptr);
F32 SaturationDynVF_Get_Output(SATURATIONDYNVF_STRUCT *st_ptr);
BOOLEAN SaturationDynVF_Get_Inverted(SATURATIONDYNVF_STRUCT *st_ptr);
BOOLEAN SaturationDynVF_Get_SatLo(SATURATIONDYNVF_STRUCT *st_ptr);
BOOLEAN SaturationDynVF_Get_SatHi(SATURATIONDYNVF_STRUCT *st_ptr);
# 65 "..\\..\\..\\Model\\Inner_Loop\\Header\\Servo_Loop.h" 2








typedef struct
{
    TEST_PORT_COEFF_STRUCT testport_case1;
    SATURATIONDYNVF_COEFF_STRUCT SaturationDynVF;
    REINTICHS_COEFF_STRUCT ReInt_ICHS;

    F32 k_ts;
    F32 k;
    F32 k2;
    F32 k3;
    F32 k4;
    F32 max_current;
    F32 rate_limiter_upper_limit;
    F32 rate_limiter_lower_limit;

} SERVO_LOOP_COEFF_STRUCT;







typedef struct
{
    F32 actr_posn;
    F32 actr_current;
    F32 rel_posn_cmd;

} SERVO_LOOP_INPUT_STRUCT;







typedef struct
{
    F32 motor_voltage_cmd;
    BOOLEAN curr_sat_ul;
    BOOLEAN curr_sat_ll;
    BOOLEAN rl_sat;

} SERVO_LOOP_OUTPUT_STRUCT;







typedef struct
{
    TEST_PORT_STRUCT testport;
    SATURATIONDYNVF_STRUCT SaturationDynVF;
    REINTICHS_STRUCT ReInt_ICHS;

    F32 servo_error;
    F32 prev_cmd;
    F32 prev_posn;
    F32 prev_rl_output;
    BOOLEAN reset;
    BOOLEAN take_half_step;


        BOOLEAN motor_voltage_rate_limited;


} SERVO_LOOP_STATE_STRUCT;







typedef struct
{
    SERVO_LOOP_COEFF_STRUCT *coeff;
    SERVO_LOOP_INPUT_STRUCT input;
    SERVO_LOOP_OUTPUT_STRUCT output;
    SERVO_LOOP_STATE_STRUCT state;

} SERVO_LOOP_STRUCT;





void Servo_Loop_Set_Actuator_Position(SERVO_LOOP_STRUCT *st_ptr, F32 Actuator_Position);
void Servo_Loop_Set_Actuator_Current(SERVO_LOOP_STRUCT *st_ptr, F32 Actuator_Current);
void Servo_Loop_Set_Relative_Position_Command(SERVO_LOOP_STRUCT *st_ptr, F32 Relative_Position_Command);
void Servo_Loop_Set_Reset(SERVO_LOOP_STRUCT *st_ptr, BOOLEAN reset);
F32 Servo_Loop_Get_Motor_Voltage_Command(SERVO_LOOP_STRUCT *st_ptr);
BOOLEAN Servo_Get_CurrSatUL(SERVO_LOOP_STRUCT * servo_loop_ptr);
BOOLEAN Servo_Get_CurrSatLL(SERVO_LOOP_STRUCT * servo_loop_ptr);
BOOLEAN Servo_Get_PLSat(SERVO_LOOP_STRUCT * servo_loop_ptr);
BOOLEAN Servo_Get_PLInv(SERVO_LOOP_STRUCT * servo_loop_ptr);
BOOLEAN Servo_Get_RLSat(SERVO_LOOP_STRUCT * servo_loop_ptr);

void Servo_Loop_Initialize(SERVO_LOOP_STRUCT *st_ptr, SERVO_LOOP_COEFF_STRUCT *coeff_st_ptr);
void Servo_Loop_Run(SERVO_LOOP_STRUCT *st_ptr);


void Servo_Update_Servo_Error(SERVO_LOOP_STRUCT * servo_loop_ptr, F32 current_error);
F32 Servo_Get_Servo_Error(SERVO_LOOP_STRUCT * servo_loop_ptr);
BOOLEAN Servo_Is_Servo_Error(SERVO_LOOP_STRUCT * servo_loop_ptr);
# 7 "main_MCP.c" 2

static TELEMETRY_LOG_STRUCT telem_data = {0};
static MCP_COEFF_STRUCT coeff = {0};
static SERVO_LOOP_COEFF_STRUCT servo_loop_coeff = {0};

int main()
{
    return 0;
}
