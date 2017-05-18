#if 0
void mcp25625_Read
(
        uint8_t reg,
        uint8_t *buffer,
        uint8_t count
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( CMD_READ );
    MCP25625_hal_cmd( reg );
    MCP25625_hal_read( buffer, count );
    MCP25625_hal_cs( 1 );
}

void mcp25625_Write
(
        uint8_t reg,
        uint8_t *buffer,
        uint8_t count
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( CMD_WRITE );
    MCP25625_hal_cmd( reg );
    MCP25625_hal_write( buffer, count );
    MCP25625_hal_cs( 1 );
}

void mcp25625_Modify
(
        uint8_t reg,
        uint8_t mask,
        uint8_t *value
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( CMD_BIT_MODIFY );
    MCP25625_hal_cmd( reg );
    MCP25625_hal_cmd( mask );
    MCP25625_hal_cmd( *value );
    MCP25625_hal_cs( 1 );
}

void mcp25625_Tx
(
        uint8_t reg,
        uint8_t *buffer,
        uint8_t len
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( reg );
    MCP25625_hal_write( buffer, len );
    MCP25625_hal_cs( 1 );
}

void mcp25625_Rx
(
        uint8_t reg,
        uint8_t *buffer,
        uint8_t len
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( reg );
    MCP25625_hal_read( buffer, len );
    MCP25625_hal_cs( 1 );
}


int mcp25625_HW_Init
(
        void
)
{
    reg.address = 0;
    reg.value = 0;

    MCP25625_hal_init();
    mcp25625_pin_reset();
    MCP25625_hal_cs( 1 );
    MCP25625_hal_stb( 0 );

    return 0;
}

int mcp25625_Pin_Reset
(
        void
)
{
    MCP25625_hal_rst( 1 );
    Delay_ms( 10 );
    MCP25625_hal_rst( 0 );
    Delay_ms( 10 );
    MCP25625_hal_rst( 1 );
    Delay_ms( 10 );

    return 0;
}

int mcp25625_Hw_Reset
(
        void
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( CMD_RESET );
    MCP25625_hal_cs( 1 );

    return 0;
}

int mcp25625_Hw_RTS_Ctl
(
        TXB_t line
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( CMD_RTS | MCP25625_RTS( line ) );
    MCP25625_hal_cs( 1 );

    return 0;
}
CAN_STATUS mcp25625_Hw_Status
(
        void
)
{
    CAN_STATUS status;

    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( CMD_READ_STAT );
    MCP25625_hal_read( ( uint8_t* )&status, 1 );
    MCP25625_hal_cs( 1 );

    return status;
}

void mcp25625_hw_rx_status
(
        rx_fstatus *status
)
{
    MCP25625_hal_cs( 0 );
    MCP25625_hal_cmd( CMD_RX_STAT );
    MCP25625_hal_read( ( uint8_t* )status, 1 );
    MCP25625_hal_cs( 1 );
}

int mcp25625_hw_ctl_set
(
        void *value
)
{
    if( *( ( uint8_t* )value + 1 ) != 0x30 )
    {
        memcpy( ( void* )&reg, value, sizeof( reg_t ) );
        hw_write( reg.address, &reg.value, 1 );
    }
    else {
        memcpy( ( void* )&reg, value, sizeof( reg_t ) );
        hw_write( CTL_TXB( reg.buffer, reg.address ), &reg.value, 1 );
    }

    return 0;
}

int mcp25625_hw_ctl_update
(
        void *value
)
{
    if( *( ( uint8_t* )value + 1 ) != 0x30 )
    {
        memcpy( ( void* )&reg, value, sizeof( reg_t ) );
        hw_modify( reg.address, reg.mask, &reg.value );
    }
    else {
        memcpy( ( void* )&reg, value, sizeof( reg_t ) );
        hw_modify( CTL_TXB( reg.buffer, reg.address ), reg.mask, &reg.value );
    }

    return 0;
}

int mcp25625_hw_ctl_get
(
        void *result
)
{
    if( *( ( uint8_t* )result + 1 ) != 0x30 )
    {
        memcpy( ( void* )&reg, result, sizeof( reg_t ) );
        hw_read( reg.address, &reg.value, 1 );
    }
    else {

        memcpy( ( void* )&reg, result, sizeof( reg_t ) );
        hw_read( CTL_TXB( reg.buffer, reg.address ), &reg.value, 1 );
    }

    memcpy( result, &reg.value, 1 );

    return 0;
}

int mcp25625_hw_data_set
(
        TXB_t num,
        mcp25625_transfer *tx_data
)
{
    hw_tx( CMD_LOAD_TX + MCP25625_TX( num ), ( uint8_t* )tx_data, 13 );

    return 0;
}

int mcp25625_hw_data_get
(
        RXB_t num,
        mcp25625_transfer *rx_data
)
{
    hw_rx( CMD_READ_RX + MCP25625_RX( num ), ( uint8_t* )rx_data, 13 );

    return 0;
}

int mcp25625_hw_filter_set
(
        RXF_t reg,
        mcp25625_id *filter
)
{
    hw_write( MCP25625_FILTER( reg ), ( uint8_t* )filter, 4 );

    return 0;
}

int mcp25625_hw_mask_set
(
        RXB_t reg,
        mcp25625_id *mask
)
{
    hw_write( MCP25625_MASK( reg ), ( uint8_t* ) mask, 4 );

    return 0;
}

#endif