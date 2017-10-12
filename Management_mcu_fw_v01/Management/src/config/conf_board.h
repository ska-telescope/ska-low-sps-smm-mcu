/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H


// ---------- Fan Management ----------
#define PIN_RPM1 PIO_PA0_IDX
#define PIN_RMP2 PIO_PA1_IDX

// ---------- I2C ----------
#define I2C1SDA PIO_PA3_IDX
#define I2C1SDA (PIO_PERIPH_A | PIO_DEFAULT)
#define I2C1SCL PIO_PA4_IDX
#define I2C1SCL (PIO_PERIPH_A | PIO_DEFAULT)

// ---------- GPIO ----------
#define XO3_REFRESH PIO_PA6_IDX

#define PIN_LEDK7 PIO_PA23_IDX
#define PIN_LEDK8 PIO_PA24_IDX

#define IMX_INT4 PIO_PA25_IDX
#define IMX_INT5 PIO_PA26_IDX
// Nand GPIO, used as normal GPIO
#define XO3_PRESENT PIO_PA29_IDX

// ---------- UART0 ----------
#define PIN_URXD PIO_PA9_IDX
#define PIN_UTXD PIO_PA10_IDX

// ---------- SPI ----------
#define PIN_ECSPI_MISO         (PIO_PA12_IDX)
#define PIN_ECSPI_MISO       (PIO_PERIPH_A | PIO_PULLUP)
#define PIN_ECSPI_MOSI         (PIO_PA13_IDX)
#define PIN_ECSPI_MOSI       (PIO_PERIPH_A | PIO_PULLUP)
#define PIN_ECSPI_SCLK        (PIO_PA14_IDX)
#define PIN_ECSPI_SCLK      (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_ECSPI_SS3 PIO_PA11_IDX
#define PIN_ECSPI_SS3 (PIO_PERIPH_A | PIO_DEFAULT)

// --------- ADC ---------
#define ADC_SOC ADC_CHANNEL_0
#define ADC_ARM ADC_CHANNEL_1
#define ADC_DDR ADC_CHANNEL_2
#define ADC_2V5 ADC_CHANNEL_3
#define ADC_1V0 ADC_CHANNEL_4
#define ADC_1V1 ADC_CHANNEL_5
#define ADC_1V2 ADC_CHANNEL_6
#define ADC_1V5 ADC_CHANNEL_7
#define ADC_3V3 ADC_CHANNEL_8
#define ADC_5V	ADC_CHANNEL_9

#define ADC_INT_TEMP	ADC_CHANNEL_15

// --------- EBI ---------
#define 


#endif // CONF_BOARD_H
