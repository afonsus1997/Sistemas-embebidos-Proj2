#include "EGSE_Manager_Task.h"

static void vEGSEManagerTask(void *pvParameters){

    //uartmsg_t sUartRcv;

    ETPUnion_t sUartRcv ;
    ETPUnion_t * test;

    static size_t endOfMsg = sizeof(ETPHeader_t); //needed later to check if msg has header
    bool hasHeader;


    while(1){

        xQueueReceive(g_pUartRPIQueue, &sUartRcv, portMAX_DELAY);
        handle_EPTMsg(&sUartRcv);

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



