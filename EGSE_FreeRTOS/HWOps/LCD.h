/*
 * LCD.h
 *
 *  Created on: 03/12/2019
 *      Author: gdmt
 */

#ifndef HWOPS_LCD_H_
#define HWOPS_LCD_H_

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
#include "../Funcs/GPIO.h"
#include "./grlib/grlib.h"

// LCD Screen Dimensions
#define LCD_VERTICAL_MAX    128
#define LCD_HORIZONTAL_MAX  128

// Define LCD Screen Orientation Here
#define LANDSCAPE

//Maximum Colors in an image color palette
#define MAX_PALETTE_COLORS  2

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

extern const Graphics_Display g_sharp128x128LCD;


void LCDinit();
void LCDToggleCS(uint32_t GPIOBASE, uint32_t GPIOPin, uint32_t state);
void LCDwriteCommand(uint8_t data);

uint8_t Sharp128x128_reverse(uint8_t x);
void Sharp128x128_InitializeDisplayBuffer(void *pvDisplayData, uint8_t ucValue);
void Sharp128x128_PixelDraw(void *pvDisplayData, int16_t lX, int16_t lY,uint16_t ulValue);
void Sharp128x128_DrawMultiple(void *pvDisplayData, int16_t lX, int16_t lY, int16_t lX0, int16_t lCount,
                                    int16_t lBPP,
                                    const uint8_t *pucData,
                                    const uint32_t *pucPalette);
void Sharp128x128_LineDrawH(void *pvDisplayData, int16_t lX1, int16_t lX2, int16_t lY, uint16_t ulValue);
void Sharp128x128_LineDrawV(void *pvDisplayData, int16_t lX, int16_t lY1, int16_t lY2, uint16_t ulValue);
void Sharp128x128_RectFill(void *pvDisplayData, const Graphics_Rectangle *pRect, uint16_t ulValue);
uint32_t Sharp128x128_ColorTranslate(void *pvDisplayData, uint32_t ulValue);
void Sharp128x128_Flush(void *pvDisplayData);
void Sharp128x128_ClearScreen(void *pvDisplayData, uint16_t ulValue);


#endif /* HWOPS_LCD_H_ */
