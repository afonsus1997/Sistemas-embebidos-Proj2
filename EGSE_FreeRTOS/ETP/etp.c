#include "etp.h"

void EGSE_newHeader(ETPUnion_t *msg, ETPOpcode_e opcode, size_t size) {
    msg->header =
        (ETPHeader_t){.opcode = (uint8_t)opcode, .flags = 0, .size = (uint16_t)(size)};
}

void EGSE_newAck(ETPUnion_t *msg) { EGSE_newHeader(msg, ETPOpcode_Ack, 0); }

void EGSE_newSync(ETPUnion_t *msg) { EGSE_newHeader(msg, ETPOpcode_Sync, 0); }

void EGSE_newKeepAlive(ETPUnion_t *msg) { EGSE_newHeader(msg, ETPOpcode_KeepAlive, 0); }

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


void handle_EPTMsg(ETPUnion_t * msg){
    ETPHeader_t *header = &msg->header;
    ETPUnion_t * msgtemp;
    ETPUnionHW_t hwmsg;


    //UARTprintf("[EGSE Manager Task] - Got Opcode");
    //UARTprintf("%s\n", header->opcode);

    switch(header->opcode){
        case ETPOpcode_Sync: {
            UARTprintf("[EGSE Manager Task] - Got sync request from RPI\n");
            EGSE_ready = true;
            EGSE_sendSync(msgtemp);
            EGSE_sendLog(msgtemp, "Hi there!");
            UARTprintf("[EGSE Manager Task] - Sent sync to RPI\n");
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
            UARTprintf("[EGSE Manager Task] - Got Keep Alive request from RPI\n");
            EGSE_newKeepAlive(msgtemp);
            EGSE_sendUARTRPI(msgtemp);
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
           UARTprintf("[EGSE Manager Task] - Sending to UART3DATA request from RPI\n");
           EGSE_sendUART3(msg);
           break;
       }

       case ETPOpcode_reset: {
           UARTprintf("[EGSE Manager Task] - Rebooting TIVA\n");
           const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
           vTaskDelay(xDelay);
           HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;
           break;
       }

       case ETPOpcode_PSUSingle: {
          UARTprintf("[EGSE Manager Task] - Got PSUSET opcode\n");
          memcpy(&hwmsg, msg, sizeof(ETPUnionHW_t));
          xQueueSend(g_HardwareTaskQueueToHardware, (void *) &hwmsg, portMAX_DELAY);
          break;
      }

       case ETPOpcode_ADCSingle: {
          UARTprintf("[EGSE Manager Task] - Got EGSEADCsingle opcode\n");
          memcpy(&hwmsg, msg, sizeof(ETPUnionHW_t));
         xQueueSend(g_HardwareTaskQueueToHardware, (void *) &hwmsg, portMAX_DELAY);
          break;
      }

       case ETPOpcode_GPIOread: {
          UARTprintf("[EGSE Manager Task] - Got GPIOread opcode\n");
          xQueueSend(g_HardwareTaskQueueToHardware, (void *) msg, portMAX_DELAY);
          break;
      }

       case ETPOpcode_GPIOwrite: {
            UARTprintf("[EGSE Manager Task] - Got GPIOread opcode\n");
            //xQueueSend(g_HardwareTaskQueueToHardware, (void *) &msg, portMAX_DELAY);
            break;
       }
       case ETPOpcode_GPIOmode: {
            UARTprintf("[EGSE Manager Task] - Got GPIOset opcode\n");
            xQueueSend(g_HardwareTaskQueueToHardware, (void *) &msg, portMAX_DELAY);
            break;
    }

       default: {
           UARTprintf("[EGSE Manager Task] - Unknown opcode\n");
           break;
       }

    }

}


void HandleHWRX(ETPUnionHW_t * HWmsg){
    ETPUnion_t toUART;

    memcpy(&toUART, HWmsg, sizeof(ETPUnionHW_t));
    EGSE_sendUARTRPI(&toUART);

}

