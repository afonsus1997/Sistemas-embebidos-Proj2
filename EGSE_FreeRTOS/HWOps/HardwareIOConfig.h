/*
 * HardwareIOConfig.h
 *
 *  Created on: Nov 17, 2019
 *      Author: Afonso Muralha
 */

#ifndef TASKS_HARDWAREIOCONFIG_H_
#define TASKS_HARDWAREIOCONFIG_H_

#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"


#define GPIOexPIN_21  0
#define GPIOexPIN_22  1
#define GPIOexPIN_23  2
#define GPIOexPIN_24  3
#define GPIOexPIN_25  4
#define GPIOexPIN_26  5
#define GPIOexPIN_27  6
#define GPIOexPIN_28  7
#define GPIOexPIN_1   8
#define GPIOexPIN_2   9
#define GPIOexPIN_3   10
#define GPIOexPIN_4   11
#define GPIOexPIN_5   12
#define GPIOexPIN_6   13
#define GPIOexPIN_7   14
#define GPIOexPIN_8   15

//=======GPIO Expander 1==========
#define GPIO1 GPIOexPIN_1 //GPB0
#define GPIO2 GPIOexPIN_2 //GPB1
#define GPIO3 GPIOexPIN_3 //GPB2
#define GPIO4 GPIOexPIN_4 //GPB3
#define GPIO5 GPIOexPIN_5 //GPB4
#define GPIO6 GPIOexPIN_6 //GPB5
#define GPIO7 GPIOexPIN_7 //GPB6
#define GPIO8 GPIOexPIN_8 //GPB7

#define BAT_DISCHARGE1 GPIOexPIN_21 //GPB0
#define BAT_DISCHARGE0 GPIOexPIN_22 //GPB1
#define REG_PGOOD_3V3 GPIOexPIN_23 //GPB2
#define REG_EN_3V3 GPIOexPIN_24 //GPB3
#define REG_PGOOD_ALT GPIOexPIN_25 //GPB4
#define REG_EN_ALT GPIOexPIN_26 //GPB5
#define REG_PGOOD_MAIN GPIOexPIN_27 //GPB6
#define REG_EN_MAIN GPIOexPIN_28 //GPB7

#define GPIO1_EXID 0 //GPB0
#define GPIO2_EXID 0 //GPB1
#define GPIO3_EXID 0 //GPB2
#define GPIO4_EXID 0 //GPB3
#define GPIO5_EXID 0 //GPB4
#define GPIO6_EXID 0 //GPB5
#define GPIO7_EXID 0 //GPB6
#define GPIO8_EXID 0 //GPB7

#define BAT_DISCHARGE1_EXID 0 //GPB0
#define BAT_DISCHARGE0_EXID 0 //GPB1
#define REG_PGOOD_3V3_EXID 0 //GPB2
#define REG_EN_3V3_EXID 0 //GPB3
#define REG_PGOOD_ALT_EXID 0 //GPB4
#define REG_EN_ALT_EXID 0 //GPB5
#define REG_PGOOD_MAIN_EXID 0 //GPB6
#define REG_EN_MAIN_EXID 0 //GPB7

//================================

//=======GPIO Expander 2==========
#define SW_EN2 GPIOexPIN_1 //GPB0
#define SW_EN1 GPIOexPIN_2 //GPB1
#define EOC1 GPIOexPIN_3 //GPB2
#define EOC2 GPIOexPIN_4 //GPB3
#define SW_EN4 GPIOexPIN_5 //GPB4
#define SW_EN3 GPIOexPIN_6 //GPB5
#define SW_EN6 GPIOexPIN_7 //GPB6
#define SW_EN5 GPIOexPIN_8 //GPB7

#define FP_EXP1 GPIOexPIN_21 //GPB0
#define FP_EXP2 GPIOexPIN_22 //GPB1
#define FP_EXP3 GPIOexPIN_23 //GPB2
#define FP_EXP4 GPIOexPIN_24 //GPB3
#define FP_EXP5 GPIOexPIN_25 //GPB4
#define ADC_SHUTDOWN GPIOexPIN_26 //GPB5
#define ADC_TRIGGER GPIOexPIN_27 //GPB6
#define NOT_CONNECTED GPIOexPIN_28 //GPB7

#define SW_EN2_EXID 1 //GPB0
#define SW_EN1_EXID 1//GPB1
#define EOC1_EXID 1//GPB2
#define EOC2_EXID 1//GPB3
#define SW_EN4_EXID 1//GPB4
#define SW_EN3_EXID 1//GPB5
#define SW_EN6_EXID 1//GPB6
#define SW_EN5_EXID 1//GPB7

#define FP_EXP1_EXID 1//GPB0
#define FP_EXP2_EXID 1//GPB1
#define FP_EXP3_EXID 1//GPB2
#define FP_EXP4_EXID 1//GPB3
#define FP_EXP5_EXID 1//GPB4
#define ADC_SHUTDOWN_EXID 1//GPB5
#define ADC_TRIGGER_EXID 1//GPB6
#define NOT_CONNECTED_EXID 1//GPB7

//================================

//============TIVA================

#define BAT_CHARGE_EN   GPIO_PIN_5 //PB5
#define CS_ADC2         GPIO_PIN_0 //PB0
#define CS1_GPIO_EX     GPIO_PIN_1 //PB1
#define I2C1_CLK        GPIO_PIN_4 //PE4
#define I2C1_DATA       GPIO_PIN_5 //PE5
#define SCK_ADC         GPIO_PIN_5 //PB5
#define SPI_MASTER_FP   GPIO_PIN_5//PA5
#define I2C0_CLK        GPIO_PIN_6 //PA6
#define I2C0_DATA       GPIO_PIN_7 //PA7

