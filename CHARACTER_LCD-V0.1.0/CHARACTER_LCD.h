/*
------------------------------------------------------------------------------
~ File   : CHARACTER_LCD.h
~ Author : Majid Derhambakhsh
~ Version: V0.1.0
~ Created: 2/17/2019 01:43:00 PM
~ Brief  :
~ Support: Majid.do16@gmail.com
------------------------------------------------------------------------------
~ Description:

~ Attention  :    This file is for AVR/ARM microcontroller

~ Changes    :
				  Add     : Disable 'unused function' section.
				  Improve : Speed.
------------------------------------------------------------------------------
*/

#ifndef __CHARACTER_LCD_H_
#define __CHARACTER_LCD_H_

/* ------------------------------------- Includes ------------------------------------- */

#include "CHARACTER_LCD_CONFIG.h" /* Import config file */
#include <stdint.h> /* Import standard int */

/* ------------------------------------------------------------------ */

#ifdef __CODEVISIONAVR__  /* Check compiler */

#pragma warn_unref_func- /* Disable 'unused function' warning */

#include "GPIO_UNIT/gpio_unit.h"        /* Import AVR IO library */
#include <delay.h>       /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(__GNUC__)  /* Check compiler */

#pragma GCC diagnostic ignored "-Wunused-function" /* Disable 'unused function' warning */

#include "GPIO_UNIT/gpio_unit.h"        /* Import HAL library */
#include <util/delay.h>  /* Import delay library */

/* ------------------------------------------------------------------ */

#elif defined(USE_HAL_DRIVER)  /* Check driver */

	/* --------------- Check Mainstream series --------------- */
	
	#ifdef STM32F0
		#include "stm32f0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F1)
		#include "stm32f1xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F2)
		#include "stm32f2xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F3)
		#include "stm32f3xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F4)
		#include "stm32f4xx_hal.h"       /* Import HAL library */
	#elif defined(STM32F7)
		#include "stm32f7xx_hal.h"       /* Import HAL library */
	#elif defined(STM32G0)
		#include "stm32g0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32G4)
		#include "stm32g4xx_hal.h"       /* Import HAL library */
	
	/* ------------ Check High Performance series ------------ */
	
	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"       /* Import HAL library */
	
	/* ------------ Check Ultra low power series ------------- */
	/* ------------------------------------------------------- */
	#elif defined(STM32L0)
		#include "stm32l0xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L1)
		#include "stm32l1xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L5)
		#include "stm32l5xx_hal.h"       /* Import HAL library */
	#elif defined(STM32L4)
		#include "stm32l4xx_hal.h"       /* Import HAL library */
	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"       /* Import HAL library */
	#else
	#endif /* STM32F1 */
	
	/* ------------------------------------------------------- */
	
	#if defined ( __ICCARM__ ) /* ICCARM Compiler */
	
		#pragma diag_suppress=Pe177   /* Disable 'unused function' warning */
		
	#elif defined   (  __GNUC__  ) /* GNU Compiler */
	
		#pragma diag_suppress 177     /* Disable 'unused function' warning */
		
	#endif /* __ICCARM__ */

/* ------------------------------------------------------------------ */

#else                     /* Compiler not found */

#error Chip or GPIO Library not supported  /* Send error */

#endif /* __CODEVISIONAVR__ */

/* ------------------------------------------------------------------ */

/* -------------------------------------- Define -------------------------------------- */

/* ----------- DD RAM ADDRESS ----------- */

#define _FIRST_ROW  0x80 /* First line address */
#define _SECOND_ROW 0xC0 /* Second line address */
#define _THIRD_ROW  0x94 /* Third line address */
#define _FOURTH_ROW 0xD4 /* Fourth line address */

/* -------------------------------------- */

#define _R0   0 /* Row 0 selector */
#define _R1   1 /* Row 1 selector */
#define _R2   2 /* Row 2 selector */
#define _R3   3 /* Row 3 selector */
#define _NBIT 3 /* Select number of line bit in register */
#define _FBIT 2 /* Select font bit in register */
#define _WAIT_FOR_POWER_ON 15 /* Delay time for power on */
#define _WAIT_FOR_SET_MODE 5 /* Delay time for set */

/* --------------- Public --------------- */

#define _NIBBLE 0xF  /* Nibble value */
#define _BYTE   0xFF /* Byte value */
#define _HIGH_NIBBLE_SHIFT 4 /* Select high byte */

/*----------------------------------------------------------*/

#ifdef __CODEVISIONAVR__  /* Check compiler */

#define _Delay_Ms(t)                                    delay_ms(t) /* Select delay function */
#define _GPIO_WritePin(gpiox , gpio_pin , pin_state)    GPIO_WritePin((gpiox) , (uint8_t)(gpio_pin) , pin_state) /* Select GPIO function */

/*----------------------------------------------------------*/

#elif defined(__GNUC__)   /* Check compiler */

