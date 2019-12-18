#include "GPIOex.h"

uint8_t GPIOex0PinMap[8] = {GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7};


//#define psutest

uint8_t msg[10];

void GPIOexToggleCS(uint32_t GPIOBASE, uint32_t GPIOPin, uint32_t state){
    if(state){
        while(SSIBusy(SSI1_BASE));
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
        SysCtlDelay(1);
    }
    else{
//        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, GPIOPin);
        ROM_GPIOPinWrite(GPIOBASE, GPIOPin, 0);
    }
}

void GPIOexSendmsgSPI(uint8_t exid, uint8_t * buf, uint16_t size){
    unsigned char * buff = &buf[0];
    uint8_t ln = size;

    while(ln--)
        SSIDataPut(SSI1_BASE, *buff++);
}



void GPIOexSendRegSPI(uint8_t exid, uint8_t addr){
    uint8_t i = 3;
    uint8_t msg[3];
    uint8_t rcv;
    msg[0] = 0b01000000;
    msg[1] = addr;
    msg[2] = EXreg[exid][addr];
    unsigned char * buff = &msg[0];
    if(exid == 0){

        //toggle cs
        GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
        while(i--)
            SSIDataPut(SSI1_BASE, *buff++);
        GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
    }
    else if (exid == 1){
        //toggle cs
        GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
        while(i--)
            SSIDataPut(SSI1_BASE, *buff++);
        GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
    }
}

void GPIOexReceiveRegSPI(uint8_t exid, uint8_t addr){
    uint8_t i = 2;
    uint8_t msg[2];
    uint8_t rcv;
    msg[0] = 0b01000001;
    msg[1] = addr;
    msg[2] = 0b00000000;
    unsigned char *buff = &msg[0];

    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
    SSIDataPut(SSI1_BASE, buff++);
    while(SSIBusy(SSI1_BASE));
    SSIDataPut(SSI1_BASE, buff++);
    while(SSIBusy(SSI1_BASE));
    SSIDataPut(SSI1_BASE, buff);
    while(SSIBusy(SSI1_BASE));
    SSIDataGet(SSI1_BASE, &rcv);
    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
    EXreg[exid][addr] = rcv;
    UARTprintf("SPI DataGet %d\n", rcv);

    /*GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
    SSIDataPut(SSI1_BASE, buff++);
    while(SSIBusy(SSI1_BASE));
    SSIDataPut(SSI1_BASE, buff);
    while(SSIBusy(SSI1_BASE));
    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
    SSIDataGet(SSI1_BASE, &rcv);
    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);*/


   /* unsigned char *buff = &msg[0];
    if(exid == 0){
        //toggle cs
        GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
        while(i--){
            SSIDataPut(SSI1_BASE, buff++);
            while(SSIBusy(SSI1_BASE));
        }
        SSIDataGet(SSI1_BASE, &rcv);
        while(SSIBusy(SSI1_BASE));
        GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
        EXreg[exid][addr] = rcv;
        UARTprintf("SPI DataGet %d\n", rcv);
    }
    else if (exid == 1){
        //toggle cs
        GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX_BASE, 0);
        while(i--)
            SSIDataPut(SSI1_BASE, buff++);
        SSIDataGet(SSI1_BASE, &rcv);
        GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX_BASE, 1);
        EXreg[exid][addr] = rcv;
    }*/
}

uint8_t GPIOexWriteAll(){
    uint8_t msg[2] = {0b01000000, 0};
//    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
//    GPIOexSendmsgSPI(1, (uint8_t *)&msg, 2);
//    GPIOexSendmsgSPI(1, (uint8_t* )&EXreg[0], EXRegSIZE);
//    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);

    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
    GPIOexSendmsgSPI(2, (uint8_t *)&msg, 2);
    GPIOexSendmsgSPI(2, (uint8_t* )&EXreg[1], EXRegSIZE);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
}



void GPIOexReadRegister(uint8_t exid, uint8_t addr){
    if (addr > 21) {
        return;
    }
    else{
        GPIOexReceiveRegSPI(exid, addr);
    }

}

