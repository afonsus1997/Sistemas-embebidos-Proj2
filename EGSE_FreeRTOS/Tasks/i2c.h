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

#define I2CEGSETaskStackSize        128         // Stack size in words

typedef volatile struct {
    uint8_t rxBuff[255];
    size_t rxIdxWrite;
    size_t rxIdxRead;
    size_t rxSize;
} uartmsg_t;

#define I2CEGSE_ITEM_SIZE           sizeof(uint8_t)
#define I2CEGSE_QUEUE_SIZE          5

xQueueHandle g_pI2CEGSEQueue;



//BaseType_t xHigherPriorityTaskWoken = pdFALSE;


uint32_t vI2CEGSETaskInit(void);


static void vI2CEGSETask(void *pvParameters);

