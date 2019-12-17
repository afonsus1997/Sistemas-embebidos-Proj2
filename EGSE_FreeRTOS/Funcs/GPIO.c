#include "GPIO.h"

void vHardwareIOInit(){
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, SPI_MASTER_FP | SPI_MASTER_EGSE | CS2_GPIO_EX);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, CS2_GPIO_EX);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, BAT_CHARGE_EN | CS_ADC2 | CS1_GPIO_EX);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, UART_EGSE_ENA | UART_EGSE_ENB);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, UART_EGSE_ENB | BAT_GND_EN);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, CS_ADC1 | CS_LCD | CS_SDCARD);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, BAT_CHARGE_CTRL);
    //ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, CS2_GPIO_EX, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //Initialize GPIO with default values
    ROM_GPIOPinWrite(GPIO_PORTB_BASE, CS1_GPIO_EX, CS1_GPIO_EX);
    ROM_GPIOPinWrite(GPIO_PORTA_BASE, CS2_GPIO_EX, CS2_GPIO_EX);

    ROM_GPIOPinWrite(CS_ADC1_BASE, CS_ADC1, CS_ADC1);
    ROM_GPIOPinWrite(CS_ADC2_BASE, CS_ADC2, CS_ADC2);
    ROM_GPIOPinWrite(CS_LCD_BASE, CS_LCD, CS_LCD);
    ROM_GPIOPinWrite(CS_SDCARD_BASE, CS_SDCARD, CS_SDCARD);

    //ROM_GPIOPinWrite(GPIO_PORTA_BASE, CS2_GPIO_EX, 0);

//    for(;;);

}


uint8_t GPIOcmd(ETPUnionHW_t * msg){
    switch(msg->header.opcode){
        case ETPOpcode_GPIOmode :
            GPIOexPinMode(0, GPIOex0PinMap[msg->etpgpio.id], msg->etpgpio.Val);
        case ETPOpcode_GPIOwrite :
            GPIOexGPIOWrite(0, GPIOex0PinMap[msg->etpgpio.id], msg->etpgpio.Val);
        case ETPOpcode_GPIOread :
            msg->etpgpio.Val = GPIOexGPIORead(0, GPIOex0PinMap[msg->etpgpio.id]);
        default:
            break;
        return 0;
    }
}