void GPIOexWriteRegister(uint8_t exid, uint8_t addr){
    if (addr > 21) {
        return;
    }
    else{
        GPIOexReceiveRegSPI(exid, addr);
    }
}


void GPIOexPinMode(uint8_t exid, uint8_t pin, uint8_t mode){
    if (pin >= 16) {
        return;
    }
    uint8_t dirReg = IODIRA;
    uint8_t puReg = GPPUA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = IODIRB;
        puReg = GPPUB;
    }

    switch (mode) {
        case OUTPUT:
            EXreg[exid][dirReg] &= ~(1<<pin);
            GPIOexSendRegSPI(exid, dirReg);
            break;

        case INPUT:
        case INPUT_PULLUP:
            EXreg[exid][dirReg] |= (1<<pin);
            GPIOexSendRegSPI(exid, dirReg);
            if (mode == INPUT_PULLUP) {
                EXreg[exid][puReg] |= (1<<pin);
            } else {
                EXreg[exid][puReg] &= ~(1<<pin);
            }
            GPIOexSendRegSPI(exid, puReg);
            break;
    }
}


void GPIOexGPIOWrite(uint8_t exid, uint8_t pin, uint8_t value){

    if (pin >= 16) {
        return;
    }
    uint8_t dirReg = IODIRA;
    uint8_t puReg = GPPUA;
    uint8_t latReg = OLATA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = IODIRB;
        puReg = GPPUB;
        latReg = OLATB;
    }


    uint8_t mode = ((EXreg[exid][dirReg] & (1<<pin)) == 0) ? OUTPUT : INPUT;

    UARTprintf("Pin: %d, Value: %d, Mode: %d\n", pin, value, mode);


    switch (mode) {
        case OUTPUT:
            if (value == 0) {
                EXreg[exid][latReg] &= ~(1<<pin);
            } else {
                EXreg[exid][latReg] |= (1<<pin);
            }
            GPIOexSendRegSPI(exid, latReg);
            UARTprintf("Latreg: %d\n", EXreg[exid][latReg]);
            break;

        /*case INPUT:
            if (value == 0) {
                EXreg[exid][puReg] &= ~(1<<pin);
            } else {
                EXreg[exid][puReg] |= (1<<pin);
            }
            GPIOexSendRegSPI(exid, puReg);
            break;*/
    }


}

uint8_t GPIOexGPIORead(uint8_t exid, uint8_t pin){
    if (pin >= 16) {
        return;
    }
    uint8_t dirReg = IODIRA;
    uint8_t portReg = GPIOA;
    uint8_t latReg = OLATA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = IODIRB;
        portReg = GPIOB;
        latReg = OLATB;
    }

    uint8_t mode = ((EXreg[exid][dirReg] & (1<<pin)) == 0) ? OUTPUT : INPUT;
    UARTprintf("Pin: %d, Mode: %d\n", pin, mode);

    switch(mode){
        case OUTPUT:
            UARTprintf("Latreg: %d\n", EXreg[exid][latReg]);
            return ((EXreg[exid][latReg] & (1<<pin)) == 0) ? 0 : 1;
        case INPUT:
            GPIOexReceiveRegSPI(exid, portReg);
            return ((EXreg[exid][portReg] & (1<<pin)) == 0) ? 0 : 1;
    }
    return 1;

}

