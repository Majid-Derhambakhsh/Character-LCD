/*
------------------------------------------------------------------------------
~ File   : character_lcd_conf.h
~ Author : Majid Derhambakhsh
~ Version: V1.0.0
~ Created: 01/08/2021 11:00:00 AM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    This file is for AVR/ARM microcontroller

~ Changes    :
                  Add     : Support RTOS mode
                  Add     : void Lcd_DefInit(void) function
                  Modify  : Change Lcd_xxx to LCD_xxx in functions and configuration
------------------------------------------------------------------------------
*/

#ifndef __CHARACTER_LCD_CONFIG_H_
#define __CHARACTER_LCD_CONFIG_H_

/* ~~~~~~~~~~~~~~~ Include files ~~~~~~~~~~~~~~~ */
//#include "GPIO_UNIT/gpio_unit.h"

/* ~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~ Data PORT ~~~~~~ */
#define _LCD_CTRL_PORT PORTA
#define _LCD_DATA_PORT PORTA

/* ~~~~~~ Data PIN ~~~~~~~ */
#define _LCD_DATA_PIN  3
#define _LCD_RS_PIN    0
#define _LCD_RW_PIN    1
#define _LCD_EN_PIN    2

/*
	Guide :
	       _LCD_CTRL_PORT ~ _LCD_DATA_PORT : LCD Control & DATA PORT
	                                         This parameter can be PORTx in AVR Or GPIOx in ARM.
	       
	       _LCD_DATA_PIN                   : Specifies the LCD First data pin to control ~ (DB0 in 8Bit Mode Or DB4 in 4 Bit Mode).
	       _LCD_RS_PIN                     : Specifies the LCD RS pin to control.
	       _LCD_RW_PIN                     : Specifies the LCD RW pin to control.
	       _LCD_EN_PIN                     : Specifies the LCD EN pin to control.
	
	Example:
			AVR:
				#define _LCD_CTRL_PORT PORTB
				#define _LCD_DATA_PORT PORTA

				#define _LCD_D0_PIN 0
				#define _LCD_RS_PIN 5
				#define _LCD_RW_PIN 6
				#define _LCD_EN_PIN 7

			ARM:
				#define _LCD_CTRL_PORT GPIOB
				#define _LCD_DATA_PORT GPIOA

				#define _LCD_D0 0
				#define _LCD_RS 5
				#define _LCD_RW 6
				#define _LCD_EN 7
	
*/

/* ~~~~~~ STM32 MCU ~~~~~~ */
#define STM32F1

/*
	Guide   :
			  #define STM32Xx : STM32 Family.
	Example :
			  #define STM32F1
			  #define STM32H7
			  #define STM32L0
*/

/* ~~~~~~~ SYSTEM ~~~~~~~~ */
#define _LCD_USE_FREE_RTOS   0

/*
	0 For normal mode
	1 for RTOS mode
*/

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __CHARACTER_LCD_CONFIG_H_ */
