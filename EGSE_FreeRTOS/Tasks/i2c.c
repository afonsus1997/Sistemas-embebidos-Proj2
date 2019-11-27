#include "i2c.h"

static const unsigned long g_uli2cMasterBase[2] =
{
    I2C1_BASE, I2C2_BASE
};

static const unsigned long g_uli2cSlaveBase[2] =
{
    I2C1_BASE, I2C2_BASE
};

//*****************************************************************************
//
// The list of possible interrupts for the console i2c.
//
//*****************************************************************************
static const unsigned long g_uli2cInt[2] =
{
    INT_I2C1, INT_I2C2
};

//*****************************************************************************
//
// The list of i2c peripherals.
//
//*****************************************************************************
static const unsigned long g_uli2cPeriph[2] =
{
    SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_I2C2
};

//*****************************************************************************
//
// The list of i2c gpio configurations (GPIO Port/Pin+Function assignments).
//
//*****************************************************************************
static const unsigned long g_uli2cConfig[2][2] =
{
    {GPIO_PA6_I2C1SCL, GPIO_PA7_I2C1SDA},
    {GPIO_PE4_I2C2SCL, GPIO_PE5_I2C2SDA}
};

//*****************************************************************************
//
// The list of i2c gpio configurations (GPIO Base registers).
//
//*****************************************************************************
static const unsigned long g_uli2cBase[2] =
{
    GPIO_PORTA_BASE, GPIO_PORTE_BASE
};

//*****************************************************************************
//
// The list of i2c gpio configurations (SDA, SCL pins).
//
//*****************************************************************************
static const unsigned long g_uli2cSDAPins[2] =
{
    GPIO_PIN_7, GPIO_PIN_5
};
static const unsigned long g_uli2cSCLPins[2] =
{
    GPIO_PIN_6, GPIO_PIN_4
};

static void vI2CEGSETask(void *pvParameters){
    uint32_t msg;
    while(1){
        if(xSemaphoreTake(xsI2Cin, portMAX_DELAY ) == pdTRUE ){
            //send I2C command to queue
            //UARTprintf("[UART Task] - Sent Command to I2C queue\n");
            msg = I2CSlaveDataGet(g_uli2cSlaveBase[0]);
            xQueueSend(g_pI2C_EGSEQueue, (void *)&msg, 0);
        }
    }
}

void I2CInt0Handler(void){
    static portBASE_TYPE xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    I2CSlaveIntClear(g_uli2cSlaveBase[0]);

    xSemaphoreGiveFromISR(xsI2Cin, &xHigherPriorityTaskWoken);

    if(xHigherPriorityTaskWoken == pdTRUE)
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void I2CbeginTransmission(uint8_t i2cModule, uint8_t address){
  transmitting[i2cModule] = 1;
  // set address of targeted slave
  txAddress[i2cModule] = address;
  txReadIndex[i2cModule] = 0;
  txWriteIndex[i2cModule] = 0;
}


//Initialize as a master
void I2CsetMaster(uint8_t i2cModule){
    unsigned long CPU_freq;
    CPU_freq = SysCtlClockGet();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(g_uli2cPeriph[i2cModule]);

    //Configure GPIO pins for I2C operation
    GPIOPinConfigure(g_uli2cConfig[i2cModule][0]);
    GPIOPinConfigure(g_uli2cConfig[i2cModule][1]);
    GPIOPinTypeI2C(g_uli2cBase[i2cModule], g_uli2cSDAPins[i2cModule]);
    GPIOPinTypeI2CSCL(g_uli2cBase[i2cModule], g_uli2cSCLPins[i2cModule]);
    I2CMasterInitExpClk(g_uli2cMasterBase[i2cModule], CPU_freq, false);
}

//Initialize as a slave
void I2CsetSlave(uint8_t i2cModule, uint8_t address){

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    SysCtlPeripheralEnable(g_uli2cPeriph[i2cModule]);
    GPIOPinConfigure(g_uli2cConfig[i2cModule][0]);
    GPIOPinConfigure(g_uli2cConfig[i2cModule][1]);
    GPIOPinTypeI2C(g_uli2cBase[i2cModule], g_uli2cSDAPins[i2cModule]);
    GPIOPinTypeI2CSCL(g_uli2cBase[i2cModule], g_uli2cSCLPins[i2cModule]);

    //Enable slave interrupts
    IntEnable(g_uli2cInt[i2cModule]);
    I2CSlaveIntEnableEx(g_uli2cSlaveBase[0], I2C_SLAVE_INT_DATA | I2C_SLAVE_INT_STOP);

    //Setup as a slave device
    I2CMasterDisable(g_uli2cMasterBase[0]);
    I2CSlaveEnable(g_uli2cSlaveBase[0]);
    I2CSlaveInit(g_uli2cSlaveBase[0], address);
}

void InitI2C(void){
    unsigned long CPU_freq;
    CPU_freq = SysCtlClockGet();

    //enable I2C modules 1 and 2
    SysCtlPeripheralEnable(g_uli2cPeriph[0]);
    SysCtlPeripheralEnable(g_uli2cPeriph[1]);

    //reset modules 1 and 2
    SysCtlPeripheralReset(g_uli2cPeriph[0]);
    SysCtlPeripheralReset(g_uli2cPeriph[1]);

    //enable GPIO peripheral that contains I2C1 and I2C2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Configure the pin muxing for I2C1(A6,A7) and I2C2(E4,E5)
    GPIOPinConfigure(g_uli2cConfig[0][0]);
    GPIOPinConfigure(g_uli2cConfig[0][1]);
    GPIOPinConfigure(g_uli2cConfig[1][0]);
    GPIOPinConfigure(g_uli2cConfig[1][1]);

    // Select the I2C function for these pins.
    GPIOPinTypeI2C(g_uli2cBase[0], g_uli2cSDAPins[0]);
    GPIOPinTypeI2CSCL(g_uli2cBase[0], g_uli2cSCLPins[0]);
    GPIOPinTypeI2C(g_uli2cBase[1], g_uli2cSDAPins[1]);
    GPIOPinTypeI2CSCL(g_uli2cBase[1], g_uli2cSCLPins[1]);

    I2CMasterInitExpClk(g_uli2cMasterBase[0], CPU_freq, false);
    I2CMasterInitExpClk(g_uli2cMasterBase[1], CPU_freq, false);

    //I2CMasterIntEnable(g_uli2cMasterBase[0]);
    //I2CIntRegister(g_uli2cMasterBase[0],&I2CInt0Handler);

    // Enable the Interrupt in the NVIC from I2C Master
    //IntEnable(g_uli2cMasterBase[0]);
}

uint32_t vI2CEGSETaskInit(void){

    //InitI2C();
    //I2CsetSlave(I2C_MODULE,TIVA_ADDR);

    xsI2Cin = xSemaphoreCreateBinary();

    g_pI2C_EGSEQueue = xQueueCreate(I2CEGSE_QUEUE_SIZE, I2CEGSE_ITEM_SIZE);

    if(xTaskCreate(vI2CEGSETask, (const portCHAR *)"I2C_RPI", I2CEGSETaskStackSize, NULL,
                   tskIDLE_PRIORITY + PRIORITY_I2C_RPI_TASK , NULL) != pdTRUE)
    {
        return(1);
    }

    return(0);
}
