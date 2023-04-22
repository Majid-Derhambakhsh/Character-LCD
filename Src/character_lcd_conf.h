/*
------------------------------------------------------------------------------
~ File   : character_lcd_conf.h
~ Author : Majid Derhambakhsh
~ Version: V2.0.0
~ Created: 12/25/2022 00:00:00 AM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    This file is for AVR/ARM MCU

~ Changes    :
------------------------------------------------------------------------------
*/

#ifndef __CHARACTER_LCD_CONFIG_H_
#define __CHARACTER_LCD_CONFIG_H_

/* ~~~~~~~~~~~~~~ Required Headers ~~~~~~~~~~~~~ */
/* Driver-library for AVR */
#include "GPIO_UNIT/gpio_unit.h"

/* Driver-library for STM32 */
//#include "main.h"

/* ~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~ */
/* ~~~~~ Configurations ~~~~~ */
#define LCD_MODE   LCD_MODE_4
#define LCD_FONT   LCD_FONT_5X7
#define LCD_LINES  LCD_DISPLAY_LINE_2

/*
	Guide :
			LCD_MODE  : Interface mode (LCD_MODE_4 / LCD_MODE_8)
			LCD_FONT  : Font size (LCD_FONT_5X7 / LCD_FONT_5X10)
			LCD_LINES : Interface mode (LCD_DISPLAY_LINE_1 / LCD_DISPLAY_LINE_2)
	
	Example:			
			#define LCD_MODE   LCD_MODE_4
			#define LCD_FONT   LCD_FONT_5X7
			#define LCD_LINES  LCD_DISPLAY_LINE_2
*/

/* ~~~~~~ Control Pins ~~~~~~ */
#define LCD_RS_GPIO PORTB
#define LCD_RS_PIN  3

#define LCD_RW_GPIO PORTC
#define LCD_RW_PIN  4

#define LCD_EN_GPIO PORTB
#define LCD_EN_PIN  0

/*
	Guide :
			LCD_RS_GPIO : Specifies the LCD RS port to control
			LCD_RS_PIN  : Specifies the LCD RS pin to control
			
			LCD_RW_GPIO : Specifies the LCD RW port to control
			LCD_RW_PIN  : Specifies the LCD RW pin to control
						
			LCD_EN_GPIO : Specifies the LCD EN port to control
			LCD_EN_PIN  : Specifies the LCD EN pin to control
	
	Example:
			AVR:
				#define LCD_RS_GPIO PORTB
				#define LCD_RS_PIN  3

				#define LCD_RW_GPIO PORTD
				#define LCD_RW_PIN  0

				#define LCD_EN_GPIO PORTB
				#define LCD_EN_PIN  0
				
			ARM:
				#define LCD_RS_GPIO GPIOB
				#define LCD_RS_PIN  3

				#define LCD_RW_GPIO GPIOD
				#define LCD_RW_PIN  0

				#define LCD_EN_GPIO GPIOB
				#define LCD_EN_PIN  0
*/

/* ~~~~~~~~ Data Pins ~~~~~~~ */
#define LCD_D0_GPIO PORTB
#define LCD_D0_PIN  1

#define LCD_D1_GPIO PORTB
#define LCD_D1_PIN  2

#define LCD_D2_GPIO PORTD
#define LCD_D2_PIN  5

#define LCD_D3_GPIO PORTC
#define LCD_D3_PIN  0

#define LCD_D4_GPIO PORTD
#define LCD_D4_PIN  1

#define LCD_D5_GPIO PORTC
#define LCD_D5_PIN  1

#define LCD_D6_GPIO PORTD
#define LCD_D6_PIN  2

#define LCD_D7_GPIO PORTD
#define LCD_D7_PIN  3

/*
	Guide :
			LCD_D0_GPIO ~ LCD_D7_GPIO : Specifies the LCD data ports
			LCD_D0_PIN ~ LCD_D7_PIN   : Specifies the LCD data pins
	
	Example:
			AVR:
				#define LCD_Dx_GPIO PORTB
				#define LCD_Dx_PIN  1
				
			ARM:
				#define LCD_Dx_GPIO GPIOB
				#define LCD_Dx_PIN  1
*/

/* ~~~~~~~~ Optimize ~~~~~~~~ */
/* If you use the same port for data pins, uncomment this line */
//#define LCD_DATA_PORT_OPTIMIZE

/* ~~~~~~~~ STM32 MCU ~~~~~~~ */
#define STM32F1

/*
	Guide   :
				#define STM32Xx : STM32 Family.
	Example :
				#define STM32F1
				#define STM32H7
				#define STM32L0
*/

/* ~~~~~~~~~ SYSTEM ~~~~~~~~~ */
#define LCD_USE_FREE_RTOS   0

/*
	0 For normal mode
	1 For RTOS mode
*/

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __CHARACTER_LCD_CONFIG_H_ */
