#include "SPI.h"

void SPIinit(){
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3); //init SPI3 (FrontPanel)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1); //init SPI1 (GPIOEX)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2); //init SPI2 (ADC)

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //GPIOPinConfigure(GPIO_PD0_SSI3CLK);
    //GPIOPinConfigure(GPIO_PD2_SSI3RX); //miso
    //GPIOPinConfigure(GPIO_PD3_SSI3TX); //mosi

    GPIOPinConfigure(GPIO_PF2_SSI1CLK);
    //GPIOPinConfigure(GPIO_PB3_SSI0FSS);
    GPIOPinConfigure(GPIO_PF0_SSI1RX); //miso
    GPIOPinConfigure(GPIO_PF1_SSI1TX); //mosi

    GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    //GPIOPinConfigure(GPIO_PB3_SSI0FSS);
    GPIOPinConfigure(GPIO_PB6_SSI2RX); //miso
    GPIOPinConfigure(GPIO_PB7_SSI2TX); //mosi


    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7);

    //SSIConfigSetExpClk(SSI3_BASE, 16000000, SSI_FRF_MOTO_MODE_0,
    //                       SSI_MODE_MASTER, 1000000, 8);

    SSIConfigSetExpClk(SSI1_BASE, 16000000, SSI_FRF_MOTO_MODE_0,
                           SSI_MODE_MASTER, 500000, 8);

    SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                           SSI_MODE_MASTER, 1000000, 8);
    SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                               SSI_MODE_MASTER, 500000, 8);

    SSIEnable(SSI1_BASE);
    SSIEnable(SSI2_BASE);
    //SSIEnable(SSI3_BASE);
}
