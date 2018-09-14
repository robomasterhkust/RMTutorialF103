/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the STM32F103C8T6 Module often described as "Arduino"-like
 * on eBay, typically marked "www.vcc-gnd.com".
 */

/*
 * Board identifier.
 */
#define BOARD_MINIMAL_STM32_F103
#define BOARD_NAME "STM32F103 Forest V1"

/*
 * Board frequencies.
 */
#define STM32_LSECLK 0
#define STM32_HSECLK 8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 *
 * Only xB (128KB Flash) is defined, but it's identical to the
 * x8 version (64KB Flash) except for the Flash region size in the
 * linker script. For x8 parts use xB here and change to the x8 linker
 * script in the project Makefile.
 */
#define STM32F103xB

/*
 * IO pins assignments
 *
 * numbering is sorted by onboard/connectors, as from the schematics in
 * http://www.vcc-gnd.com/read.php?tid=369
 */

/* on-board */

#define LED_ON_STATE 0
#define BUTTON_PRESSED_STATE 0

#define GPIOA_LED 8U
#define GPIOA_BUTTON 15U

#define GPIOA_CAN_RX 11U
#define GPIOA_CAN_TX 12U

#define GPIOA_USART1_TX 9U
#define GPIOA_USART1_RX 10U

#define GPIOA_SERIAL_USB_RX GPIOA_USART1_RX
#define GPIOA_SERIAL_USB_TX GPIOA_USART1_TX

#define GPIOA_USART2_TX 2U
#define GPIOA_USART2_RX 3U

#define GPIOB_I2C2_SCL 10U
#define GPIOB_I2C2_SDA 11U

#define GPIOB_MPU6050_INT 3U
#define GPIOB_MPU6050_SCL GPIOB_I2C2_SCL
#define GPIOB_MPU6050_SDA GPIOB_I2C2_SDA

//only HSE which uses the following pin, no LSE
#define GPIOC_OSC_IN 14U
#define GPIOC_OSC_OUT 15U

#define LINE_LED PAL_LINE(GPIOA, GPIOA_LED)
#define LINE_BUTTON PAL_LINE(GPIOA, GPIOA_BUTTON)

/*
following refer to stm32f1 reference manual section 9.1
*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits in ACR have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input. (FLOATING)
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * Everything input with pull-up except:
 * 5 - (GPIOA_LED 8)
 * 4 - (GPIOA_BUTTON 15) ##the board has hardware debouncing and pull-up resistor installed to the button
 * 4 - (GPIOA_CAN_RX 11)
 * B - (GPIOA_CAN_TX 12)
 * B - (GPIOA_USART1_TX 9)
 * B - (GPIOA_USART2_TX 2)
 */
#define VAL_GPIOACRL 0x88888B88 /*  PA7...PA0 */
#define VAL_GPIOACRH 0x488B48B5 /* PA15...PA8 */
#define VAL_GPIOAODR 0xFFFFFFFF

/*
 * Port B setup.
 * Everything input with pull-up except:
 * E - (GPIOB_I2C2_SCL 10)
 * E - (GPIOB_I2C2_SDA 11)
 * 4 - (GPIOB_MPU6050_INT 3)
 */
#define VAL_GPIOBCRL 0x88888888 /*  PB7...PB0 */
#define VAL_GPIOBCRH 0x8888FF88 /* PB15...PB8 */
#define VAL_GPIOBODR 0xFFFFFFFF

/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC13 - Digital output (LED).
 */
#define VAL_GPIOCCRL 0x88888888 /*  PC7...PC0 */
#define VAL_GPIOCCRH 0x88888888 /* PC15...PC8 */
#define VAL_GPIOCODR 0xFFFFFFFF

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input (XTAL).
 * PD1  - Normal input (XTAL).
 */
#define VAL_GPIODCRL 0x88888888 /*  PD7...PD0 */
#define VAL_GPIODCRH 0x88888888 /* PD15...PD8 */
#define VAL_GPIODODR 0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOECRL 0x88888888 /*  PE7...PE0 */
#define VAL_GPIOECRH 0x88888888 /* PE15...PE8 */
#define VAL_GPIOEODR 0xFFFFFFFF

// /*
//  * USB bus activation macro, required by the USB driver.
//  */
// #define usb_lld_connect_bus(usbp)	/* always connected */

// /*
//  * USB bus de-activation macro, required by the USB driver.
//  */
// #define usb_lld_disconnect_bus(usbp)	/* always connected */

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C"
{
#endif
    void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
