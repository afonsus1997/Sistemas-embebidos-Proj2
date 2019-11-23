#include "GPIOex.h"

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

uint8_t GPIOexReceiveRegSPI(uint8_t exid, uint8_t addr){
    uint8_t i = 3;
    uint8_t msg[2];
    uint8_t rcv;
    msg[0] = 0b01000001;
    msg[1] = addr;

    unsigned char *buff = &msg[0];
    if(exid == 0){
        //toggle cs
        GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
        while(i--);
            SSIDataPut(SSI1_BASE, buff++);
        //rcv=Recieve msg (send dummy byte 0xFF);
        GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
        return rcv;
    }
    else if (exid == 1){
        //toggle cs
        GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX_BASE, 0);
        while(i--);
            SSIDataPut(SSI1_BASE, buff++);
        GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX_BASE, 1);
    }
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
        EXreg[exid][addr] = GPIOexReceiveRegSPI(exid, addr);
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

    uint8_t mode = (EXreg[exid][dirReg] & (1<<pin)) == 0 ? OUTPUT : INPUT;

    switch (mode) {
        case OUTPUT:
            if (value == 0) {
                EXreg[exid][latReg] &= ~(1<<pin);
            } else {
                EXreg[exid][latReg] |= (1<<pin);
            }
            GPIOexSendRegSPI(exid, latReg);
            break;

        case INPUT:
            if (value == 0) {
                EXreg[exid][puReg] &= ~(1<<pin);
            } else {
                EXreg[exid][puReg] |= (1<<pin);
            }
            GPIOexSendRegSPI(exid, puReg);
            break;
    }


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
//    GPIOexSendmsgSPI(1, (uint8_t *)&msg, 4);
//    GPIOexToggleCS(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
    GPIOexSendmsgSPI(2, (uint8_t *)&msg, 3);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);

//    GPIOexWriteAll();

    msg[0] = 0b01000000;
    msg[1] = (uint8_t)IODIRA;
    msg[2] = 0x0;

    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
    GPIOexSendmsgSPI(2, (uint8_t *)&msg, 3);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);

    msg[0] = 0b01000000;
    msg[1] = (uint8_t)IODIRB;
    msg[2] = 0x0;

    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
    GPIOexSendmsgSPI(2, (uint8_t *)&msg, 3);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);

    msg[0] = 0b01000000;
    msg[1] = (uint8_t)GPIOA;
    msg[2] = 0xFF;

    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
    GPIOexSendmsgSPI(2, (uint8_t *)&msg, 3);
    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);

//    msg[0] = 0b01000000;
//    msg[1] = (uint8_t)GPIOB;
//    msg[2] = 0b01111111;
//
//    EXreg[1][GPIOB] = 0b11111111;
//
//    GPIOexSendRegSPI(1, GPIOB);

//    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
//    GPIOexSendmsgSPI(2, (uint8_t *)&msg, 3);
//    GPIOexToggleCS(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);

//    GPIOexReadRegister(1, IODIRA);
    GPIOexPinMode(1, SW_EN2, OUTPUT);

    GPIOexGPIOWrite(1, SW_EN2, 1);

}
