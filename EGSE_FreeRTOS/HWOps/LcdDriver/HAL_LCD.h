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
// HAL_MSP-EXP430G2_Sharp128x128.h - Prototypes for the Sharp128x128 LCD display driver.
//                                 There is no output from Sharp128x128 LCD.
//
//                 MSP430G2553                    LCD Sharp128x128
//                -----------------             -----------------
//               |     UCB0CLK/P1.5|---------> |SCLK     EXTCOMIN|-- 0
//            /|\|                 |           |                 |
//             | |    UCB0SIMO/P1.7|---------> |SI        EXTMODE|-- 0
//             --|RST              |           |                 |
//               |     UCB0STE/P1.4|---------> |SCS              |
//               |                 |		   |                 |
//               |             P1.3|---------> |DISP             |
//               |                 |		   |                 |
//               |                 |           |                 |
//               |                 |            -----------------
//*****************************************************************************

#ifndef __HAL_TIVA_SHARPLCD_H__
#define __HAL_TIVA_SHARPLCD_H__

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/rom.h"

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************

void HAL_LCD_initDisplay(void);
void HAL_LCD_writeCommandOrData(uint16_t command);
void HAL_LCD_ToggleCS(uint32_t GPIOBASE, uint32_t GPIOPin, uint32_t state);
void HAL_LCD_waitUntilLcdWriteFinish(void);

#endif // __HAL_MSP_TIVA_SHARPLCD_H__
