#include "Hardware_Manager_Task.h"


HWUnion_t hwMSG;


void handleHWMsg(HWUnion_t * msg){
    HWHeader_t * header = &msg->header;
    switch (header->opcode) {
        case HWOpcode_PSUall :
            PSUcmd(HWOpcode_PSUall, msg);
            break;
        case HWOpcode_PSUSingle :
            PSUcmd(HWOpcode_PSUSingle, msg);
            break;
        default:
            break;
    }
}



static void vHardwareManagerTask(void *pvParameters)
{
    while (1)
    {
        xQueueReceive(g_HardwareTaskQueueRX, &hwMSG, portMAX_DELAY);
        handleHWMsg(&hwMSG);
    }

}




uint32_t vHardwareManagerTaskINIT(void)
{
    //Create Hardware Queues
    g_HardwareTaskQueueTX = xQueueCreate(HARDWARE_QUEUE_ITEM_SIZE, HARDWARE_QUEUE_QUEUE_SIZE);
    g_HardwareTaskQueueRX = xQueueCreate(HARDWARE_QUEUE_ITEM_SIZE, HARDWARE_QUEUE_QUEUE_SIZE);




    SPIinit();

    //initialize tiva gpios
    vHardwareIOInit();


    //init GPIO expanders
    GPIOexBegin();



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

