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

#include "HardwareIOConfig.h"
#include "SPI.h"
#include "GPIO.h"

uint8_t EX0reg[22];   /*! Local mirrors of the 22 internal registers of the MCP23S17 chip */
uint8_t EX1reg[22];

enum {
    IODIRA,     IODIRB,
    IPOLA,      IPOLB,
    GPINTENA,   GPINTENB,
    DEFVALA,    DEFVALB,
    INTCONA,    INTCONB,
    IOCONA,     IOCONB,
    GPPUA,      GPPUB,
    INTFA,      INTFB,
    INTCAPA,    INTCAPB,
    GPIOA,      GPIOB,
    OLATA,      OLATB
};

void readRegister(uint8_t addr);
void writeRegister(uint8_t addr);
void readAll();
void writeAll();



void GPIOexBegin();
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
uint8_t digitalRead(uint8_t pin);

uint8_t readPort(uint8_t port);
void writePort(uint8_t port, uint8_t val);
void enableInterrupt(uint8_t pin, uint8_t type);
void disableInterrupt(uint8_t pin);
//void setMirror(boolean m);
uint16_t getInterruptPins();
uint16_t getInterruptValue();
void setInterruptLevel(uint8_t level);
//void setInterruptOD(boolean openDrain);
