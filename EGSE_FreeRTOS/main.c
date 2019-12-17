
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "led_task.h"
#include "switch_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//#include "uart.h"
//#include "EGSE_Manager_Task.h"
extern uint32_t UartRPITaskInit(void);
extern uint32_t vEGSEManagerTaskINIT(void);
extern uint32_t vHardwareManagerTaskINIT(void);
extern uint32_t vAcquisitionTaskINIT(void);

//windows
//https://sites.google.com/site/luiselectronicprojects/tutorials/tiva-tutorials

//xSemaphoreHandle g_pUARTSemaphore;

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    UARTprintf("[FreeRTOS] - Application Stack Overflow!\n");

    for(;;);

}


//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
int main(void)
{
    //
    // Set the clocking to run at 50 MHz from the PLL.
    //

    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);



    if(UartRPITaskInit() != 0)
        for(;;);

    if(vEGSEManagerTaskINIT()!= 0)
        for(;;);

    if(vHardwareManagerTaskINIT()!= 0)
        for(;;);

//    if(vAcquisitionTaskINIT()!= 0)
//        for(;;);





    IntMasterEnable();
    //
    // Start the scheduler.  This should not return.
    //
    UARTprintf("[FreeRTOS] - Starting scheduler...\n");

    vTaskStartScheduler();

    //
    // In case the scheduler returns for some reason, print an error and loop
    // forever.
    //

    while(1)
    {
    }
}