#define _Delay_Ms(t)                                    _delay_ms(t) /* Select delay function */
#define _GPIO_WritePin(gpiox , gpio_pin , pin_state)    GPIO_WritePin((gpiox) , (uint8_t)(gpio_pin) , pin_state) /* Select GPIO function */

/*----------------------------------------------------------*/

#elif defined(USE_HAL_DRIVER)   /* Check compiler */

#define _Delay_Ms(t)                                    HAL_Delay(t) /* Select delay function */
#define _GPIO_WritePin(gpiox , gpio_pin , pin_state)    HAL_GPIO_WritePin((gpiox) , (uint32_t)(gpio_pin) , (pin_state)) /* Select GPIO function */
#define _GPIO_PIN_RESET                                 GPIO_PIN_RESET /* Select GPIO reset instruction */
#define _GPIO_PIN_SET                                   GPIO_PIN_SET /* Select GPIO set instruction */

#endif /* __CODEVISIONAVR__ */

/*----------------------------------------------------------*/

#ifndef ENUM_U8_T
	#define ENUM_U8_T(ENUM_NAME)   Enum_##ENUM_NAME; typedef uint8_t ENUM_NAME /* Set enum size */
#endif

/* --------------------------------------- Enum --------------------------------------- */

typedef enum /* Enum for command value */
{
	
	_CLEAR_DISPLAY                               = 0x01, /* Clear display command */
	_RETURN_HOME                                 = 0x02, /* Return home command */
	_SHIFT_CURSOR_TO_LEFT_AFTER_WRITE_CHARACTER  = 0x04, /* Shift cursor mode command */
	_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER = 0x06, /* Shift cursor mode command */
	_SHIFT_CURSOR_TO_LEFT                        = 0x10, /* Shift cursor command */
	_SHIFT_CURSOR_TO_RIGHT                       = 0x14, /* Shift cursor command */
	_SHIFT_TO_LEFT                               = 0x18, /* Shift LCD command */
	_SHIFT_TO_RIGHT                              = 0x1C, /* Shift LCD command */
	_DISPLAY_OFF                                 = 0x08, /* Display off command */
	_DISABLE_LCD_CURSOR                          = 0x0C, /* Disable cursor command */
	_BLINK_LCD_CURSOR                            = 0x0D, /* Blink cursor command */
	_FIXED_LCD_CURSOR                            = 0x0E  /* Fixed cursor command */
	
}ENUM_U8_T(ALCD_Command_TypeDef);

typedef enum /* Enum for Interface mode value */
{
	
	_8BIT_INTERFACE = 0x3, /* 8Bit interface selector */
	_4BIT_INTERFACE = 0x2  /* 4Bit interface selector */
	
}ENUM_U8_T(ALCD_Interface_TypeDef);

typedef enum /* Enum for line enable value */
{
	
	_1LINE_DISPLAY = 0, /* number of lines */
	_2LINE_DISPLAY = 1  /* number of lines */
	
}ENUM_U8_T(ALCD_Lines_TypeDef);

typedef enum /* Enum for LCD font value */
{
	
	_FONT_5X10 = 1, /* character font */
	_FONT_5X7  = 0  /* character font */
	
}ENUM_U8_T(ALCD_Font_TypeDef);

/* -------------------------------------- Struct -------------------------------------- */

typedef struct /* type Structure for config LCD */
{
	
	ALCD_Interface_TypeDef  Mode; /* Variable for set LCD mode */
	ALCD_Font_TypeDef       Font; /* Variable for set LCD font */
	ALCD_Lines_TypeDef      NumberOfLine; /* Variable for set LCD number of line */
	
}ALCD_InitTypeDef;

extern ALCD_InitTypeDef Lcd_Config; /* Structure for config LCD */

/* ------------------------------------- Types ---------------------------------------- */

typedef void (*LcdCommandFunc_TypeDef)(ALCD_Command_TypeDef cmd); /* Command Function type */
typedef void (*LcdPutCharFunc_TypeDef)(char character); /* Put Char Function type */

/* ----------------------------------- Prototypes ------------------------------------- */

extern LcdCommandFunc_TypeDef Lcd_SendCommand; /* Function for send command */

extern LcdPutCharFunc_TypeDef Lcd_PutChar;  /* Function for send character to LCD */

void Lcd_Init(void); /* Function for initialize LCD */

void Lcd_PutString(char *str); /* Function for send string to LCD */

void Lcd_Clear(void); /* Function for clear LCD */

void Lcd_GotoXY(uint8_t column , uint8_t row); /* Function for set x & y address */

void Lcd_ShiftToLeft(uint8_t shift_number , uint16_t shift_time); /* Function for shift LCD */

void Lcd_ShiftToRight(uint8_t shift_number , uint16_t shift_time); /* Function for shift LCD */

/* ------------------------------------------------------------------------------------ */

#endif /* __CHARACTER_LCD_H_ */

/* Program End */
