//#define USBDEBUG

#include "uart.h"

//static uartmsg_t uartmsg;

void EGSE_sendUARTRPI(ETPUnion_t *msg){
    uint8_t size = sizeof(msg->header) + msg->header.size;
    unsigned char *buff = &msg->raw[0];
    while(size--){
        UARTCharPut(UART0_BASE, *buff++);
    }
}

void EGSE_sendUART3(ETPUnion_t *msg){
    const size_t size = msg->header.size;
    const uint8_t *data = msg->uart0.data;
    size_t i;
    for(i = 0 ; i < size ; i+=1){
        UARTCharPut(UART3_BASE, data[i]);
    }
}

static void vUartRPITask(void *pvParameters){
    while(1){
        xSemaphoreTake( xsUARTin, portMAX_DELAY  );
//        UARTprintf("[EGSE Hardware Task] - Got uart interrupt\n");
            //semaphore released
            //uartmsg_t msg = {.rxIdxWrite = 0, .rxIdxWrite = 0, .rxSize = 0};// = uartmsg; //pointer to msg structure
            ETPUnion_t msg;
            int16_t idx = 0;
            while (UARTCharsAvail(UART0_BASE)) {//while uart buf is not empty
                msg.raw[idx++] = UARTCharGetNonBlocking(UART0_BASE);   //put byte into msg
                //msg.rxIdxWrite == (msg.rxIdxWrite + 1) % sizeof(msg.rxBuff); //increment write index
                //msg.rxSize += 1;                                               //increment msg size
            }


            //msg.header.opcode = ETPOpcode_Sync;
            //send msg to queue

            //UARTprintf("[UART Task] - Sent Message to UART queue\n");
            xQueueSend(g_pUartRPIQueue, (void *) &msg, portMAX_DELAY);


    }

}


void UARTInt0Handler(void)
{
    uint32_t ui32Status;
    ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

    ROM_UARTIntClear(UART0_BASE, ui32Status);

    ui32Status = UARTIntStatus(UART0_BASE, true);

    UARTIntClear(UART0_BASE, ui32Status);


    xSemaphoreGiveFromISR( xsUARTin, &xHigherPriorityTaskWoken );

    //if(xHigherPriorityTaskWoken == pdTRUE)
        //portYIELD_FROM_ISR(pdFALSE);
}


uint32_t UartRPITaskInit(void)
{
    g_pUartRPIQueue = xQueueCreate(UartRPI_QUEUE_SIZE, UartRPI_ITEM_SIZE);


    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    //UARTFlowControlSet(UART0_BASE, UART_FLOWCONTROL_TX | UART_FLOWCONTROL_RX);


    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    ROM_UARTConfigSetExpClk(UART0_BASE, 16000000, 57600,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                 UART_CONFIG_PAR_NONE));


    ROM_GPIOPinConfigure(GPIO_PC6_U3RX);
    ROM_GPIOPinConfigure(GPIO_PC7_U3TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    ROM_UARTConfigSetExpClk(UART3_BASE, 16000000, 115200,
                                    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                     UART_CONFIG_PAR_NONE));


    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTClockSourceSet(UART3_BASE, UART_CLOCK_PIOSC);


    //UARTStdioConfig(3, 115200, 16000000);

    UARTStdioConfig(3, 57600, ROM_SysCtlClockGet());
    //for(;;)
    UARTprintf("\n\n[UART Task] - UART Initialization!\n");


    IntEnable(INT_UART0);
    //IntEnable(INT_UART3);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT);

    UARTIntRegister(UART0_BASE, &UARTInt0Handler);

    xsUARTin = xSemaphoreCreateBinary();

    if(xTaskCreate(vUartRPITask, (const portCHAR *)"UartRPI", UartRPITASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_I2C_RPI_TASK , NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}



