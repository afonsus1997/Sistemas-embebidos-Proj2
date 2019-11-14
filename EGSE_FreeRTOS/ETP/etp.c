#include "etp.h"



void EGSE_newHeader(ETPUnion_t *msg, ETPOpcode_e opcode, size_t size) {
    msg->header =
        (ETPHeader_t){.opcode = (uint8_t)opcode, .flags = 0, .size = (uint16_t)(size)};
}

void EGSE_newAck(ETPUnion_t *msg) { EGSE_newHeader(msg, ETPOpcode_Ack, 0); }

void EGSE_newSync(ETPUnion_t *msg) { EGSE_newHeader(msg, ETPOpcode_Sync, 0); }

void EGSE_sendSync(ETPUnion_t *msg) {
    EGSE_newSync(msg);
    EGSE_sendUARTRPI(msg);
}

void EGSE_newLog(ETPUnion_t *msg, const char *log) {
    size_t size = strlen(log);
    EGSE_newHeader(msg, ETPOpcode_Log, size);
    memmove(msg->log.text, log, size);
}

void EGSE_sendLog(ETPUnion_t *msg, const char *log) {
    EGSE_newLog(msg, log);
    EGSE_sendUARTRPI(msg);
}

void EGSE_sendPong(ETPUnion_t *msg) {
    EGSE_newHeader(msg, ETPOpcode_Pong, 0);
    EGSE_sendUARTRPI(msg);
}


void handle_EPTMsg(ETPUnion_t *msg){
    ETPHeader_t *header = &msg->header;
    ETPUnion_t *msgtemp;

    switch(header->opcode){
        case ETPOpcode_Sync: {
            UARTprintf("[EGSE Manager Task] - Got sync request from RPI\n");
            EGSE_ready = true;
            EGSE_sendSync(msgtemp);
            EGSE_sendLog(msgtemp, "Hi there!");
            break;
       }
        case ETPOpcode_DeSync: {
            UARTprintf("[EGSE Manager Task] - Got desync request from RPI\n");
            EGSE_ready = false;

            break;
       }
        case ETPOpcode_I2C0Frame: {

            break;
       }
        case ETPOpcode_I2C0Replay: {

            break;
       }

        case ETPOpcode_ETPOCMState: {

            break;
       }
        case ETPOpcode_KeepAlive: {

            break;
       }

        case ETPOpcode_Ping: {
            UARTprintf("[EGSE Manager Task] - Got ping from RPI\n");
            EGSE_sendPong(msgtemp);
            break;
       }

        case ETPOpcode_Pong: {
            break;
       }

       case ETPOpcode_SPI0Frame: {

           break;
       }

       case ETPOpcode_UART0Data: {

           break;
       }

       case ETPOpcode_reset: {

           break;
       }

       default: {

           break;
       }

    }

}
