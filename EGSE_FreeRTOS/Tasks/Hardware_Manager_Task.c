#include "Hardware_Manager_Task.h"


ETPUnion_t hwMSG;

uint8_t SW_EN_map[6] = {SW_EN1, SW_EN2, SW_EN3, SW_EN4, SW_EN5, SW_EN6};


void PSUcmd(ETPPSUCmd_t * PSUmsg){
    UARTprintf((uint8_t)PSUmsg->id);printf(" to  "); UARTprintf((uint8_t)PSUmsg->state);
    GPIOexGPIOWrite(1, SW_EN_map[(uint8_t)PSUmsg->id], (uint8_t)PSUmsg->state);
}



void HandleADCRequest(ETPUnionHW_t *msg){
    if(LastReadings.ADCs[msg->etpEGSEAdc.ADCNum] != NULL)
        msg->etpEGSEAdc.ADCVal = LastReadings.ADCs[msg->etpEGSEAdc.ADCNum];
    //else
        //return error reply
    return;
}

void handleHWMsg(ETPUnion_t * msg){

    ETPUnionHW_t * hwMSG;
    hwMSG->header.opcode = &msg->header;
    UARTprintf("[EGSE Hardware Task] - Handling Hardware\n");
    switch (hwMSG->header.opcode) {
        case ETPOpcode_PSUSingle :
            UARTprintf("[EGSE Hardware Task] - Setting PSU");
            hwMSG = &msg->etppsu;
            PSUcmd(hwMSG);
            break;
        case ETPOpcode_ADCSingle :
            hwMSG = &msg->etpEGSEAdc;
            HandleADCRequest(hwMSG);
            xQueueSend(g_HardwareTaskQueueFromHardware, (void *) &hwMSG, portMAX_DELAY);
            break;
        default:
            break;
    }
}



static void vHardwareManagerTask(void *pvParameters)
{
    while (1)
    {
        xQueueReceive(g_HardwareTaskQueueToHardware, &hwMSG, portMAX_DELAY);
        handleHWMsg(&hwMSG);
    }
    vTaskDelete( NULL );
}




uint32_t vHardwareManagerTaskINIT(void)
{
    //Create Hardware Queues
    g_HardwareTaskQueueToHardware = xQueueCreate(HARDWARE_QUEUE_ITEM_SIZE, HARDWARE_QUEUE_QUEUE_SIZE);
    g_HardwareTaskQueueFromHardware = xQueueCreate(HARDWARE_QUEUE_ITEM_SIZE, HARDWARE_QUEUE_QUEUE_SIZE);



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

