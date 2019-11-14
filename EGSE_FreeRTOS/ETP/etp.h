#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "msgtypes.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "FreeRTOS.h"

void EGSE_newHeader(ETPUnion_t *msg, ETPOpcode_e opcode, size_t size);

void EGSE_newAck(ETPUnion_t *msg);

void EGSE_newSync(ETPUnion_t *msg);

void EGSE_sendSync(ETPUnion_t *msg);

void EGSE_newLog(ETPUnion_t *msg, const char *log);

void EGSE_sendLog(ETPUnion_t *msg, const char *log);

void EGSE_sendPong(ETPUnion_t *msg);

extern void EGSE_sendUARTRPI(ETPUnion_t *msg);

static _Atomic bool EGSE_ready;
