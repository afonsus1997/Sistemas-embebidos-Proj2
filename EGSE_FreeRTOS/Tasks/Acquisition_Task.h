/*
 * Acquisition_Task.h
 *
 *  Created on: Nov 27, 2019
 *      Author: Afonso Muralha
 */

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
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "../HWOps/HardwareIOConfig.h"
#include "../HWOps/ADCconversion.h"
#include "../ETP/msgtypes.h"

#define AcquisitionTaskSTACKSIZE        750         // Stack size in words

#define ZERO_THRESHOLD 1

typedef struct __attribute__((packed)) {
    uint16_t ADCs[26];
//    uint16_t ADCs[32];
    uint8_t GPIO[13];

} LastReadings_t;

LastReadings_t RawReadings;
LastReadings_t LastReadings;

extern uint8_t PSUstatus[6];





