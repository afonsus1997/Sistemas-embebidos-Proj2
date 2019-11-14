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
#include "../ETP/msgtypes.h"


#define UartRPITASKSTACKSIZE        500         // Stack size in words


#ifdef USBDEBUG
    #define DEBUG_UARTBASE 0
#endif
#ifndef USBDEBUG
    #define DEBUG_UARTBASE 3
#endif

#define UartRPI_ITEM_SIZE           sizeof(uartmsg_t)
#define UartRPI_QUEUE_SIZE          5

xQueueHandle g_pUartRPIQueue;
extern xQueueHandle g_pLEDQueue;

SemaphoreHandle_t xsUARTin;

BaseType_t xHigherPriorityTaskWoken = pdTRUE;


uint32_t UartRPITaskInit(void);

static void UartRPITask(void *pvParameters);


/*===========  DATA TYPES ===========*/

typedef volatile struct {  //uart reading type
    uint8_t rxBuff[255];
    size_t rxIdxWrite;
    size_t rxIdxRead;
    size_t rxSize;
} uartmsg_t;




