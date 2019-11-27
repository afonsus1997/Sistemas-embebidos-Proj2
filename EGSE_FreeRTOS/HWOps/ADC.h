/*
 * ADC.h
 *
 *  Created on: 26/11/2019
 *      Author: gdmt
 */

#ifndef HWOPS_ADC_H_
#define HWOPS_ADC_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"

#include "HardwareIOConfig.h"
#include "../Funcs/SPI.h"
#include "../funcs/GPIO.h"
#include "../Tasks/Acquisition_Task.h"

#define AMM_CHANNEL 15
#define AMM_ADC 2
#define NUM_SSI_DATA 2

/* Register of ADC's */
#define CONVERSION 0b11111000//0x80
#define SETUP      0x40
#define AVERAGING  0x20
#define RESET      0x10

/* Register Bits - RESET */
#define nRESET 3

/* Register Bits - CONVERSION */
#define CHSEL3 6
#define CHSEL2 5
#define CHSEL1 4
#define CHSEL0 3
#define SCAN1  2
#define SCAN0  1

/* Register Bits - SETUP */
#define CKSEL1  5
#define CKSEL0  4
#define REFSEL1 3
#define REFSEL0 2

/* Register Bits - AVERAGING */
#define AVGON  4
#define NAVG1  3
#define NAVG0  2
#define NSCAN1 1
#define NSCAN0 0


uint16_t ADCFIFO[AMM_ADC][AMM_CHANNEL];

void ADCToggleCS(uint32_t GPIOBASE, uint32_t GPIOPin, uint32_t state);
void ADCinit();
uint8_t ADCreadRegister(uint8_t ADCid);
void ADCwriteRegister(uint8_t ADCid, uint8_t data);
void ADCreadFIFO();
void ADCwriteAll();

extern LastReadings_t LastReadings;


#endif /* HWOPS_ADC_H_ */
