# 1 "main_MCP.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 331 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "main_MCP.c" 2



# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h" 1
# 47 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h" 1
# 42 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/HeliTrak_Constants.h" 1
# 41 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/HeliTrak_Constants.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/HeliTrak_Natural_Constants.h" 1
# 42 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/HeliTrak_Constants.h" 2
# 43 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h" 2








typedef unsigned char U8, u8;
# 61 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef signed char S8, s8;
# 71 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef unsigned short U16, u16;
# 81 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef signed short S16, s16;
# 91 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef unsigned long UL32, ul32, U32, u32;
# 101 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef signed long SL32, sl32, S32, s32;
# 111 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef unsigned long long UL64, ul64, U64, u64;
# 121 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef signed long long SL64, sl64, S64, s64;
# 131 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef float F32, f32;
# 141 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
typedef u8 BOOLEAN;
# 163 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
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
# 281 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\HeliTrak_Types.h"
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
# 48 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\User_Input.h" 1
# 65 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\User_Input.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h" 1
# 55 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Target_Signals.h" 1
# 107 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Target_Signals.h"
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
# 56 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Stream_IO.h" 1
# 83 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Stream_IO.h"
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
# 122 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Stream_IO.h"
typedef enum
{
    IOCTL_TX_DISABLE,
    IOCTL_TX_ENABLE,
    IOCTL_RX_DISABLE,
    IOCTL_RX_ENABLE,
    IOCTL_TX_IS_BUSY,
    IOCTL_ENABLE_HW_FIFO,
    IOCTL_FLUSH_RX_BUFFER
# 145 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Stream_IO.h"
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
# 57 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Debug_Support.h" 1
# 52 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Debug_Support.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Target_Software_Defs_Common.h" 1
# 53 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Debug_Support.h" 2
# 63 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Debug_Support.h"
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
# 253 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Debug_Support.h"
        extern void _assert(int, const char *);
        extern void _abort_msg(const char *);
# 58 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h" 2

# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals_GPIO_CM3.h" 1
# 54 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals_GPIO_CM3.h"
typedef struct
{
    U32 port;

    U8 pin;

} PIN_GPIO_HW_STRUCT;






typedef void (*INTERRUPT_CALLBACK_PTR)(void * instance_ID);
# 105 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals_GPIO_CM3.h"
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
# 60 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals_ADC_CM3.h" 1
# 55 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals_ADC_CM3.h"
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
# 61 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h" 2
# 83 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h"
typedef enum
{
    SIGNALS_PWM_UNIT_0,
    SIGNALS_PWM_UNIT_1,
    SIGNALS_PWM_UNIT_2,
    SIGNALS_PWM_UNIT_3,

    SIGNALS_PWM_UNIT_NUM_OF,

    SIGNALS_PWM_NULL

} SIGNALS_PWM_UNIT_ENUM;
# 103 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Signals.h"
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
# 66 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\User_Input.h" 2

# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Model\\Common\\Header\\Momentary_Switch.h" 1
# 42 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Model\\Common\\Header\\Momentary_Switch.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Model\\Common\\Header/Persistent1Shot.h" 1
# 53 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Model\\Common\\Header/Persistent1Shot.h"
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
# 43 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Model\\Common\\Header\\Momentary_Switch.h" 2
# 53 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Model\\Common\\Header\\Momentary_Switch.h"
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
# 68 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\User_Input.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/User_Input_HW.h" 1
# 77 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/User_Input_HW.h"
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
# 166 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/User_Input_HW.h"
USER_INPUT_FLAGS User_Input_Run_HW(void);
void User_Input_Show_Flags(USER_INPUT_FLAGS cmdflags, char *tag);
# 69 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\User_Input.h" 2
# 81 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\User_Input.h"
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
# 49 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Target.h" 1
# 74 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Target.h"
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
# 95 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Target.h"
typedef struct
{
    PIN_GPIO_HW_STRUCT bit_0;

    PIN_GPIO_HW_STRUCT bit_1;

} TARGET_ID_HW_STRUCT;
# 110 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Target.h"
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
# 154 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Target.h"
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
# 201 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Target.h"
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
# 50 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h" 1
# 52 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Math_Utils.h" 1
# 86 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Math_Utils.h"
typedef U8 CKSUMTYPE;
# 378 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Math_Utils.h"
F32 PiRads(F32 value);
CKSUMTYPE Checksum_Compute(void * buffer, U16 length);
F32 Hex_To_Float(U32 hex);


F32 ZeroTo2PiRads(F32 angle);
# 53 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h" 2


# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Fault_Mgmt.h" 1
# 84 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Fault_Mgmt.h"
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Fault_Defs.h" 1
# 68 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Fault_Defs.h"
typedef enum
{
# 81 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Fault_Defs.h"
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
# 85 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Fault_Mgmt.h" 2
# 108 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Fault_Mgmt.h"
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
# 56 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Annunciators.h" 1
# 104 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Annunciators.h"
typedef struct
{
    F32 on_duration_seconds;
    F32 off_duration_seconds;
    U32 num_repeats;
    BOOLEAN end_state;

} ANNUNCIATORS_PATTERN_COEFF_STRUCT;
# 120 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header/Annunciators.h"
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
# 57 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h" 2
# 84 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
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
# 114 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
    typedef enum
    {
        MCP2ADP_PACKET_FLIGHT_DATA,
        MCP2ADP_PACKET_POST_DATA,
        MCP2ADP_PACKET_MX_VOTE,

        MCP2ADP_PACKET_LAST

    } MCP2ADP_PACKET_TYPE;
# 132 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
    typedef enum
    {
        ADP2MCP_PACKET_FLIGHT_DATA,
        ADP2MCP_PACKET_POST_DATA,



        ADP2MCP_PACKET_LAST

    } ADP2MCP_PACKET_TYPE;
# 151 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
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
# 174 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
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
# 199 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
    typedef struct
    {
        ADP2MCP_PACKET_TYPE packet_type;
    } PACKET_TYPE_STRUCT;
# 211 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
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
# 244 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
    typedef struct
    {
        MCP2ADP_PACKET_TYPE packet_type;
        U32 frame_number;
        BOOLEAN vote;
        BOOLEAN valid;

    } MSG_MX_VOTE_STRUCT;
# 260 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
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
# 282 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
    typedef union
    {
        PACKET_TYPE_STRUCT packet_base;
        MSG_ADP2MCP_STRUCT flight_data;
        POST_DATA_STRUCT POST_data;
        MSG_MX_VOTE_STRUCT mx_vote;

    } MSG_ADP2MCP_UNION;
# 300 "C:\\Helitrak\\Servo200_FLT\\SwDev\\Common\\Header\\Messaging.h"
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
# 51 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h" 2
# 1 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header/Target_Software_Defs_MCP.h" 1
# 52 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h" 2
# 88 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h"
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
# 132 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h"
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
# 157 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h"
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
# 239 "C:\\Helitrak\\Servo200_FLT\\SwDev\\MCP\\Header\\Telemetry_Log.h"
RETURN_TYPE Telemetry_Log_Run(void);

TELEMETRY_LOG_STRUCT * Telemetry_Log_Get_Telem_Structure();
void Telemetry_Log_Set_IL_Monitors(U32 monitor_flags);
void Telemetry_Log_Set_Servo_Loop_Flags(U32 servo_loop_flags);
void Telemetry_Log_Set_Differential_Pressures(F32 value, U32 sensor);
void Telemetry_Log_Enable_Raw_Data(BOOLEAN enable);
# 5 "main_MCP.c" 2

static TELEMETRY_LOG_STRUCT telem_data = {0};

int main()
{
    return 0;
}
