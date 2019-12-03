#ifndef HWMSGTYPES_H_
#define HWMSGTYPES_H_

typedef struct __attribute__((packed)) {
    uint8_t opcode;
    uint8_t flags;
    uint16_t size;

} HWHeader_t;

typedef struct __attribute__((packed)) {
    HWHeader_t header;
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

#endif
