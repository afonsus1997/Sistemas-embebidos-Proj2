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
//#include "uart.h"
//test


#define EGSEManagerSTACKSIZE        1000         // Stack size in words

extern xQueueHandle g_pUartRPIQueue;

typedef volatile struct {
    uint8_t rxBuff[255];
    size_t rxIdxWrite;
    size_t rxIdxRead;
    size_t rxSize;
} uartmsg_t;

static BaseType_t xHigherPriorityTaskWoken = pdFALSE;


static void vEGSEManagerTask(void *pvParameters);

uint32_t vEGSEManagerTaskINIT(void);

extern void handle_EPTMsg(ETPUnion_t *msg);