#define SCK_EGSE        GPIO_PIN_0 //PD0
#define CS_EGSE         GPIO_PIN_1 //PD1
#define MISO_EGSE       GPIO_PIN_2 //PD2
#define MOSI_EGSE       GPIO_PIN_3 //PD3
#define MOSI_GPIO_EX    GPIO_PIN_1 //PF1

#define SCK_GPIO_EX     GPIO_PIN_2 //PF2
#define BAT_CHARGE_CTRL GPIO_PIN_3 //PF3
#define REG_PGOOD       GPIO_PIN_3 //PB3
#define UART_EGSE_ENA   GPIO_PIN_4 //PC4
#define UART_EGSE_ENB   GPIO_PIN_5 //PC5
#define UART_EGSE_TX    GPIO_PIN_6 //PC6
#define UART_EGSE_RX    GPIO_PIN_7 //PC7
#define BAT_GND_EN      GPIO_PIN_7 //PD7

#define ADC_TRIGGER_TIVA GPIO_PIN_2 //PB2
#define CS_ADC1         GPIO_PIN_0 //PE0
#define MISO_GPIO_EX    GPIO_PIN_0 //PF0
#define MOSI_ADC        GPIO_PIN_7 //PB7
#define MISO_ADC        GPIO_PIN_6 //PB6
#define SPI_MASTER_EGSE GPIO_PIN_4 //PA4
#define CS2_GPIO_EX     GPIO_PIN_3 //PA3


//=============TIVA_BASES==========

#define BAT_CHARGE_EN_BASE   GPIO_PORTB_BASE //PB5
#define CS_ADC2_BASE         GPIO_PORTB_BASE //PB0
#define CS1_GPIO_EX_BASE     GPIO_PORTB_BASE //PB1
#define I2C1_CLK_BASE        GPIO_PORTE_BASE //PE4
#define I2C1_DATA_BASE       GPIO_PORTE_BASE //PE5
#define SCK_ADC_BASE         GPIO_PORTB_BASE //PB5
#define SPI_MASTER_FP_BASE   GPIO_PORTA_BASE//PA5
#define I2C0_CLK_BASE        GPIO_PORTA_BASE //PA6
#define I2C0_DATA_BASE       GPIO_PORTA_BASE //PA7

#define SCK_EGSE_BASE        GPIO_PORTD_BASE //PD0
#define CS_EGSE_BASE         GPIO_PORTD_BASE //PD1
#define MISO_EGSE_BASE       GPIO_PORTD_BASE //PD2
#define MOSI_EGSE_BASE       GPIO_PORTD_BASE //PD3
#define MOSI_GPIO_EX_BASE    GPIO_PORTF_BASE //PF1

#define SCK_GPIO_EX_BASE     GPIO_PORTF_BASE //PF2
#define BAT_CHARGE_CTRL_BASE GPIO_PORTF_BASE //PF3
#define REG_PGOOD_BASE       GPIO_PORTB_BASE //PB3
#define UART_EGSE_ENA_BASE   GPIO_PORTC_BASE //PC4
#define UART_EGSE_ENB_BASE   GPIO_PORTC_BASE //PC5
#define UART_EGSE_TX_BASE    GPIO_PORTC_BASE //PC6
#define UART_EGSE_RX_BASE    GPIO_PORTC_BASE //PC7
#define BAT_GND_EN_BASE      GPIO_PORTD_BASE //PD7

#define ADC_TRIGGER_TIVA_BASE GPIO_PORTB_BASE //PB2
#define CS_ADC1_BASE         GPIO_PORTE_BASE //PE0
#define MISO_GPIO_EX_BASE    GPIO_PORTF_BASE //PF0
#define MOSI_ADC_BASE        GPIO_PORTB_BASE //PB7
#define MISO_ADC_BASE        GPIO_PORTB_BASE //PB6
#define SPI_MASTER_EGSE_BASE GPIO_PORTA_BASE //PA4
#define CS2_GPIO_EX_BASE     GPIO_PORTA_BASE //PA3

//================================

//============ADC 2===============

#define ADC_V2      AIN0
#define ADC_I2      AIN1
#define ADC_V5      AIN2
#define ADC_I5      AIN3
#define ADC_V3      AIN4
#define ADC_I3      AIN5
#define ADC_V1      AIN6
#define ADC_I1      AIN7
#define EXP_ADC1    AIN11
#define EXP_ADC2    AIN12
#define EXP_ADC3    AIN13
#define EXP_ADC4    AIN14
//#define ADC_TRIGGER AIN15

//================================

//============ADC 1===============

#define ADC_BAT_I AIN0
#define ADC_BAT_V AIN1
#define ESGE_ADC1 AIN2
#define ESGE_ADC2 AIN3
#define ESGE_ADC3 AIN4
#define ESGE_ADC4 AIN5
#define ESGE_ADC5 AIN6
#define ESGE_ADC6 AIN7
#define ESGE_ADC7 AIN8
#define ESGE_ADC8 AIN9
#define ADC_V6    AIN10
#define ADC_I6    AIN11
#define ADC_I4    AIN12
#define ADC_V4    AIN13
//#define NULL    AIN14


#endif /* TASKS_HARDWAREIOCONFIG_H_ */
