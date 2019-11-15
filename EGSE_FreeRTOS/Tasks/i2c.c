#include "i2c.h"

static void vI2CEGSETask(void *pvParameters){
    // If necessary, it is the interrupt handler’s responsibility to
    // clear the interrupt source via I2CMasterIntClear()

    //while(1){}

}

void I2CInt0Handler(void)
{
    //uint32_t ui32Status;
    //ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

    //ROM_UARTIntClear(UART0_BASE, ui32Status);

    //xSemaphoreGiveFromISR( xsUARTin, &xHigherPriorityTaskWoken );

    //if(xHigherPriorityTaskWoken == pdTRUE)
    ///portYIELD_FROM_ISR();
}

/*void InitI2C0(void){
    //enable I2C module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    //reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    //enable GPIO peripheral that contains I2C 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    //I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    //clear I2C FIFOs
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;

    // Enable the Interrupt in the NVIC from I2C Master
    IntEnable(INT_I2C0);
}*/

void InitI2C0(void){
    //Enable GPIO for Configuring the I2C Interface Pins
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);

    // Wait for the Peripheral to be ready for programming

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)
             || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK));

    // Configure Pins for I2C0 Master Interface
    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    // Stop the Clock, Reset and Enable I2C Module in Master Function
    SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    I2CMasterIntEnable(I2C0_BASE);
    I2CIntRegister(I2C0_BASE,&I2CInt0Handler);

    // Enable the Interrupt in the NVIC from I2C Master
    IntEnable(INT_I2C0);
}

uint32_t vI2CEGSETaskInit(void){

    InitI2C0();

    xsI2Cin = xSemaphoreCreateBinary();

    g_pI2CEGSEQueue = xQueueCreate(I2CEGSE_QUEUE_SIZE, I2CEGSE_ITEM_SIZE);

    if(xTaskCreate(vI2CEGSETask, (const portCHAR *)"I2C_RPI", I2CEGSETaskStackSize, NULL,
                   tskIDLE_PRIORITY + PRIORITY_I2C_RPI_TASK , NULL) != pdTRUE)
    {
        return(1);
    }

    return(0);
}



