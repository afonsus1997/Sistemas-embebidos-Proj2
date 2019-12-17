/*
 * Acquisition_Task.c
 *
 *  Created on: Nov 27, 2019
 *      Author: Afonso Muralha
 */


#include "Acquisition_Task.h"

float conversionMap[26] = {ADC_V1_CONV, ADC_I1_CONV,
                           ADC_V2_CONV, ADC_I2_CONV,
                           ADC_V3_CONV, ADC_I3_CONV,
                           ADC_V4_CONV, ADC_I4_CONV,
                           ADC_V5_CONV, ADC_I5_CONV,
                           ADC_V6_CONV, ADC_I6_CONV,
                           EGSE_ADC1_CONV, EGSE_ADC2_CONV,
                           EGSE_ADC3_CONV, EGSE_ADC4_CONV,
                           EGSE_ADC5_CONV, EGSE_ADC6_CONV,
                           EGSE_ADC7_CONV, EGSE_ADC8_CONV,
                           EXP_ADC1_CONV, EXP_ADC2_CONV,
                           EXP_ADC3_CONV, EXP_ADC4_CONV,
                           BAT_V_CONV, BAT_I_CONV};

uint8_t ADCvMap[6] = {ADC_V1_VAL, ADC_V2_VAL, ADC_V3_VAL, ADC_V4_VAL, ADC_V5_VAL, ADC_V6_VAL};

void ConvertValues(){
    int i;
    for(i=0; i<26; i++){
        LastReadings.ADCs[i] = RawReadings.ADCs[i] * conversionMap[i];
    }
}


void Railmonitor(){
    uint8_t i;
    for(i=0; i<6; i++){
        if(PSUstatus[i] == 0 && LastReadings.ADCs[ADCvMap[i]] < ZERO_THRESHOLD);
    }
}





static void vAcquisitionTask(void *pvParameters)
{

//    const TickType_t xAcquisitionDelay = 250 / portTICK_PERIOD_MS;
//    vTaskSuspend(vAcquisitionTask);
    while (1)
    {
        UARTprintf("[Acquisition Task] - Reading adcs\n");
        ADCreadFIFO();
        ConvertValues();
//        Railmonitor();
//        vTaskDelay( xAcquisitionDelay );
        taskYIELD();

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


