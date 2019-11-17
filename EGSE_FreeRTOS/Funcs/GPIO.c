#include "GPIO.h"

static int8_t vHardwareIOInit(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, SPI_MASTER_FP | SPI_MASTER_EGSE | CS2_GPIO_EX);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, BAT_CHARGE_EN | CS_DAC2 | CS1_GPIO_EX);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, UART_EGSE_ENA | UART_EGSE_ENB);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, CS_EGSE | UART_EGSE_ENB | BAT_GND_EN);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, CS_DAC1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, BAT_CHARGE_CTRL);

    //Initialize GPIO with default values

    return 1;

}
