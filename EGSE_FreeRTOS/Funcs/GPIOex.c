#include "GPIOex.h"

uint8_t msg[10];


void GPIOexSendmsgSPI(uint8_t exid, uint8_t * buf, uint8_t size){

    uint8_t buff = &buf[0];
    uint8_t ln = size;

    if(exid == 1){
        //toggle cs
        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
        while(ln--);
            //send buff++
        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
    }
    else if (exid == 2){
        //toggle cs
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
        while(ln--);
            //send buff++
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
    }
}



void GPIOexSendRegSPI(uint8_t exid, uint8_t addr){
    uint8_t i = 3;
    uint8_t msg[3];
    uint8_t rcv;
    msg[0] = 0b01000000;
    msg[1] = addr;

    if(exid == 1){
        msg[2] = EX0reg[addr];
        //toggle cs
        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
        while(i--);
            //send msg

        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
    }
    else if (exid == 2){
        msg[2] = EX0reg[addr];
        //toggle cs
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
        while(i--);
                    //send buff++
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
    }
}

uint8_t GPIOexReceiveRegSPI(uint8_t exid, uint8_t addr){
    uint8_t i = 2;
    uint8_t msg[2];
    uint8_t rcv;
    msg[0] = 0b01000001;
    msg[1] = addr;

    unsigned char *buff = &msg[0];
    if(exid == 1){
        //toggle cs
        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 0);
        while(i--);
            //send msg
        //rcv=Recieve msg (send dummy byte 0xFF);

        GPIOPinWrite(CS1_GPIO_EX_BASE, CS1_GPIO_EX, 1);
        return rcv;
    }
    else if (exid == 2){
        //toggle cs
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 0);
        while(i--);
                    //send buff++
        GPIOPinWrite(CS2_GPIO_EX_BASE, CS2_GPIO_EX, 1);
    }
}



void GPIOexBegin(){

    SPIinit();

    EX0reg[IODIRA] = 0xFF;
    EX0reg[IODIRB] = 0xFF;
    EX0reg[IPOLA] = 0x00;
    EX0reg[IPOLB] = 0x00;
    EX0reg[GPINTENA] = 0x00;
    EX0reg[GPINTENB] = 0x00;
    EX0reg[DEFVALA] = 0x00;
    EX0reg[DEFVALB] = 0x00;
    EX0reg[INTCONA] = 0x00;
    EX0reg[INTCONB] = 0x00;
    EX0reg[IOCONA] = 0x18;
    EX0reg[IOCONB] = 0x18;
    EX0reg[GPPUA] = 0x00;
    EX0reg[GPPUB] = 0x00;
    EX0reg[INTFA] = 0x00;
    EX0reg[INTFB] = 0x00;
    EX0reg[INTCAPA] = 0x00;
    EX0reg[INTCAPB] = 0x00;
    EX0reg[GPIOA] = 0x00;
    EX0reg[GPIOB] = 0x00;
    EX0reg[OLATA] = 0x00;
    EX0reg[OLATB] = 0x00;

    EX1reg[IODIRA] = 0xFF;
    EX1reg[IODIRB] = 0xFF;
    EX1reg[IPOLA] = 0x00;
    EX1reg[IPOLB] = 0x00;
    EX1reg[GPINTENA] = 0x00;
    EX1reg[GPINTENB] = 0x00;
    EX1reg[DEFVALA] = 0x00;
    EX1reg[DEFVALB] = 0x00;
    EX1reg[INTCONA] = 0x00;
    EX1reg[INTCONB] = 0x00;
    EX1reg[IOCONA] = 0x18;
    EX1reg[IOCONB] = 0x18;
    EX1reg[GPPUA] = 0x00;
    EX1reg[GPPUB] = 0x00;
    EX1reg[INTFA] = 0x00;
    EX1reg[INTFB] = 0x00;
    EX1reg[INTCAPA] = 0x00;
    EX1reg[INTCAPB] = 0x00;
    EX1reg[GPIOA] = 0x00;
    EX1reg[GPIOB] = 0x00;
    EX1reg[OLATA] = 0x00;
    EX1reg[OLATB] = 0x00;


    msg[0] = 0b01000000;
    msg[1] = IOCONA;
    msg[2] = 0x10;

    GPIOexSendmsgSPI(0, &msg, 3);
    GPIOexSendmsgSPI(1, &msg, 3);

}


void GPIOexReadRegister(uint8_t exid, uint8_t addr){
    if (addr > 21) {
        return;
    }
    else{
        if (exid == 0)
            EX0reg[addr] = GPIOexReceiveRegSPI(exid, addr);
        else if(exid == 1)
            EX1reg[addr] = GPIOexReceiveRegSPI(exid, addr);
    }

}

void GPIOexWriteRegister(uint8_t exid, uint8_t addr){
    if (addr > 21) {
        return;
    }
    else{
        if (exid == 0)
            GPIOexReceiveRegSPI(exid, addr);
        else if(exid == 1)
            GPIOexReceiveRegSPI(exid, addr);
    }

}

