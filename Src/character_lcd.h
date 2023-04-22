/*
------------------------------------------------------------------------------
~ File   : character_lcd.h
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

#ifndef __CHARACTER_LCD_H_
#define __CHARACTER_LCD_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "character_lcd_conf.h" /* Import config file */
#include <stdint.h> /* Import standard int */

/* ------------------------------------------------------------------ */
#ifdef _CodeVISIONAVR__  /* Check compiler */

#pragma warn_unref_func- /* Disable 'unused function' warning */

#ifndef __GPIO_UNIT_H_
	#include "GPIO_UNIT/gpio_unit.h"        /* Import AVR IO library */
#endif /* __GPIO_UNIT_H_ */

#include <delay.h>       /* Import delay library */

/* ------------------------------------------------------------------ */
#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */

#pragma GCC diagnostic ignored "-Wunused-function" /* Disable 'unused function' warning */

#ifndef __GPIO_UNIT_H_
	#include "GPIO_UNIT/gpio_unit.h"        /* Import AVR IO library */
#endif /* __GPIO_UNIT_H_ */

#include <avr/pgmspace.h>
#include <util/delay.h>  /* Import delay library */

/* ------------------------------------------------------------------ */
#elif defined(USE_HAL_DRIVER)  /* Check driver */

	#if LCD_USE_FREE_RTOS == 1
		#include "cmsis_os.h"
	#endif /* _LCD_USE_FREE_RTOS */
	
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

#endif /* _CodeVISIONAVR__ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ------------------------------ LCD ------------------------------ */
/* ................ DD RAM ADDRESS ................ */
#define LCD_ROW_0      0 /* Row 0 selector */
#define LCD_ROW_1      1 /* Row 1 selector */
#define LCD_ROW_2      2 /* Row 2 selector */
#define LCD_ROW_3      3 /* Row 3 selector */

#define LCD_ROW_0_ADD  0x80 /* Row 0 Address */
#define LCD_ROW_1_ADD  0xC0 /* Row 1 Address */
#define LCD_ROW_2_ADD  0x94 /* Row 2 Address */
#define LCD_ROW_3_ADD  0xD4 /* Row 3 Address */

/* ................. Register bits ................ */
#define LCD_BIT_4      4
#define LCD_BIT_LINES  3 /* Number of line bit */
#define LCD_BIT_FONT   2 /* Font bit */

/* .................... Timing .................... */
#define LCD_POWER_ON_TIME_MS 15 /* Power On Time */
#define LCD_SET_MODE_TIME_MS 5 /* Set Time */

/* .................... Config .................... */
/* LCD Mode */
#define LCD_MODE_4         0x02
#define LCD_MODE_8         0x03

/* Number of lines */
#define LCD_DISPLAY_LINE_1 0
#define LCD_DISPLAY_LINE_2 1

/* Font size */
#define LCD_FONT_5X7       0
#define LCD_FONT_5X10      1

/* .................... Common .................... */

/* ................... Macro's .................... */
#define LCD_PutChar(ch)  LCD_Transmit((ch), LCD_TRANSMIT_CHAR)
#define LCD_PutCMD(ch)   LCD_Transmit((ch), LCD_TRANSMIT_CMD)

#define lcd_init()       LCD_Init()
#define lcd_init2(plcd)  LCD_Init2((plcd))

#define LCD_Putch(ch)    LCD_PutChar((ch))
#define lcd_putch(ch)    LCD_PutChar((ch))

#define LCD_Puts(str)    LCD_PutString((str))
#define lcd_puts(str)    LCD_PutString((str))

#define LCD_Putsf(str)   LCD_PutStringF((str))
#define lcd_putsf(str)   LCD_PutStringF((str))

#define lcd_clear()      LCD_Clear()

#define lcd_gotoxy(x, y) LCD_GotoXY((x), (y))

