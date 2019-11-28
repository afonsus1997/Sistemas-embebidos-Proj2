/*
 * Acquisition_Task.c
 *
 *  Created on: Nov 27, 2019
 *      Author: Afonso Muralha
 */


#include "Acquisition_Task.h"



static void vAcquisitionTask(void *pvParameters)
{

    const TickType_t xAcquisitionDelay = 250 / portTICK_PERIOD_MS;

    while (1)
    {
        ADCreadFIFO();
        vTaskDelay( xAcquisitionDelay );
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

