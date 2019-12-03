#include "PSUcmds.h"

uint8_t SW_EN_map[6] = {SW_EN1, SW_EN2, SW_EN3, SW_EN4, SW_EN5, SW_EN6};


void PSUcmd(uint8_t opcode, HWPSUCmd_t * PSUmsg){
    if(opcode == HWOpcode_PSUSingle){
        GPIOexGPIOWrite(1, SW_EN_map[PSUmsg->PSUsingle[0]], PSUmsg->PSUsingle[1]);
    }

}
