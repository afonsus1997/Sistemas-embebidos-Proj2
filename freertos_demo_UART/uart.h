#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define UartRPITASKSTACKSIZE        128         // Stack size in words


#define UartRPI_ITEM_SIZE           sizeof(uint8_t)
#define UartRPI_QUEUE_SIZE          5

xQueueHandle g_pUartRPIQueue;


uint32_t UartRPITaskInit(void);

static void UartRPITask(void *pvParameters);

