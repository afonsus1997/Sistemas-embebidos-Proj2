/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
//
// HAL_MSP-EXP430FR5969_Sharp128x128.c
//
//*****************************************************************************
//
//! \addtogroup display_api
//! @{
//
//*****************************************************************************

#include <HWOps/LcdDriver/HAL_LCD.h>
#include "Sharp128x128.h"

//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the Sharp128x128 display. This function
//! configures the GPIO pins used to control the LCD display when the basic
//! GPIO interface is in use. On exit, the LCD has been reset and is ready to
//! receive command and data writes.
//!
//! \return None.
//
//*****************************************************************************
void HAL_LCD_initDisplay(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3); //init SPI3 (FrontPanel)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinConfigure(GPIO_PD0_SSI3CLK);
    GPIOPinConfigure(GPIO_PD2_SSI3RX); //miso
    GPIOPinConfigure(GPIO_PD3_SSI3TX); //mosi

    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);

    SSIConfigSetExpClk(SSI3_BASE, 16000000, SSI_FRF_MOTO_MODE_0,
                           SSI_MODE_MASTER, 1000000, 8);

    SSIEnable(SSI3_BASE);
}

//*****************************************************************************
//
// Writes command or data to the LCD Driver
//
// \param ucCmdData is the 8 or 16 bit command to send to the LCD driver
// Uses the SET_LCD_DATA macro
//
// \return None
//
//*****************************************************************************
void HAL_LCD_writeCommandOrData(uint16_t command){
    SSIDataPut(SSI3_BASE, command);
    //while(SSIBusy(SSI3_BASE));
}

//*****************************************************************************
//
// Clear and set CS line
//
// This macro allows to set the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************
void HAL_LCD_ToggleCS(uint32_t GPIOBASE, uint32_t GPIOPin, uint32_t state){
    if(state){
        while(SSIBusy(SSI3_BASE));
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
        SysCtlDelay(1);
    }
    else{
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
        SysCtlDelay(1);
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, 0);
    }
}

//*****************************************************************************
//
// Waits until the SPI communication with the LCD is finished a command to
// the LCD Driver
//
// \param None
//
// \return None
//*****************************************************************************
void HAL_LCD_waitUntilLcdWriteFinish(void)
{
    while(SSIBusy(SSI3_BASE));
}

/*void HAL_LCD_InitializeDisplayBuffer(void *pvDisplayData, uint8_t ucValue){
    uint16_t i = 0,j = 0;
    uint8_t *pucData = pvDisplayData;
    for(i = 0; i < LCD_VERTICAL_MAX; i++)
    {
        for(j = 0; j < (LCD_HORIZONTAL_MAX >> 3); j++)
        {
            *pucData++ = ucValue;
        }
    }
}*/

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
