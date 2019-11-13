
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

    ETPOpcode__num,

} ETPOpcode_e;
