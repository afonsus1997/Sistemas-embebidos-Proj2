#ifndef HARDWARE_MANAGER_TASK_H_
#define HARDWARE_MANAGER_TASK_H_


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
#include "../Funcs/GPIO.h"
#include "../HWOps/GPIOex.h"
#include "../HWOps/ADC.h"
#include "../HWOps/LCD.h"
#include "../HWOps/PSUcmds.h"
#include "../Funcs/GPIO.h"


#define HardwareManagerTaskSTACKSIZE        500         // Stack size in words

#define HARDWARE_QUEUE_ITEM_SIZE           sizeof(ETPUnionHW_t)
#define HARDWARE_QUEUE_QUEUE_SIZE          10

xQueueHandle g_HardwareTaskQueueFromHardware;
xQueueHandle g_HardwareTaskQueueToHardware;

uint8_t PSUstatus[6] = {1, 1, 1, 1, 1, 1};

extern LastReadings_t LastReadings;

//BaseType_t xHigherPriorityTaskWoken = pdFALSE;

uint32_t vHardwareManagerTaskINIT(void);

static void vHardwareManagerTask(void *pvParameters);

#endif
