/*
 * ADC.c
 *
 *  Created on: 26/11/2019
 *      Author: gdmt
 */

#include "ADC.h"
//#define ADCSCANTEST
uint16_t SPIrxbuf[2];

uint8_t adc0PinMap[15] = {BAT_I, BAT_V, EGSE_ADC1, EGSE_ADC2, EGSE_ADC3, EGSE_ADC4, EGSE_ADC5, EGSE_ADC6, EGSE_ADC7, EGSE_ADC8, ADC_V6_VAL, ADC_I6_VAL, ADC_I4_VAL, ADC_V4_VAL, NULL};
uint8_t adc1PinMap[15] = {ADC_V2_VAL, ADC_I2_VAL, ADC_V5_VAL, ADC_V3_VAL, ADC_I3_VAL, ADC_V1_VAL, ADC_I1_VAL, NULL, NULL, NULL, EXP_ADC1_VAL, EXP_ADC2_VAL, EXP_ADC3_VAL, EXP_ADC4_VAL, NULL};



void ADCToggleCS(uint32_t GPIOBASE, uint32_t GPIOPin, uint32_t state){
    if(state){
        while(SSIBusy(SSI2_BASE));
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
        SysCtlDelay(1);
    }
    else{
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
        SysCtlDelay(1);
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, 0);
    }
}

void ADCwriteRegister(uint8_t ADCid, uint8_t data){
    if(ADCid == 0){
        ADCToggleCS(CS_ADC1_BASE,CS_ADC1,0);
        SSIDataPut(SSI2_BASE, data);
        ADCToggleCS(CS_ADC1_BASE,CS_ADC1,1);
    }
    else if(ADCid == 1){
        ADCToggleCS(CS_ADC2_BASE,CS_ADC2,0);
        SSIDataPut(SSI2_BASE, data);
        ADCToggleCS(CS_ADC2_BASE,CS_ADC2,1);
    }
}

uint8_t ADCreadRegister(uint8_t ADCid){
    uint8_t *data = 0;
    if(ADCid == 0){
        ADCToggleCS(CS_ADC1_BASE,CS_ADC1,0);
        SSIDataGet(SSI2_BASE, data);
        ADCToggleCS(CS_ADC1_BASE,CS_ADC1,1);
    }
    else if(ADCid == 1){
        ADCToggleCS(CS_ADC2_BASE,CS_ADC2,0);
        SSIDataGet(SSI2_BASE, data);
        ADCToggleCS(CS_ADC2_BASE,CS_ADC2,1);
    }
    return data;
}

void ADCinit(){

    /* Program functions for ADC1 */
    ADCwriteRegister(0, RESET & ~(1<<nRESET));
    ADCwriteRegister(0, (SETUP | (1<<REFSEL1) | (1<<CKSEL1)));
    ADCwriteRegister(0, (AVERAGING | (1<<AVGON) | (1<<NAVG1)));
    //ADCwriteRegister(0, CONVERSION);

    // Program functions for ADC2 */
    ADCwriteRegister(1, RESET & ~(1<<nRESET));
    ADCwriteRegister(1, (SETUP | (1<<REFSEL1) | (1<<CKSEL1)));

    ADCwriteRegister(1, (AVERAGING | (1<<AVGON) | (1<<NAVG1)));

#ifdef ADCSCANTEST
    while(1){
        ADCreadFIFO();
        SysCtlDelay(15000 * (SysCtlClockGet() /3 /1000000)); //wait for conversion
    }
#endif
}

void ADCreadFIFO(){
    ADCwriteRegister(0, RESET & ~(1<<nRESET));
    ADCwriteRegister(0, (SETUP | (1<<REFSEL1) | (1<<CKSEL1)));
    ADCwriteRegister(0, (AVERAGING | (1<<AVGON) | (1<<NAVG1)));

    ADCwriteRegister(0, CONVERSION);

    SysCtlDelay(150 * (SysCtlClockGet() /3 /1000000)); //wait for conversion
    ADCToggleCS(CS_ADC1_BASE,CS_ADC1,0); //ask for values

    uint8_t i;
    uint8_t ulindex;
    while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[0])); //clean fifo garbage
    for(i=0;i<15;i++){


        /*
        SSIDataPut(SSI2_BASE, 0);
        //ADCwriteRegister(0, 0);
        while(SSIBusy(SSI2_BASE));
        while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[ulindex]));
        while(SSIBusy(SSI2_BASE)){}

        SSIDataPut(SSI2_BASE, 0);
        //ADCwriteRegister(0, 0);
        while(SSIBusy(SSI2_BASE));
        while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[ulindex]));
        while(SSIBusy(SSI2_BASE)){}
        */


        if(adc0PinMap[i] != NULL){ //sets the read value range
            RawReadings.ADCs[adc0PinMap[i]] = (SPIrxbuf[0] << 8) | SPIrxbuf[1];
        }

    }

    ADCToggleCS(CS_ADC1_BASE,CS_ADC1,1);

    // ADC2
    ADCwriteRegister(1, RESET & ~(1<<nRESET));
    ADCwriteRegister(1, (SETUP | (1<<REFSEL1) | (1<<CKSEL1)));

    ADCwriteRegister(1, (AVERAGING | (1<<AVGON) | (1<<NAVG1)));


    ADCwriteRegister(1, CONVERSION);

    SysCtlDelay(150 * (SysCtlClockGet() /3 /1000000)); //wait for conversion
    ADCToggleCS(CS_ADC2_BASE,CS_ADC2,0); //ask for values

    while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[0])); //clean fifo garbage
    for(i=0;i<15;i++){

        /*
        SSIDataPut(SSI2_BASE, 0);
        //ADCwriteRegister(0, 0);
        while(SSIBusy(SSI2_BASE));
        while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[ulindex]));
        while(SSIBusy(SSI2_BASE)){}

        SSIDataPut(SSI2_BASE, 0);
        //ADCwriteRegister(0, 0);
        while(SSIBusy(SSI2_BASE));
        while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[ulindex]));
        while(SSIBusy(SSI2_BASE)){}
        */


        if(adc1PinMap[i] != NULL){
            RawReadings.ADCs[adc1PinMap[i]] = SPIrxbuf[0] << 8 | SPIrxbuf[1];
        }



        ADCToggleCS(CS_ADC2_BASE,CS_ADC2,1);

    }

    //update values

}



