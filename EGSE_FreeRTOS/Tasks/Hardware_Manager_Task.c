#include "Hardware_Manager_Task.h"


HWUnion_t hwMSG;


void handleHWMsg(HWUnion_t * msg){
    HWHeader_t * header = &msg->header;
    switch (header->opcode) {
        case HWOpcode_PSUSingle :
            PSUcmd(HWOpcode_PSUSingle, msg);
            break;
        default:
            break;
    }
}



static void vHardwareManagerTask(void *pvParameters)
{
    hwMSG.PSU.PSUsingle[PSUNum] = 3;
    hwMSG.PSU.PSUsingle[PSUState] = 1;
    hwMSG.PSU.header.opcode = HWOpcode_PSUSingle;
//    while (1)
//    {
        //xQueueReceive(g_HardwareTaskQueueRX, &hwMSG, portMAX_DELAY);
        //handleHWMsg(&hwMSG);
//    }
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

