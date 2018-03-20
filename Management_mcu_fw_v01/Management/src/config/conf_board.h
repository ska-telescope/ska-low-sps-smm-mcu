/**
 * \file
 *
 * \brief Board configuration.
 *
 * Copyright (c) 2012-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/* Clock */



/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE

//! [tc_define_peripheral]
/* Use TC Peripheral 0. */
#define TC             TC0
#define TC_PERIPHERAL  0
//! [tc_define_peripheral]

//! [tc_define_ch1]
/* Configure TC0 channel 1 as waveform output. */
#define TC_CHANNEL_WAVEFORM 1
#define ID_TC_WAVEFORM      ID_TC1
#define PIN_TC_WAVEFORM     PIN_TC0_TIOA1
#define PIN_TC_WAVEFORM_MUX PIN_TC0_TIOA1_MUX
//! [tc_define_ch1]

//! [tc_define_ch2]
/* Configure TC0 channel 2 as capture input. */
#define TC_CHANNEL_CAPTURE 2
#define ID_TC_CAPTURE ID_TC2
#define PIN_TC_CAPTURE PIN_TC0_TIOA2
#define PIN_TC_CAPTURE_MUX PIN_TC0_TIOA2_MUX
//! [tc_define_ch2]

//! [tc_define_irq_handler]
/* Use TC2_Handler for TC capture interrupt. */
#define TC_Handler  TC2_Handler
#define TC_IRQn     TC2_IRQn
//! [tc_define_irq_handler]

// ---------- Fan Management ----------
#define PIN_RPM1 PIO_PA0_IDX
#define PIN_RMP2 PIO_PA1_IDX
#define PIN_FAN	 PIO_PA2_IDX

// ---------- I2C ----------
#define I2C1SDA PIO_PA3_IDX
#define I2C1SDA (PIO_PERIPH_A | PIO_DEFAULT)
#define I2C1SCL PIO_PA4_IDX
#define I2C1SCL (PIO_PERIPH_A | PIO_DEFAULT)

// ---------- GPIO ----------
#define XO3_REFRESH PIO_PA6_IDX

#define PIN_LEDK7 PIO_PA23_IDX
#define PIN_LEDK8 PIO_PA24_IDX
#define PIN_LEDTB PIO_PC23_IDX

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
#define ADC_VCORE ADC_CHANNEL_6
#define ADC_1V5 ADC_CHANNEL_7
#define ADC_3V3 ADC_CHANNEL_8
#define ADC_5V	ADC_CHANNEL_9
#define ADC_3V	ADC_CHANNEL_11
#define ADC_2V8	ADC_CHANNEL_12

#define ADC_INT_TEMP	ADC_TEMPERATURE_SENSOR


#endif /* CONF_BOARD_H_INCLUDED */
