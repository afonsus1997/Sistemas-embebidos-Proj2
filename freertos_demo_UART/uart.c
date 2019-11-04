

#include "uart.h"

static void UartRPITask(void *pvParameters){
    for(;;);
}


uint32_t UartRPITaskInit(void)
{
    g_pUartRPIQueue = xQueueCreate(UartRPI_QUEUE_SIZE, UartRPI_ITEM_SIZE);



    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    ROM_GPIOPinConfigure(GPIO_PC6_U3RX);
    ROM_GPIOPinConfigure(GPIO_PC7_U3TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);


    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTClockSourceSet(UART3_BASE, UART_CLOCK_PIOSC);


    UARTStdioConfig(0, 115200, 16000000);
    UARTStdioConfig(3, 115200, 16000000);


    if(xTaskCreate(UartRPITask, (const portCHAR *)"UartRPI", UartRPITASKSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_UartRPI_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}



