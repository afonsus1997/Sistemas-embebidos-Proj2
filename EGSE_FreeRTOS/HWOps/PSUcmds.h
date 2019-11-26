#ifndef PSUCMDS_H_
#define PSUCMDS_H_

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

#include "HWmsgtypes.h"
#include "GPIOex.h"
#include "HardwareIOConfig.h"


void PSUcmd(uint8_t opcode, HWPSUCmd_t * PSUmsg);

#endif
