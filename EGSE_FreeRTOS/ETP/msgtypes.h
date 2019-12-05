
typedef struct __attribute__((packed)) {
    uint8_t opcode;
    uint8_t flags;
    uint16_t size;

} ETPHeader_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint8_t addr;
    uint8_t data[];
} ETPMsgI2C_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint16_t vals[7];
} ETPADCSample_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint32_t timeTotal;
    uint32_t timeActive;
    uint8_t ocmOBCState; // 0 -> off, 1 -> on, 2-> restarting
    uint8_t ocm3V3State;
} ETPTivaReport_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint8_t id;
    uint8_t state;
    uint16_t limit;
    uint32_t restart_period_ms;
} ETPETPOCMState_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    char text[256];
} ETPLog_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint8_t addr;
    uint16_t num;
    uint8_t data[];
} ETPMsgI2CReplay_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint8_t data[256];
} ETPSPI0_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint8_t data[256];
} ETPUART0_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint8_t opcode;
    uint8_t errcode;
} ETPReply_t;

/*======HARDWARE RELATED=======*/

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint8_t PSUsingle[2];
} ETPPSUCmd_t;

typedef struct __attribute__((packed)) {
    ETPHeader_t header;
    uint16_t ADCsingle[2];
} ETPEGSEADCCmd_t;

typedef enum {
    PSUNum,
    PSUState
} PSUStatetypes_e;

typedef enum {
    ADCNum,
    ADCVal
} ADCReport_e;

typedef enum {
    ADC_V1_VAL, ADC_I1_VAL,
    ADC_V2_VAL, ADC_I2_VAL,
    ADC_V3_VAL, ADC_I3_VAL,
    ADC_V4_VAL, ADC_I4_VAL,
    ADC_V5_VAL, ADC_I5_VAL,
    ADC_V6_VAL, ADC_I6_VAL,
    EGSE_ADC1, EGSE_ADC2,
    EGSE_ADC3, EGSE_ADC4,
    EGSE_ADC5, EGSE_ADC6,
    EGSE_ADC7, EGSE_ADC8,
    EXP_ADC1_VAL, EXP_ADC2_VAL,
    EXP_ADC3_VAL, EXP_ADC4_VAL,
    BAT_V, BAT_I
} ADCVals_e;

typedef enum {
    GPIO_1, GPIO_2,
    GPIO_3, GPIO_4,
    GPIO_5, GPIO_6,
    GPIO_7, GPIO_8,
    GPIO_9, GPIO_10,
    GPIO_11, GPIO_12, GPIO_13,
} GPIOVals_e;

/*===========================*/


typedef union {
    ETPHeader_t header;
    ETPMsgI2C_t msgI2C;
    ETPADCSample_t adcSample;
    ETPTivaReport_t tivaReport;
    ETPETPOCMState_t ocmState;
    ETPLog_t log;
    ETPMsgI2CReplay_t msgI2CReplay;
    ETPSPI0_t spi0;
    ETPUART0_t uart0;
    ETPReply_t etpreply;
    ETPPSUCmd_t etppsu;
    ETPEGSEADCCmd_t etpEGSEAdc;
    //etpgpio


    // maximum possible packet size (derived from ax25) + error margin
    uint8_t raw[sizeof(ETPHeader_t) + 256 + 16];
} ETPUnion_t;

// NOTE: Must match the enum in src/python/egse.py
typedef enum {
    ETPOpcode_Ack = 0,
    ETPOpcode_Sync = 1,
    ETPOpcode_DeSync = 2,
    ETPOpcode_I2C0Frame = 3,
    ETPOpcode_I2C1Frame = 4,
    ETPOpcode_AdcSamples = 5,
    ETPOpcode_TivaReport = 6,
    ETPOpcode_ETPOCMState = 7,
    ETPOpcode_KeepAlive = 8,
    ETPOpcode_Log = 9,
    ETPOpcode_Ping = 10,
    ETPOpcode_Pong = 11,
    ETPOpcode_I2C0Replay = 12,
    ETPOpcode_SPI0Frame = 13,
    ETPOpcode_UART0Data = 14,
    ETPOpcode_reset = 15,
    ETPOpcode_PSUSingle = 16,
    ETPOpcode_ADCSingle = 17,
    ETPOpcode_GPIOmode = 18,
    ETPOpcode_GPIOset = 19,
    ETPOpcode_GPIOread = 20,
    ETPOpcode_Reply = 21,

    ETPOpcode__num,

} ETPOpcode_e;

typedef enum {

    InvalidPSUVal,
    InvalidADCVal,
} ETPErrCode_e;
