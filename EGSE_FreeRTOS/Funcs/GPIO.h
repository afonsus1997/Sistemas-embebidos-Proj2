#ifndef GPIO_H_
#define GPIO_H_


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

#include "../HWOps/HardwareIOConfig.h"
#include "../ETP/msgtypes.h"
#include "../HWOps/GPIOex.h"

void vHardwareIOInit();

uint8_t GPIOcmd(ETPUnionHW_t * msg);

extern uint8_t GPIOex0PinMap[8];

#endif
