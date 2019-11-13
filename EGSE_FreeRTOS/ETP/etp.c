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
