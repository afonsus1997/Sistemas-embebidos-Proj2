/*
 * ADC.c
 *
 *  Created on: 26/11/2019
 *      Author: gdmt
 */

#include "ADC.h"

uint32_t SPIrxbuf[10];

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

    /* Program functions for ADC2 */
    //ADCwriteRegister(1, RESET & ~(1<<nRESET));
    //ADCwriteRegister(1, (SETUP | (1<<REFSEL1) | (1<<CKSEL1)));
    //ADCwriteRegister(1, CONVERSION);
    //ADCwriteRegister(1, (AVERAGING | (1<<AVGON) | (1<<NAVG1)));

    ADCreadFIFO();
}

void ADCreadFIFO(){

    ADCwriteRegister(0, CONVERSION);
    //ADCwriteRegister(0, CONVERSION);

    SysCtlDelay(150 * (SysCtlClockGet() /3 /1000000)); //wait for conversion
    ADCToggleCS(CS_ADC1_BASE,CS_ADC1,0); //ask for values


    uint8_t i;
    uint8_t ulindex;
    while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[0])); //clean fifo garbage
    for(i=0;i<AMM_CHANNEL;i++){


//        for(ulindex = 0; ulindex < 10; ulindex++)
//        {
            SSIDataPut(SSI2_BASE, 0x00);

            //ADCwriteRegister(0, 0);
            while(SSIBusy(SSI2_BASE));
            while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[0]) == 0);
            //SSIDataGet(SSI2_BASE, &SPIrxbuf[0]);

            SSIDataPut(SSI2_BASE, 0x00);
            //ADCwriteRegister(0, 0);
            while(SSIBusy(SSI2_BASE));
            while(SSIDataGetNonBlocking(SSI2_BASE, &SPIrxbuf[1]) == 0);
            //SSIDataGet(SSI2_BASE, &SPIrxbuf[1]);
//        }

        //bufflsb = bufflsb | buffmsb << 8;
        ADCFIFO[0][i] = SPIrxbuf[0] << 8 | SPIrxbuf[1];
    }


    //ADCToggleCS(CS_ADC1_BASE,CS_ADC1,1);

    //================================================//

    /* Chip Select ADC2 */

    /* Write to conversion register to indicate to request data */
    //ADCwriteRegister(1, CONVERSION);

    /* Toogle Chip Select to start the conversion */
    //ADCToggleCS(CS_ADC2_BASE,CS_ADC2, 0);

    /*
    for(i=0;i<AMM_CHANNEL;i++){
        SSIDataGet(SSI2_BASE, &buffadc);
        buffadc = buffadc << 8;
        SSIDataGet(SSI2_BASE, &buffadc);
        ADCFIFO[1][i] = buffadc;
    }
    ADCToggleCS(CS_ADC2_BASE,CS_ADC2,1);
    */
}
