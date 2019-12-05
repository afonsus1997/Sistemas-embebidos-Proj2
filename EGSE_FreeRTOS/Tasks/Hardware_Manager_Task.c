#include "Hardware_Manager_Task.h"


ETPUnion_t hwMSG;


void HandleADCRequest(ETPUnion_t *msg){
    if(LastReadings.ADCs[msg->etpEGSEAdc.ADCsingle[ADCNum]] != NULL)
        msg->etpEGSEAdc.ADCsingle[ADCVal] = LastReadings.ADCs[msg->etpEGSEAdc.ADCsingle[ADCNum]];
    //else
        //return error reply
    return;
}

void handleHWMsg(ETPUnion_t * msg){
    ETPHeader_t * header = &msg->header;
    switch (header->opcode) {
        case ETPOpcode_PSUSingle :
            PSUcmd((ETPPSUCmd_t * ) msg);
            break;
        case ETPOpcode_ADCSingle :
            HandleADCRequest((ETPEGSEADCCmd_t * ) msg);
            break;
        default:
            break;
    }
}



static void vHardwareManagerTask(void *pvParameters)
{
//    hwMSG.etppsu.PSUsingle[PSUNum] = 3;
//    hwMSG.etppsu.PSUsingle[PSUState] = 1;
//    hwMSG.etppsu.header.opcode = ETPOpcode_PSUSingle;
    while (1)
    {
        xQueueReceive(g_HardwareTaskQueueRX, &hwMSG, portMAX_DELAY);
        handleHWMsg(&hwMSG);
    }
    vTaskDelete( NULL );
}




uint32_t vHardwareManagerTaskINIT(void)
{
    //Create Hardware Queues
    g_HardwareTaskQueueTX = xQueueCreate(HARDWARE_QUEUE_ITEM_SIZE, HARDWARE_QUEUE_QUEUE_SIZE);
    g_HardwareTaskQueueRX = xQueueCreate(HARDWARE_QUEUE_ITEM_SIZE, HARDWARE_QUEUE_QUEUE_SIZE);



    SPIinit();

    vHardwareIOInit();

    //init GPIO expanders
    GPIOexBegin();

    //init ADC's
    ADCinit();


//    LCDinit();



    if (xTaskCreate(vHardwareManagerTask, (const portCHAR *)"HardwareManager", HardwareManagerTaskSTACKSIZE, NULL,
            tskIDLE_PRIORITY + PRIORITY_HARDWARE_TASK , NULL) != pdTRUE)
    {
        return (1);
    }

    //
    // Success.
    //
    return (0);
}

