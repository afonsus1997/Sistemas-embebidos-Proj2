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
// IMPORTANT NOTE: The following driver file supports using either RAM or
// non-volatile memory(Flash or FRAM) to store the LCD DisplayBuffer.
//
//*****************************************************************************

//*****************************************************************************
//
// Sharp128x128.c
//
//*****************************************************************************
//
//! \addtogroup display_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include "grlib.h"
#include "Sharp128x128.h"

uint8_t VCOMbit = 0x40;
uint8_t flagSendToggleVCOMCommand = 0;

uint8_t DisplayBuffer[LCD_VERTICAL_MAX][LCD_HORIZONTAL_MAX / 8];

//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the Sharp128x128 display controller preparing it to
//! display data.
//!
//! \return None.
//
//*****************************************************************************
void Sharp128x128_initDisplay(void)
{
    HAL_LCD_initDisplay();
}


//*****************************************************************************
//
//! Initialize DisplayBuffer.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//!
//!	\param ucValue is the foreground color of the buffered data.
//!
//! This function initializes the display buffer and discards any cached data.
//!
//! \return None.
//
//*****************************************************************************
void Sharp128x128_InitializeDisplayBuffer(void *pvDisplayData, uint8_t ucValue){

    uint16_t i = 0,j = 0;
    uint8_t *pucData = pvDisplayData;
    for(i = 0; i < LCD_VERTICAL_MAX; i++)
    {
        for(j = 0; j < (LCD_HORIZONTAL_MAX >> 3); j++)
        {
            *pucData++ = ucValue;
        }
    }
}

//*****************************************************************************
//
//! Draws a pixel on the screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX is the X coordinate of the pixel.
//! \param lY is the Y coordinate of the pixel.
//! \param ulValue is the color of the pixel.
//!
//! This function sets the given pixel to a particular color.  The coordinates
//! of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
void Sharp128x128_PixelDraw(void *pvDisplayData,
                                 int16_t lX,
                                 int16_t lY,
                                 uint16_t ulValue)
{
    if(ClrBlack == ulValue)
    {
        DisplayBuffer[lY][lX >> 3] &= ~(0x80 >> (lX & 0x7));
    }
    else
    {
        DisplayBuffer[lY][lX >> 3] |= (0x80 >> (lX & 0x7));
    }
}

//*****************************************************************************
//
//! Draws a horizontal sequence of pixels on the screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX is the X coordinate of the first pixel.
//! \param lY is the Y coordinate of the first pixel.
//! \param lX0 is sub-pixel offset within the pixel data, which is valid for 1
//! or 4 bit per pixel formats.
//! \param lCount is the number of pixels to draw.
//! \param lBPP is the number of bits per pixel; must be 1, 4, or 8.
//! \param pucData is a pointer to the pixel data.  For 1 and 4 bit per pixel
//! formats, the most significant bit(s) represent the left-most pixel.
//! \param pucPalette is a pointer to the palette used to draw the pixels.
//!
//! This function draws a horizontal sequence of pixels on the screen, using
//! the supplied palette.  For 1 bit per pixel format, the palette contains
//! pre-translated colors; for 4 and 8 bit per pixel formats, the palette
//! contains 24-bit RGB values that must be translated before being written to
//! the display.
//!
//! \return None.
//
//*****************************************************************************
/*void Sharp128x128_DrawMultiple(void *pvDisplayData,
                                    int16_t lX,
                                    int16_t lY,
                                    int16_t lX0,
                                    int16_t lCount,
                                    int16_t lBPP,
                                    const uint8_t *pucData,
                                    const uint32_t *pucPalette)
{
    uint8_t *pData = &DisplayBuffer[lY][lX >> 3];
    uint16_t xj = 0;

    //Write bytes of data to the display buffer
    for(xj = 0; xj < (lCount >> 3); xj++)
    {
        *pData++ = *pucData++;
    }

    //Write last data byte to the display buffer
    *pData = (*pData & (0xFF >> (lCount & 0x7))) | *pucData;
}*/

//*****************************************************************************
//
//! Send command to clear screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param ucValue is the background color of the buffered data.
//!
//! This function sets every pixel to the background color.
//!
//! \return None.
//
//*****************************************************************************
void Sharp128x128_ClearScreen(void *pvDisplayData,
                                   uint16_t ulValue)
{
    //clear screen mode(0X100000b)
    //uint8_t command = SHARP_LCD_CMD_CLEAR_SCREEN;
    //COM inversion bit
    //command = command ^ VCOMbit;

    HAL_LCD_ToggleCS(CS_LCD_BASE, CS_LCD, 0);

    HAL_LCD_writeCommandOrData(SHARP_LCD_CMD_CLEAR_SCREEN);
    //flagSendToggleVCOMCommand = SHARP_SKIP_TOGGLE_VCOM_COMMAND;
    //HAL_LCD_writeCommandOrData(SHARP_LCD_TRAILER_BYTE);

    // Wait for last byte to be sent, then drop SCS
    HAL_LCD_waitUntilLcdWriteFinish();

    //HAL_LCD_writeCommandOrData();

    HAL_LCD_ToggleCS(CS_LCD_BASE, CS_LCD, 1);
    /*if(ClrBlack == ulValue)
    {
        Sharp128x128_InitializeDisplayBuffer(pvDisplayData, SHARP_BLACK);
    }
    else
    {
        Sharp128x128_InitializeDisplayBuffer(pvDisplayData, SHARP_WHITE);
    }*/
}

//*****************************************************************************
//
//! The display structure that describes the driver for the
//! sharpLCD panel
//
//*****************************************************************************
const Graphics_Display g_sharp128x128LCD =
{
    sizeof(tDisplay),
    DisplayBuffer,
    LCD_HORIZONTAL_MAX,
    LCD_VERTICAL_MAX,
    Sharp128x128_PixelDraw, //PixelDraw,
    //Sharp128x128_DrawMultiple,
    Sharp128x128_ClearScreen //Clear screen. Contents of display buffer unmodified
};

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
