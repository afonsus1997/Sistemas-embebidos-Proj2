/*
 * ADC.c
 *
 *  Created on: 26/11/2019
 *      Author: gdmt
 */

#include "ADC.h"
//#define ADCSCANTEST
uint16_t SPIrxbuf[2];

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

    uint8_t i, channel = 0;
    uint8_t ulindex;
    while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[0])); //clean fifo garbage
    for(i=0;i<AMM_CHANNEL;i++){

        for(ulindex = 0; ulindex < 2; ulindex++)
        {
            SSIDataPut(SSI2_BASE, 0);
            //ADCwriteRegister(0, 0);
            while(SSIBusy(SSI2_BASE));
            while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[ulindex]));
            while(SSIBusy(SSI2_BASE)){}

        }

        if(1){ //sets the read value range
            LastReadings.ADCs[channel] = (SPIrxbuf[0] << 8) | SPIrxbuf[1];
            channel++;
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

    //channel = 0;
    while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[0])); //clean fifo garbage
    for(i=0;i<AMM_CHANNEL;i++){

        for(ulindex = 0; ulindex < 2; ulindex++)
        {
            SSIDataPut(SSI2_BASE, 0);
            //ADCwriteRegister(0, 0);
            while(SSIBusy(SSI2_BASE));
            while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[ulindex]));
            while(SSIBusy(SSI2_BASE)){}

        }

        if(!(i >= 8 && i<= 10 )){
            LastReadings.ADCs[channel+14] = SPIrxbuf[0] << 8 | SPIrxbuf[1];
            channel++;
        }

        ADCToggleCS(CS_ADC2_BASE,CS_ADC2,1);

    }

    //update values

}
