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
// Sharp128x128.h - Prototypes for the Sharp128x128 LCD display driver
//
//*****************************************************************************

#ifndef __SHARPLCD_H__
#define __SHARPLCD_H__

#include "HAL_LCD.h"
#include "../HardwareIOConfig.h"
#include "grlib.h"

//*****************************************************************************
//
// User Configuration for the LCD Driver
//
//*****************************************************************************

// LCD Screen Dimensions
#define LCD_VERTICAL_MAX                   128
#define LCD_HORIZONTAL_MAX                 128

//Maximum Colors in an image color palette
//#define MAX_PALETTE_COLORS  2

//*****************************************************************************
//
// Macros for the Display Driver
//
//*****************************************************************************
#define SHARP_BLACK                                                     0x00
#define SHARP_WHITE                                                     0xFF
#define SHARP_SEND_TOGGLE_VCOM_COMMAND          0x01
#define SHARP_SKIP_TOGGLE_VCOM_COMMAND          0x00
#define SHARP_LCD_TRAILER_BYTE                          0x00
#define SHARP_VCOM_TOGGLE_BIT                           0x40
#define SHARP_LCD_CMD_CHANGE_VCOM                       0x00
#define SHARP_LCD_CMD_CLEAR_SCREEN                      0x20
#define SHARP_LCD_CMD_WRITE_LINE                        0x80

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern const Graphics_Display g_sharp128x128LCD;


void Sharp128x128_initDisplay(void);
void Sharp128x128_InitializeDisplayBuffer(void *, uint8_t);
void Sharp128x128_PixelDraw(void *, int16_t, int16_t, uint16_t);
//void Sharp128x128_DrawMultiple(void *, int16_t, int16_t, int16_t, int16_t, int16_t, const uint8_t *, const uint32_t *);
void Sharp128x128_ClearScreen(void *, uint16_t);

#endif // __SHARPLCD_H__
