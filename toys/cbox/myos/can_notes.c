struct {
    FIFO_STRUCT FIFO
    U8 FIFO_data[CAN_FIFO_SIZE]
} CAN_FIFOS[NUM_CHANNELS];

CAN_Init
    FIFO_Init(size, CAN_FIFOS[i].FIFO_data, &CAN_FIFO[i].FIFO);
CAN_Read
    IRQ Off
    size = FIFO_Dequeue(data, max_size, &CAN_FIFO[rx_channel].FIFO)
    IRQ On
    return size
CAN_Write
    IRQ Off
    FIFO_Enqueue(data, max_size, &CAN_FIFO[tx_channel].FIFO)
    if CAN idle Send_Next
    IRQ On
CAN_Irqh
    TX: Send_Next
    RX: Recv_Next
Send_Next
    load CAN Msg
    Dequeue(FIFO[tx_channel])
    Send to HW
Recv_Next
    Recv from HW
    if my ID and len > 0
        Enqueue(FIFO[rx_channel])