/* ----------------------- Define by compiler ---------------------- */
#ifdef _CodeVISIONAVR__  /* Check compiler */

	#define _GPIO_WritePin(gpiox , gpio_pin , pin_state)  GPIO_WritePin(&(gpiox) , (uint8_t)(gpio_pin) , pin_state) /* Select GPIO function */
	
	#ifndef DELAY_MS
		#define DELAY_MS(t)                               delay_ms((t)) /* Change function */
	#endif /* DELAY_MS */
	
/*----------------------------------------------------------*/
#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)   /* Check compiler */

	#define _GPIO_WritePin(gpiox , gpio_pin , pin_state)  GPIO_WritePin(&(gpiox) , (uint8_t)(gpio_pin) , pin_state) /* Select GPIO function */
	
	#ifndef DELAY_MS
		#define DELAY_MS(t)                               _delay_ms((t)) /* Change function */
	#endif /* DELAY_MS */
	
/*----------------------------------------------------------*/
#elif defined(USE_HAL_DRIVER)   /* Check compiler */
	
	#define _GPIO_WritePin(gpiox , gpio_pin , pin_state)  HAL_GPIO_WritePin((gpiox) , (uint32_t)(gpio_pin) , (pin_state)) /* Select GPIO function */
	#define _GPIO_PIN_SET                                 GPIO_PIN_SET /* Select GPIO set instruction */
	#define _GPIO_PIN_RESET                               GPIO_PIN_RESET /* Select GPIO reset instruction */
	
	#if LCD_USE_FREE_RTOS == 1
		
		#ifndef DELAY_MS
			#define DELAY_MS(t)                           osDelay((t)) /* Change function */
		#endif /* DELAY_MS */
		
	#else
	
		#ifndef DELAY_MS
			#define DELAY_MS(t)                           HAL_Delay((t)) /* Change function */
		#endif /* DELAY_MS */
		
	#endif /* LCD_USE_FREE_RTOS */

#endif /* _CodeVISIONAVR__ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* -------------------------- LCD Commands ------------------------- */
typedef enum /* Enum for command value */
{
	
	LCD_CLEAR_DISPLAY                               = 0x01, /* Clear display command */
	LCD_RETURN_HOME                                 = 0x02, /* Return home command */
	LCD_SHIFT_CURSOR_TO_LEFT_AFTER_WRITE_CHARACTER  = 0x04, /* Shift cursor mode command */
	LCD_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER = 0x06, /* Shift cursor mode command */
	LCD_SHIFT_CURSOR_TO_LEFT                        = 0x10, /* Shift cursor command */
	LCD_SHIFT_CURSOR_TO_RIGHT                       = 0x14, /* Shift cursor command */
	LCD_SHIFT_TO_LEFT                               = 0x18, /* Shift LCD command */
	LCD_SHIFT_TO_RIGHT                              = 0x1C, /* Shift LCD command */
	LCD_DISPLAY_OFF                                 = 0x08, /* Display off command */
	LCD_DISPLAY_ON                                  = 0x0C, /* Display on command */
	LCD_DISABLE_LCD_CURSOR                          = 0x0C, /* Disable cursor command */
	LCD_BLINK_LCD_CURSOR                            = 0x0D, /* Blink cursor command */
	LCD_FIXED_LCD_CURSOR                            = 0x0E  /* Fixed cursor command */
	
}LCD_CMDTypeDef;

/* ----------------------- LCD Configuration ----------------------- */
// typedef enum /* Enum for Interface mode value */
// {
// 	
// 	LCD_MODE_8 = 0x03, /* 8 bit interface selector */
// 	LCD_MODE_4 = 0x02  /* 4 bit interface selector */
// 	
// }LCD_ModeTypeDef;
// 
// typedef enum /* Enum for line enable value */
// {
// 	
// 	LCD_DISPLAY_LINE_1 = 0,
// 	LCD_DISPLAY_LINE_2 = 1
// 	
// }LCD_LinesTypeDef;
// 
// typedef enum /* Enum for LCD font value */
// {
// 	
// 	LCD_FONT_5X10 = 1, /* character font */
// 	LCD_FONT_5X7  = 0  /* character font */
// 	
// }LCD_FontTypeDef;

