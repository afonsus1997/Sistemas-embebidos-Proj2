#include "EGSE_Manager_Task.h"

static void vEGSEManagerTask(void *pvParameters){

    uartmsg_t sUartRcv;

    ETPUnion_t *msg ;

    static size_t endOfMsg = sizeof(ETPHeader_t); //needed later to check if msg has header
    bool hasHeader;


    while(1){

        while(xQueueReceive(g_pUartRPIQueue, &sUartRcv, portMAX_DELAY) != pdTRUE);


        UARTprintf("[EGSE Manager Task] - Recieved message from UART queue: %c\n", sUartRcv.rxBuff[0]);
        msg = (ETPUnion_t *)&sUartRcv.rxBuff;
        //HARD CODING EXAMPLE
        //msg->header.opcode = ETPOpcode_Sync;
        //assuming message has header

        //handle_EPTMsg(msg);

        //msg->header.opcode = ETPOpcode_Ping;
        //handle_EPTMsg(msg);

        /* uint8_t msg_UART3 = 57600;
        msg->header.opcode = ETPOpcode_UART0Data;
        msg->header.size = 1;
        msg->uart0.data[0] = 123;
        handle_EPTMsg(msg); */

        msg->header.opcode = ETPOpcode_reset;
        handle_EPTMsg(msg);







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



