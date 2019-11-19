#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "priorities.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"

#define I2CEGSETaskStackSize        500         // Stack size in words
#define I2CEGSE_ITEM_SIZE           sizeof(uint32_t)
#define I2CEGSE_QUEUE_SIZE          5
#define I2C_MODULE 0
#define TIVA_ADDR 0x08
//#define SLAVE_ADDRESS 0x00

xQueueHandle g_pI2C_EGSEQueue;
SemaphoreHandle_t xsI2Cin;

void InitI2C(void);
uint32_t vI2CEGSETaskInit(void);
void I2CInt0Handler(void);
static void vI2CEGSETask(void *pvParameters);
void I2CsetMaster(uint8_t i2cModule);
void I2CsetSlave(uint8_t i2cModule, uint8_t address);