typedef enum /* Enum for LCD font value */
{
	
	LCD_TRANSMIT_CMD  = 0,
	LCD_TRANSMIT_CHAR = 1
	
}LCD_TransmitTypeDef;

/* ---------------------------- Common ----------------------------- */
typedef struct /* LCD Type */
{
	
	uint8_t Mode; /* Variable for set LCD mode */
	uint8_t Font; /* Variable for set LCD font */
	uint8_t DisplayLines; /* Variable for set LCD number of line */
	
}LCD_TypeDef;

typedef void (*LCD_TransmitFuncTypeDef)(uint8_t Data, LCD_TransmitTypeDef TType); /* LCD Data transmit function type */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
extern LCD_TransmitFuncTypeDef LCD_Transmit;

/* ......................... Initialize ........................ */
/*
 * Function: LCD_Init
 * ------------------
 * Initialize LCD by 'character_lcd_conf.h' pin map and configuration parameters
 *
 * Param  : 
 *         -
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         LCD_Init();
 *         ...
 *
 */
void LCD_Init(void); /* Function for initialize LCD */

/*
 * Function: LCD_Init2
 * -------------------
 * Initialize LCD by 'character_lcd_conf.h' pin map and LCD_TypeDef configuration parameters
 *
 * Param  : 
 *         pLCD: Pointer to LCD module type
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         LCD_TypeDef LCD1;
 *         
 *         LCD1.Font = LCD_FONT_5X7;
 *         LCD1.Mode = LCD_MODE_8;
 *         LCD1.DisplayLines = LCD_DISPLAY_LINE_2;
 *
 *         LCD_Init2(&LCD1);
 *         ...
 *         
 */
void LCD_Init2(LCD_TypeDef *pLCD);

/*
 * Function: LCD_DefInit
 * ---------------------
 * Initialize LCD by 'character_lcd_conf.h' pin map and default configuration parameters
 *
 * Param  : 
 *         -
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         LCD_DefInit();
 *         ...
 *
 */
void LCD_DefInit(void);

/* ............................................................. */
/*
 * Function: LCD_PutString
 * -----------------------
 * Show text on LCD
 *
 * Param  : 
 *         str: Pointer to string to show text
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         char myText[7] = "World!";
 *
 *         LCD_PutString("Hello ");
 *         LCD_PutString(myText);
 *         ...
 *         
 */
void LCD_PutString(char *str);

/*
 * Function: LCD_PutStringF
 * ------------------------
 * Show text on LCD from MCU Flash Memory
 *
 * Param  : 
 *         str: Pointer to constant string to show text
 *         
 * Returns: 
 *         -
 *         
 * Example 1 (AVR): 
 *         const char PROGMEM myText[13] = "Hello World!";
 *
 *         LCD_PutStringF(myText);
 *         ...
 *         
 * Example 2 (AVR):
 *         LCD_PutStringF(PSTR("Hello World!"));
 *         ...
 *         
 * Example 3 (STM32):
 *         const char myText[13] = "Hello World!";
 *
 *         LCD_PutStringF(myText);
 *         ...
 *         
 */
void LCD_PutStringF(const char *str);

/*
 * Function: LCD_Clear
 * -------------------
 * Clear the LCD text
 *
 * Param  : 
 *         -
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         LCD_Clear();
 *         ...
 *
 */
void LCD_Clear(void);

/*
 * Function: LCD_GotoXY
 * --------------------
 * Go to the X and Y positions of the LCD
 *
 * Param  : 
 *         Column: X position of LCD
 *         Row   : Y position of LCD
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         LCD_GotoXY(5, 0); // Column 5 and Row 0
 *         LCD_PutString("Hello");
 *         LCD_GotoXY(0, 1); // Column 0 and Row 1
 *         LCD_PutString("LCD Library");
 *         ...
 *         
 */
