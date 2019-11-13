

#include "i2c.h"



//static uartmsg_t uartmsg;


static void vI2CEGSETask(void *pvParameters){


    while(1){

    }

}




uint32_t vI2CEGSETaskInit(void)
{
    //g_pI2CEGSEQueue = xQueueCreate(I2CEGSE_QUEUE_SIZE, I2CEGSE_ITEM_SIZE);




    //if(xTaskCreate(vI2CEGSETask, (const portCHAR *)"UartRPI", I2CEGSETaskStackSize, NULL,
    //               tskIDLE_PRIORITY + PRIORITY_I2CEGSE_TASK, NULL) != pdTRUE)
    //{
    //    return(1);
    //}

    //
    // Success.
    //
    return(0);
}



