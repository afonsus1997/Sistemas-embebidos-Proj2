

#include "EGSE_Manager_Task.h"






static void vEGSEManagerTask(void *pvParameters){

    uartmsg_t sUartRcv;

    while(1){


        if(xQueueReceive(g_pUartRPIQueue, &sUartRcv, portMAX_DELAY) == pdPASS)

            UARTprintf("\n\nRecieved message from uart queue\n");

    }

}





uint32_t vEGSEManagerTaskINIT(void)
{


    if(xTaskCreate(vEGSEManagerTask, (const portCHAR *)"EGSE_Manager", EGSEManagerSTACKSIZE, NULL,
                   tskIDLE_PRIORITY + PRIORITY_EGSE_MANAGER_TASK, NULL) != pdTRUE)
    {
        return(1);
    }

    //
    // Success.
    //
    return(0);
}