void LCD_GotoXY(uint8_t Column, uint8_t Row);

/*
 * Function: LCD_Shift
 * -------------------
 * Shift LCD text to left or right
 *
 * Param  : 
 *         Shifts    : Number of Shift
 *         Dir       : Shift direction (LCD_SHIFT_TO_LEFT / LCD_SHIFT_TO_RIGHT)
 *         DelayTime : Delay time of each shift
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         LCD_GotoXY(0, 0);
 *         LCD_PutString("Hello");
 *         
 *         LCD_Shift(11, LCD_SHIFT_TO_RIGHT, 1000);
 *         LCD_Shift(11, LCD_SHIFT_TO_LEFT, 1000);
 *         ...
 *         
 */
void LCD_Shift(uint8_t Shifts, LCD_CMDTypeDef Dir, uint16_t DelayTime);

/*
 * Function: LCD_StoreInCGRAM
 * --------------------------
 * Save custom characters on LCD CGRAM memory
 *
 * Param  : 
 *         CharMap : Pointer to custom character pixels data
 *         Code    : Location of custom character in CGRAM
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         uint8_t Battery_CHAR[8] = {0x0E, 0x1F, 0x1D, 0x1D, 0x1D, 0x1D, 0x1F, 0x00};
 *         uint8_t Lock_CHAR[8] = {0x0E, 0x10, 0x10, 0x1B, 0x1B, 0x1B, 0x1F, 0x00};
 *         
 *         LCD_StoreInCGRAM(Battery_CHAR, 0);
 *         LCD_StoreInCGRAM(Lock_CHAR, 5);
 *         
 *         LCD_GotoXY(0, 0);
 *         LCD_PutChar(0); // Show battery character
 *         LCD_GotoXY(2, 0);
 *         LCD_PutChar(5); // Show lock character
 *         ...
 *         
 */
void LCD_StoreInCGRAM(uint8_t *CharMap, char Code);

/*
 * Function: LCD_StoreInCGRAMF
 * ---------------------------
 * Save custom characters on LCD CGRAM memory from MCU Flash Memory
 *
 * Param  : 
 *         CharMap : Pointer to constant custom character pixels data
 *         Code    : Location of custom character in CGRAM
 *         
 * Returns: 
 *         -
 *         
 * Example 1 (AVR):
 *         const uint8_t PROGMEM Battery_CHAR[8] = {0x0E, 0x1F, 0x1D, 0x1D, 0x1D, 0x1D, 0x1F, 0x00};
 *
 *         LCD_StoreInCGRAMF(Battery_CHAR, 0);
 *
 *         LCD_PutChar(0); // Show battery character
 *         ...
 *
 * Example 2 (STM32):
 *         const uint8_t Battery_CHAR[8] = {0x0E, 0x1F, 0x1D, 0x1D, 0x1D, 0x1D, 0x1F, 0x00};
 *
 *         LCD_StoreInCGRAMF(Battery_CHAR, 0);
 *
 *         LCD_PutChar(0); // Show battery character
 *         ...
 *         
 */
void LCD_StoreInCGRAMF(const uint8_t *CharMap, char Code);

/*
 * Function: LCD_PutCustomChar
 * ---------------------------
 * Save and show custom characters on LCD
 *
 * Param  : 
 *         CharMap : Pointer to custom character pixels data
 *         Code    : Location of custom character in CGRAM
 *         Column  : X position of LCD
 *         Row     : Y position of LCD
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         uint8_t Lock_CHAR[8] = {0x0E, 0x10, 0x10, 0x1B, 0x1B, 0x1B, 0x1F, 0x00};
 *         
 *         LCD_PutCustomChar(Lock_CHAR, 1, 0, 0); // Show char on X = Y = 0
 *         ...
 *         
 */
void LCD_PutCustomChar(uint8_t *CharMap, char Code, uint8_t Column, uint8_t Row);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __CHARACTER_LCD_H_ */