void GPIOexBegin(){



    EXreg[0][IODIRA] = 0xFF;
    EXreg[0][IODIRB] = 0xFF;
    EXreg[0][IPOLA] = 0x00;
    EXreg[0][IPOLB] = 0x00;
    EXreg[0][GPINTENA] = 0x00;
    EXreg[0][GPINTENB] = 0x00;
    EXreg[0][DEFVALA] = 0x00;
    EXreg[0][DEFVALB] = 0x00;
    EXreg[0][INTCONA] = 0x00;
    EXreg[0][INTCONB] = 0x00;
    EXreg[0][IOCONA] = 0x18;
    EXreg[0][IOCONB] = 0x18;
    EXreg[0][GPPUA] = 0x00;
    EXreg[0][GPPUB] = 0x00;
    EXreg[0][INTFA] = 0x00;
    EXreg[0][INTFB] = 0x00;
    EXreg[0][INTCAPA] = 0x00;
    EXreg[0][INTCAPB] = 0x00;
    EXreg[0][GPIOA] = 0x00;
    EXreg[0][GPIOB] = 0x00;
    EXreg[0][OLATA] = 0x00;
    EXreg[0][OLATB] = 0x00;

    EXreg[1][IODIRA] = 0x00;
    EXreg[1][IODIRB] = 0x00;
    EXreg[1][IPOLA] = 0x00;
    EXreg[1][IPOLB] = 0x00;
    EXreg[1][GPINTENA] = 0x00;
    EXreg[1][GPINTENB] = 0x00;
    EXreg[1][DEFVALA] = 0x00;
    EXreg[1][DEFVALB] = 0x00;
    EXreg[1][INTCONA] = 0x00;
    EXreg[1][INTCONB] = 0x00;
    EXreg[1][IOCONA] = 0x8;
    EXreg[1][IOCONB] = 0x8;
    EXreg[1][GPPUA] = 0x00;
    EXreg[1][GPPUB] = 0x00;
    EXreg[1][INTFA] = 0x00;
    EXreg[1][INTFB] = 0x00;
    EXreg[1][INTCAPA] = 0x00;
    EXreg[1][INTCAPB] = 0x00;
    EXreg[1][GPIOA] = 0xFF;
    EXreg[1][GPIOB] = 0xFF;
    EXreg[1][OLATA] = 0x00;
    EXreg[1][OLATB] = 0x00;


    msg[0] = 0b01000000;
    msg[1] = (uint8_t)IOCONA;
    msg[2] = 0x8;

//    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
//    GPIOexSendmsgSPI(1, (uint8_t *)&msg, 3);
//    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
    GPIOexSendmsgSPI(1, (uint8_t *)&msg, 3);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);



    //define psu as outputs
    GPIOexPinMode(SW_EN1_EXID, SW_EN1, OUTPUT);
    GPIOexPinMode(SW_EN2_EXID, SW_EN2, OUTPUT);
    GPIOexPinMode(SW_EN3_EXID, SW_EN3, OUTPUT);
    GPIOexPinMode(SW_EN4_EXID, SW_EN4, OUTPUT);
    GPIOexPinMode(SW_EN5_EXID, SW_EN5, OUTPUT);
    GPIOexPinMode(SW_EN6_EXID, SW_EN6, OUTPUT);
    //set default psu output as 0
    GPIOexGPIOWrite(SW_EN1_EXID, SW_EN1, 1);
    GPIOexGPIOWrite(SW_EN2_EXID, SW_EN2, 1);
    GPIOexGPIOWrite(SW_EN3_EXID, SW_EN3, 1);
    GPIOexGPIOWrite(SW_EN4_EXID, SW_EN4, 1);
    GPIOexGPIOWrite(SW_EN5_EXID, SW_EN5, 1);
    GPIOexGPIOWrite(SW_EN6_EXID, SW_EN6, 1);

    //define front panel exp as outputs
    GPIOexPinMode(FP_EXP1_EXID, FP_EXP1, OUTPUT);
    GPIOexPinMode(FP_EXP2_EXID, FP_EXP2, OUTPUT);
    GPIOexPinMode(FP_EXP3_EXID, FP_EXP3, OUTPUT);
    GPIOexPinMode(FP_EXP4_EXID, FP_EXP4, OUTPUT);
    GPIOexPinMode(FP_EXP5_EXID, FP_EXP5, OUTPUT);
    //set default front panel exp output as 0



#ifdef psutest
    int i = 0;
    while(1){
        GPIOexGPIOWrite(SW_EN1_EXID, SW_EN1, !i);
        GPIOexGPIOWrite(SW_EN2_EXID, SW_EN2, i);
        GPIOexGPIOWrite(SW_EN3_EXID, SW_EN3, !i);
        GPIOexGPIOWrite(SW_EN4_EXID, SW_EN4, i);
        GPIOexGPIOWrite(SW_EN5_EXID, SW_EN5, !i);
        GPIOexGPIOWrite(SW_EN6_EXID, SW_EN6, i);
        i=!i;
        SysCtlDelay(1000000);

    }
#endif


}
