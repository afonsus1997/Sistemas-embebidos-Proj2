/*
 * HardwareIOConfig.h
 *
 *  Created on: Nov 17, 2019
 *      Author: Afonso Muralha
 */

#ifndef TASKS_HARDWAREIOCONFIG_H_
#define TASKS_HARDWAREIOCONFIG_H_

#include "driverlib/gpio.h"

//=======GPIO Expander 1==========
#define GPIO1 1 //GPB0
#define GPIO2 2 //GPB1
#define GPIO3 3 //GPB2
#define GPIO4 4 //GPB3
#define GPIO5 5 //GPB4
#define GPIO6 6 //GPB5
#define GPIO7 7 //GPB6
#define GPIO8 8 //GPB7

#define BAT_DISCHARGE1 21 //GPB0
#define BAT_DISCHARGE0 22 //GPB1
#define REG_PGOOD_3V3 23 //GPB2
#define REG_EN_3V3 24 //GPB3
#define REG_PGOOD_ALT 25 //GPB4
#define REG_EN_ALT 26 //GPB5
#define REG_PGOOD_MAIN 27 //GPB6
#define REG_EN_MAIN 28 //GPB7

//================================

//=======GPIO Expander 2==========
#define SW_EN2 1 //GPB0
#define SW_EN1 2 //GPB1
#define EOC1 3 //GPB2
#define EOC2 4 //GPB3
#define SW_EN4 5 //GPB4
#define SW_EN3 6 //GPB5
#define SW_EN6 7 //GPB6
#define SW_EN5 8 //GPB7

#define FP_EXP1 21 //GPB0
#define FP_EXP2 22 //GPB1
#define FP_EXP3 23 //GPB2
#define FP_EXP4 24 //GPB3
#define FP_EXP5 25 //GPB4
#define ADC_SHUTDOWN 26 //GPB5
#define ADC_TRIGGER 27 //GPB6
#define NOT_CONNECTED 28 //GPB7

//================================

//============TIVA================

#define BAT_CHARGE_EN   GPIO_PIN_5 //PB5
#define CS_DAC2         GPIO_PIN_0 //PB0
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
#define CS_DAC1         GPIO_PIN_0 //PE0
#define MISO_GPIO_EX    GPIO_PIN_0 //PF0
#define MOSI_ADC        GPIO_PIN_7 //PB7
#define MISO_ADC        GPIO_PIN_6 //PB6
#define SPI_MASTER_EGSE GPIO_PIN_4 //PA4
#define CS2_GPIO_EX     GPIO_PIN_3 //PA3


//=============TIVA_BASES==========

#define BAT_CHARGE_EN_BASE   GPIO_PORTB_BASE //PB5
#define CS_DAC2_BASE         GPIO_PORTB_BASE //PB0
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
#define CS_DAC1_BASE         GPIO_PORTE_BASE //PE0
#define MISO_GPIO_EX_BASE    GPIO_PORTF_BASE //PF0
#define MOSI_ADC_BASE        GPIO_PORTB_BASE //PB7
#define MISO_ADC_BASE        GPIO_PORTB_BASE //PB6
#define SPI_MASTER_EGSE_BASE GPIO_PORTA_BASE //PA4
#define CS2_GPIO_EX_BASE     GPIO_PORTA_BASE //PA3




#endif /* TASKS_HARDWAREIOCONFIG_H_ */
