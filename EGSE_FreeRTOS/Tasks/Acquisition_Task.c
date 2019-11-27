/*
 * Acquisition_Task.c
 *
 *  Created on: Nov 27, 2019
 *      Author: Afonso Muralha
 */


#include "Acquisition_Task.h"



static void vAcquisitionTask(void *pvParameters)
{

    while (1)
    {
        //xQueueReceive(g_HardwareTaskQueueRX, &hwMSG, portMAX_DELAY);
    }
}




uint32_t vAcquisitionTaskINIT(void)
{


    if (xTaskCreate(vAcquisitionTask, (const portCHAR *)"AcquisitionTask", AcquisitionTaskSTACKSIZE, NULL,
            tskIDLE_PRIORITY + PRIORITY_ACQUISITION_TASK , NULL) != pdTRUE)
    {
        return (1);
    }

    //
    // Success.
    //
    return (0);
}

