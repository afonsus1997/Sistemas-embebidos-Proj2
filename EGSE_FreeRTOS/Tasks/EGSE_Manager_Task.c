#include "EGSE_Manager_Task.h"

static void vEGSEManagerTask(void *pvParameters){

    //uartmsg_t sUartRcv;

    ETPUnion_t sUartRcv ;
    ETPUnionHW_t sHWRcv;
//    ETPUnion_t * test;

    static size_t endOfMsg = sizeof(ETPHeader_t); //needed later to check if msg has header
    bool hasHeader;
    portBASE_TYPE xStatusRX;
    portBASE_TYPE xStatusTX;

    while(1){
        xStatusRX = xQueueReceive(g_pUartRPIQueue, &sUartRcv, 0);
//        sUartRcv.header.opcode= ETPOpcode_ADCSingle;
//        sUartRcv.header.opcode= ETPOpcode_PSUSingle;
//        sUartRcv.etpEGSEAdc.ADCNum = 1;
        if(xStatusRX == pdTRUE)
            handle_EPTMsg(&sUartRcv);


        //check if theres hw messages to send back to uart
        xStatusTX = xQueueReceive(g_HardwareTaskQueueFromHardware, &sHWRcv, 0);
        if(xStatusTX == pdTRUE)
            HandleHWRX(&sHWRcv);
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



