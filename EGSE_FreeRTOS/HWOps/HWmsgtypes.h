#ifndef HWMSGTYPES_H_
#define HWMSGTYPES_H_

typedef struct __attribute__((packed)) {
    uint8_t opcode;
    uint8_t flags;
    uint16_t size;

} HWHeader_t;

typedef struct __attribute__((packed)) {
    HWHeader_t header;
    uint8_t PSUall[6];
    uint8_t PSUsingle[2];
} HWPSUCmd_t;

typedef struct __attribute__((packed)) {
    HWHeader_t header;
    uint8_t ADCall[39];
    uint8_t ADCsingle[2];
} HWADCCmd_t;

typedef union {
    HWHeader_t header;
    HWPSUCmd_t PSU;
    HWADCCmd_t ADC;
} HWUnion_t;

typedef enum {
    HWOpcode_Ack,
    HWOpcode_PSUall,
    HWOpcode_PSUSingle,
    HWOpcode_ADCall,
    HWOpcode_ADCSingle,
    HWOpcode_GPIOmode,
    HWOpcode_GPIOset,
    HWOpcode_reset
} HWOpcode_e;


typedef enum {
    PSUNum,
    PSUState
} PSUStatetypes_e;

typedef enum {
    ADCNum,
    ADCVal
} ADCReport_e;

typedef enum {
    ADC_V1, ADC_I1,
    ADC_V2, ADC_I2,
    ADC_V3, ADC_I3,
    ADC_V4, ADC_I4,
    ADC_V5, ADC_I5,
    ADC_V6, ADC_I6,
    EGSE_ADC1, EGSE_ADC2,
    EGSE_ADC3, EGSE_ADC4,
    EGSE_ADC5, EGSE_ADC6,
    EGSE_ADC7, EGSE_ADC8,
    EXP_ADC1_VAL, EXP_ADC2_VAL,
    EXP_ADC3_VAL, EXP_ADC4_VAL,
    GPIO_1, GPIO_2,
    GPIO_3, GPIO_4,
    GPIO_5, GPIO_6,
    GPIO_7, GPIO_8,
    GPIO_9, GPIO_10,
    GPIO_11, GPIO_12, GPIO_13,
    BAT_V, BAT_I
} ADCVals_e;

#endif
