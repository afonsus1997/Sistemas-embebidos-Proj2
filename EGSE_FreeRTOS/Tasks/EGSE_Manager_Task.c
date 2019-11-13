

#include "EGSE_Manager_Task.h"



static void handle_EPTMsg(ETPUnion_t *msg){
    ETPHeader_t *header = &msg->header;
    switch(header->opcode){
        case ETPOpcode_Sync: {
            UARTprintf("\n\nGot sync!\n");
            break;
       }
        case ETPOpcode_DeSync: {
            break;
       }
        case ETPOpcode_I2C0Frame: {

            break;
       }
        case ETPOpcode_I2C0Replay: {

            break;
       }

        case ETPOpcode_ETPOCMState: {

            break;
       }
        case ETPOpcode_KeepAlive: {

            break;
       }

        case ETPOpcode_Ping: {

            break;
       }

        case ETPOpcode_Pong: {
            break;
       }

       case ETPOpcode_SPI0Frame: {

           break;
       }

       case ETPOpcode_UART0Data: {

           break;
       }

       case ETPOpcode_reset: {

           break;
       }

       default: {

           break;
       }

    }

}


static void vEGSEManagerTask(void *pvParameters){

    uartmsg_t sUartRcv;

    ETPUnion_t *msg ;

    static size_t endOfMsg = sizeof(ETPHeader_t); //needed later to check if msg has header
    bool hasHeader;


    while(1){


        if(xQueueReceive(g_pUartRPIQueue, &sUartRcv, portMAX_DELAY) == pdPASS){
            UARTprintf("\n\nRecieved message from uart queue:%c\n", sUartRcv.rxBuff[0]);
            //msg = (ETPUnion_t *)&sUartRcv.rxBuff;

            //HARD CODING EXAMPLE
            msg->header.opcode = ETPOpcode_Sync;

            //assuming message has header
            handle_EPTMsg(msg);






        }



           //compact message into standard structure


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



