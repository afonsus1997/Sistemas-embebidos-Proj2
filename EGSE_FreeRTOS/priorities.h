//*****************************************************************************
//
// priorities.h - Priorities for the various FreeRTOS tasks.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#ifndef __PRIORITIES_H__
#define __PRIORITIES_H__

//*****************************************************************************
//
// The priorities of the various tasks.
//
//*****************************************************************************
#define PRIORITY_SWITCH_TASK       1
#define PRIORITY_LED_TASK          1
#define PRIORITY_UartRPI_TASK      3
#define PRIORITY_I2C_RPI_TASK      1
#define PRIORITY_EGSE_MANAGER_TASK 2
#define PRIORITY_HARDWARE_TASK     3
#define PRIORITY_ACQUISITION_TASK  1

#endif // __PRIORITIES_H__
