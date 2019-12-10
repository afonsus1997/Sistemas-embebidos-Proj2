///*
// * LCD.c
// *
// *  Created on: 03/12/2019
// *      Author: gdmt
// */
//
//#include "LCD.h"
//
//const uint8_t reverse_data[] = {0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 0x1,
//                                0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF};
//
//uint8_t DisplayBuffer[1][1];
//uint8_t VCOMbit = 0x40;
//uint8_t flagSendToggleVCOMCommand = 0;
//Graphics_Context g_sContext;
//
//void LCDToggleCS(uint32_t GPIOBASE, uint32_t GPIOPin, uint32_t state){
//    if(state){
//        while(SSIBusy(SSI3_BASE));
//        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
//        SysCtlDelay(1);
//    }
//    else{
//        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
//        SysCtlDelay(1);
//        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, 0);
//    }
//}
//
//void LCDinit(){
//    Graphics_initContext(&g_sContext, &g_sharp128x128LCD);
//    Graphics_setForegroundColor(&g_sContext, ClrBlack);
//    /*Graphics_setBackgroundColor(&g_sContext, ClrWhite);
//    Graphics_setFont(&g_sContext, &g_sFontFixed6x8);
//    Graphics_clearDisplay(&g_sContext);*/
//}
//
//void LCDwriteCommand(uint8_t data){
//    LCDToggleCS(CS_LCD_BASE,CS_LCD,0);
//    SSIDataPut(SSI3_BASE, data);
//    while(SSIBusy(SSI3_BASE));
//    LCDToggleCS(CS_LCD_BASE,CS_LCD,1);
//}
//
//uint8_t Sharp128x128_reverse(uint8_t x){
//    uint8_t b = 0;
//
//    b = reverse_data[x & 0xF] << 4;
//    b |= reverse_data[(x & 0xF0) >> 4];
//    return(b);
//}
//
//void Sharp128x128_InitializeDisplayBuffer(void *pvDisplayData, uint8_t ucValue){
//    uint16_t i = 0,j = 0;
//    uint8_t *pucData = pvDisplayData;
//    for(i = 0; i < LCD_VERTICAL_MAX; i++)
//    {
//        for(j = 0; j < (LCD_HORIZONTAL_MAX >> 3); j++)
//        {
//            *pucData++ = ucValue;
//        }
//    }
//}
//
//void Sharp128x128_PixelDraw(void *pvDisplayData, int16_t lX, int16_t lY,uint16_t ulValue){
//    if(ClrBlack == ulValue)
//    {
//        DisplayBuffer[lY][lX >> 3] &= ~(0x80 >> (lX & 0x7));
//    }
//    else
//    {
//        DisplayBuffer[lY][lX >> 3] |= (0x80 >> (lX & 0x7));
//    }
//}
//
//void Sharp128x128_DrawMultiple(void *pvDisplayData, int16_t lX,
//                                    int16_t lY,
//                                    int16_t lX0,
//                                    int16_t lCount,
//                                    int16_t lBPP,
//                                    const uint8_t *pucData,
//                                    const uint32_t *pucPalette)
//{
//    uint8_t *pData = &DisplayBuffer[lY][lX >> 3];
//    uint16_t xj = 0;
//
//    //Write bytes of data to the display buffer
//    for(xj = 0; xj < (lCount >> 3); xj++)
//    {
//        *pData++ = *pucData++;
//    }
//
//    //Write last data byte to the display buffer
//    *pData = (*pData & (0xFF >> (lCount & 0x7))) | *pucData;
//}
//
//void Sharp128x128_LineDrawH(void *pvDisplayData,
//                                 int16_t lX1,
//                                 int16_t lX2,
//                                 int16_t lY,
//                                 uint16_t ulValue)
//{
//    uint16_t xi = 0;
//    uint16_t x_index_min = lX1 >> 3;
//    uint16_t x_index_max = lX2 >> 3;
//    uint8_t *pucData, ucfirst_x_byte, uclast_x_byte;
//
//    //calculate first byte
//    //mod by 8 and shift this # bits
//    ucfirst_x_byte = (0xFF >> (lX1 & 0x7));
//    //calculate last byte
//    //mod by 8 and shift this # bits
//    uclast_x_byte = (0xFF << (7 - (lX2 & 0x7)));
//
//    //check if more than one data byte
//    if(x_index_min != x_index_max)
//    {
//        //set buffer to correct location
//        pucData = &DisplayBuffer[lY][x_index_min];
//
//        //black pixels (clear bits)
//        if(ClrBlack == ulValue)
//        {
//            //write first byte
//            *pucData++ &= ~ucfirst_x_byte;
//
//            //write middle bytes
//            for(xi = x_index_min; xi < x_index_max - 1; xi++)
//            {
//                *pucData++ = 0x00;
//            }
//
//            //write last byte
//            *pucData &= ~uclast_x_byte;
//        }
//        //white pixels (set bits)
//        else
//        {
//            //write first byte
//            *pucData++ |= ucfirst_x_byte;
//
//            //write middle bytes
//            for(xi = x_index_min; xi < x_index_max - 1; xi++)
//            {
//                *pucData++ = 0xFF;
//            }
//
//            //write last byte
//            *pucData |= uclast_x_byte;
//        }
//    }
//    //only one data byte
//    else
//    {
//        //calculate value of single byte
//        ucfirst_x_byte &= uclast_x_byte;
//
//        //set buffer to correct location
//        pucData = &DisplayBuffer[lY][x_index_min];
//
//        //draw black pixels (clear bits)
//        if(ClrBlack == ulValue)
//        {
//            *pucData++ &= ~ucfirst_x_byte;
//        }
//        //white pixels (set bits)
//        else
//        {
//            *pucData++ |= ucfirst_x_byte;
//        }
//    }
//}
//
////*****************************************************************************
////
////! Draws a vertical line.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param lX is the X coordinate of the line.
////! \param lY1 is the Y coordinate of the start of the line.
////! \param lY2 is the Y coordinate of the end of the line.
////! \param ulValue is the color of the line.
////!
////! This function draws a vertical line on the display.  The coordinates of the
////! line are assumed to be within the extents of the display.
////!
////! \return None.
////
////*****************************************************************************
//void Sharp128x128_LineDrawV(void *pvDisplayData,
//                                 int16_t lX,
//                                 int16_t lY1,
//                                 int16_t lY2,
//                                 uint16_t ulValue)
//{
//    uint16_t yi = 0;
//    uint16_t x_index = lX >> 3;
//    uint8_t data_byte;
//
//    //calculate data byte
//    //mod by 8 and shift this # bits
//    data_byte = (0x80 >> (lX & 0x7));
//
//    //write data to the display buffer
//    for(yi = lY1; yi <= lY2; yi++)
//    {
//        //black pixels (clear bits)
//        if(ClrBlack == ulValue)
//        {
//            DisplayBuffer[yi][x_index] &= ~data_byte;
//        }
//        //white pixels (set bits)
//        else
//        {
//            DisplayBuffer[yi][x_index] |= data_byte;
//        }
//    }
//}
//
////*****************************************************************************
////
////! Fills a rectangle.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param pRect is a pointer to the structure describing the rectangle.
////! \param ulValue is the color of the rectangle.
////!
////! This function fills a rectangle on the display.  The coordinates of the
////! rectangle are assumed to be within the extents of the display, and the
////! rectangle specification is fully inclusive (in other words, both sXMin and
////! sXMax are drawn, along with sYMin and sYMax).
////!
////! \return None.
////
////*****************************************************************************
//void Sharp128x128_RectFill(void *pvDisplayData,
//                                const Graphics_Rectangle *pRect,
//                                uint16_t ulValue)
//{
//    uint16_t xi = 0;
//    uint16_t yi = 0;
//    uint16_t x_index_min = pRect->sXMin >> 3;
//    uint16_t x_index_max = pRect->sXMax >> 3;
//    uint8_t *pucData, ucfirst_x_byte, uclast_x_byte;
//
//    //calculate first byte
//    //mod by 8 and shift this # bits
//    ucfirst_x_byte = (0xFF >> (pRect->sXMin & 0x7));
//
//    //calculate last byte
//    //mod by 8 and shift this # bits
//    uclast_x_byte = (0xFF << (7 - (pRect->sXMax & 0x7)));
//
//    //check if more than one data byte
//    if(x_index_min != x_index_max)
//    {
//        //write bytes
//        for(yi = pRect->sYMin; yi <= pRect->sYMax; yi++)
//        {
//            //set buffer to correct location
//            pucData = &DisplayBuffer[yi][x_index_min];
//
//            //black pixels (clear bits)
//            if(ClrBlack == ulValue)
//            {
//                //write first byte
//                *pucData++ &= ~ucfirst_x_byte;
//
//                //write middle bytes
//                for(xi = x_index_min; xi < x_index_max - 1; xi++)
//                {
//                    *pucData++ = 0x00;
//                }
//
//                //write last byte
//                *pucData &= ~uclast_x_byte;
//            }
//            //white pixels (set bits)
//            else
//            {
//                //write first byte
//                *pucData++ |= ucfirst_x_byte;
//
//                //write middle bytes
//                for(xi = x_index_min; xi < x_index_max - 1; xi++)
//                {
//                    *pucData++ = 0xFF;
//                }
//
//                //write last byte
//                *pucData |= uclast_x_byte;
//            }
//        }
//    }
//    //only one data byte
//    else
//    {
//        //calculate value of single byte
//        ucfirst_x_byte &= uclast_x_byte;
//
//        //set buffer to correct location
//        pucData = &DisplayBuffer[pRect->sYMin][x_index_min];
//
//        //black pixels (clear bits)
//        if(ClrBlack == ulValue)
//        {
//            *pucData++ &= ~ucfirst_x_byte;
//        }
//        //white pixels (set bits)
//        else
//        {
//            *pucData++ |= ucfirst_x_byte;
//        }
//    }
//}
//
////*****************************************************************************
////
////! Translates a 24-bit RGB color to a display driver-specific color.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////!   display driver
////! \param ulValue is the 24-bit RGB color.  The least-significant byte is the
////!   blue channel, the next byte is the green channel, and the third byte is
////!   the red channel.
////!
////! This fucntion translates a 24-bit RGB color into a value that can be written
////! into the display's frame buffer in order to reproduce that color, or the
////! closest possible approximation of that color. This particular driver
////! requires the 8-8-8 24 bit RGB color to convert into mono color
////! 1 = White, 0 = Black
////!
////! \return Returns the display-driver specific color
////
////*****************************************************************************
//uint32_t Sharp128x128_ColorTranslate(void *pvDisplayData,
//                                          uint32_t ulValue)
//{
//    //
//    // Translate from a 24-bit RGB color to mono color.
//    //
//    return(((ulValue != 0) ? ulValue = 1 : ulValue));
//}
//
////*****************************************************************************
////
////! Flushes any cached drawing operations.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////!
////!
////! This functions flushes any cached drawing operations to the display.  This
////! is useful when a local frame buffer is used for drawing operations, and the
////! flush would copy the local frame buffer to the display.
////!
////! \return None.
////
////*****************************************************************************
//void Sharp128x128_Flush(void *pvDisplayData)
//{
//    uint8_t *pucData = &DisplayBuffer[0][0];
//    int32_t xi = 0;
//    int32_t xj = 0;
//    //image update mode(1X000000b)
//    uint8_t command = SHARP_LCD_CMD_WRITE_LINE;
//
//    //COM inversion bit
//    command = command ^ VCOMbit;
//
//    //HAL_LCD_setCS();
//
//    LCDwriteCommand(command);
//
//    flagSendToggleVCOMCommand = SHARP_SKIP_TOGGLE_VCOM_COMMAND;
//#ifdef LANDSCAPE
//    for(xj = 0; xj < LCD_VERTICAL_MAX; xj++)
//    {
//        LCDwriteCommand(Sharp128x128_reverse(xj + 1));
//
//        for(xi = 0; xi < (LCD_HORIZONTAL_MAX >> 3); xi++)
//        {
//            LCDwriteCommand(*(pucData++));
//        }
//        LCDwriteCommand(SHARP_LCD_TRAILER_BYTE);
//    }
//#endif
//#ifdef LANDSCAPE_FLIP
//    pucData =
//        &DisplayBuffer[LCD_VERTICAL_MAX - 1][(LCD_HORIZONTAL_MAX >> 3) - 1];
//
//    for(xj = 1; xj <= LCD_VERTICAL_MAX; xj++)
//    {
//        LCDwriteCommand(Sharp128x128_reverse(xj));
//
//        for(xi = 0; xi < (LCD_HORIZONTAL_MAX >> 3); xi++)
//        {
//            LCDwriteCommand(Sharp128x128_reverse(*pucData--));
//        }
//        LCDwriteCommand(SHARP_LCD_TRAILER_BYTE);
//    }
//#endif
//
//    LCDwriteCommand(SHARP_LCD_TRAILER_BYTE);
//
//    // Wait for last byte to be sent, then drop SCS
//    //HAL_LCD_waitUntilLcdWriteFinish();
//
//    // Ensure a 2us min delay to meet the LCD's thSCS
//    //__delay_cycles(SYSTEM_CLOCK_SPEED * 0.000002);
//
//    //HAL_LCD_clearCS();
//}
//
////*****************************************************************************
////
////! Send command to clear screen.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param ucValue is the background color of the buffered data.
////!
////! This function sets every pixel to the background color.
////!
////! \return None.
////
////*****************************************************************************
//void Sharp128x128_ClearScreen(void *pvDisplayData,
//                                   uint16_t ulValue)
//{
//    //clear screen mode(0X100000b)
//    uint8_t command = SHARP_LCD_CMD_CLEAR_SCREEN;
//    //COM inversion bit
//    command = command ^ VCOMbit;
//
//    //HAL_LCD_setCS();
//
//    LCDwriteCommand(command);
//    flagSendToggleVCOMCommand = SHARP_SKIP_TOGGLE_VCOM_COMMAND;
//    LCDwriteCommand(SHARP_LCD_TRAILER_BYTE);
//
//    // Wait for last byte to be sent, then drop SCS
//    //HAL_LCD_waitUntilLcdWriteFinish();
//
//    // Ensure a 2us min delay to meet the LCD's thSCS
//    //__delay_cycles(SYSTEM_CLOCK_SPEED * 0.000002);
//
//    //HAL_LCD_clearCS();
//    if(ClrBlack == ulValue)
//    {
//        Sharp128x128_InitializeDisplayBuffer(pvDisplayData, SHARP_BLACK);
//    }
//    else
//    {
//        Sharp128x128_InitializeDisplayBuffer(pvDisplayData, SHARP_WHITE);
//    }
//}
//
////*****************************************************************************
////
////! The display structure that describes the driver for the
////! sharpLCD panel
////
////*****************************************************************************
//const Graphics_Display g_sharp128x128LCD =
//{
//    sizeof(tDisplay),
//    DisplayBuffer,
//    LCD_HORIZONTAL_MAX,
//    LCD_VERTICAL_MAX,
//    Sharp128x128_PixelDraw, //PixelDraw,
//    Sharp128x128_DrawMultiple,
//    Sharp128x128_LineDrawH,
//    Sharp128x128_LineDrawV, //LineDrawV,
//    Sharp128x128_RectFill, //RectFill,
//    Sharp128x128_ColorTranslate,
//    Sharp128x128_Flush, //Flush
//    Sharp128x128_ClearScreen //Clear screen. Contents of display buffer unmodified
//};
