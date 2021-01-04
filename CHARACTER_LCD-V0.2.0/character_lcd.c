/*
------------------------------------------------------------------------------
~ File   : character_lcd.c
~ Author : Majid Derhambakhsh
~ Version: V0.2.0
~ Created: 12/11/2019 06:56:00 PM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    This file is for AVR/ARM microcontroller

~ Changes    :
                  Add     : include file section.
                  Improve : time shift value check before compile.
                  Improve : change library name to character_lcd
------------------------------------------------------------------------------
*/

#include "character_lcd.h"

/* --------------------- Struct ---------------------- */

ALCD_InitTypeDef Lcd_Config; /* Structure for config LCD */

/* ---------------------- Types ---------------------- */

LcdCommandFunc_TypeDef Lcd_SendCommand; /* Create Send Command function */
LcdPutCharFunc_TypeDef Lcd_PutChar; /* Create Put Char function */

/* -------------------- Functions -------------------- */

static void SendCommand_4Bit(ALCD_Command_TypeDef u_cmd) /* Function for send command in 4 bit mode */
{
	
	_Delay_Ms(1); /* Wait for transfer previous command */
	
	/* ----------- High nibble send ----------- */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RS_PIN)|(1 << _LCD_RW_PIN) , _GPIO_PIN_RESET); /* Reset RS/RW pin */
	
	_GPIO_WritePin(_LCD_DATA_PORT , ( _NIBBLE << _LCD_DATA_PIN) , _GPIO_PIN_RESET); /* Clear Data port */
	_GPIO_WritePin(_LCD_DATA_PORT , ( ( (u_cmd >> _HIGH_NIBBLE_SHIFT) & _NIBBLE) << _LCD_DATA_PIN) , _GPIO_PIN_SET); /* Send high nibble data to data port */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_RESET); /* Reset EN pin */
	
	/* ----------- Low nibble send ------------ */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RS_PIN)|(1 << _LCD_RW_PIN) , _GPIO_PIN_RESET); /* Reset RS/RW pin */
	
	_GPIO_WritePin(_LCD_DATA_PORT , ( _NIBBLE << _LCD_DATA_PIN) , _GPIO_PIN_RESET); /* Clear Data port */
	_GPIO_WritePin(_LCD_DATA_PORT , ( (u_cmd & _NIBBLE) << _LCD_DATA_PIN) , _GPIO_PIN_SET); /* Send low nibble data to data port */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_RESET); /* Reset EN pin */
	
	/* Function End */
}

static void SendCommand_8Bit(ALCD_Command_TypeDef u_cmd) /* Function for send command in 8 bit mode */
{
	
	_Delay_Ms(1); /* Wait for transfer previous command */
	
	/* ----------- Send user command ----------- */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RS_PIN)|(1 << _LCD_RW_PIN) , _GPIO_PIN_RESET); /* Reset RS/RW pin */
	
	_GPIO_WritePin(_LCD_DATA_PORT , ( _BYTE << _LCD_DATA_PIN) , _GPIO_PIN_RESET); /* Clear Data port */
	_GPIO_WritePin(_LCD_DATA_PORT , (u_cmd << _LCD_DATA_PIN) , _GPIO_PIN_SET); /* Send data to data port */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_RESET); /* Reset EN pin */
	
	/* Function End */
}

static void PutData_4Bit(char u_data) /* Function for send data in 4 bit mode */
{
	
	_Delay_Ms(1); /* Wait for transfer previous data */
	
	/* ----------- High nibble send ----------- */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RS_PIN) , _GPIO_PIN_SET); /* Set RS pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RW_PIN) , _GPIO_PIN_RESET); /* Reset RW pin */
	
	_GPIO_WritePin(_LCD_DATA_PORT , ( _NIBBLE << _LCD_DATA_PIN) , _GPIO_PIN_RESET); /* Clear Data port */
	_GPIO_WritePin(_LCD_DATA_PORT , ( ( (u_data >> _HIGH_NIBBLE_SHIFT) & _NIBBLE) << _LCD_DATA_PIN) , _GPIO_PIN_SET); /* Send high nibble data to data port */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_RESET); /* Reset EN pin */
	
	/* ----------- Low nibble send ------------ */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RS_PIN) , _GPIO_PIN_SET); /* Set RS pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RW_PIN) , _GPIO_PIN_RESET); /* Reset RW pin */
	
	_GPIO_WritePin(_LCD_DATA_PORT , ( _NIBBLE << _LCD_DATA_PIN) , _GPIO_PIN_RESET); /* Clear Data port */
	_GPIO_WritePin(_LCD_DATA_PORT , ( (u_data & _NIBBLE) << _LCD_DATA_PIN) , _GPIO_PIN_SET); /* Send low nibble data to data port */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_RESET); /* Reset EN pin */
	
	/* Function End */
}

static void PutData_8Bit(char u_data) /* Function for send data in 4 bit mode */
{
	_Delay_Ms(1); /* Wait for transfer previous data */
	
	/* ----------- Send user data ----------- */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RS_PIN) , _GPIO_PIN_SET); /* Set RS pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_RW_PIN) , _GPIO_PIN_RESET); /* Reset RW pin */
	
	_GPIO_WritePin(_LCD_DATA_PORT , ( _BYTE << _LCD_DATA_PIN) , _GPIO_PIN_RESET); /* Clear Data port */
	_GPIO_WritePin(_LCD_DATA_PORT , (u_data << _LCD_DATA_PIN) , _GPIO_PIN_SET); /* Send data to data port */
	
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(_LCD_CTRL_PORT , (1 << _LCD_EN_PIN) , _GPIO_PIN_RESET); /* Reset EN pin */
	
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void Lcd_Init(void) /* Function for initialize LCD */
{
		
	switch (Lcd_Config.Mode)
	{
		case _4BIT_INTERFACE: /* 4Bit mode selected */
		{
			
			Lcd_SendCommand = SendCommand_4Bit; /* Set Function */
			Lcd_PutChar = PutData_4Bit; /* Set Function */
			
			/* ------------------- Initialize LCD ------------------- */
			
			_Delay_Ms(_WAIT_FOR_POWER_ON); /* No data should be transferred to or from the display during this time */
			
			Lcd_SendCommand(_8BIT_INTERFACE); /* Function Set Command: (8-Bit interface) */
			_Delay_Ms(_WAIT_FOR_SET_MODE); /* No data should be transferred to or from the display during this time */
			
			Lcd_SendCommand(_8BIT_INTERFACE); /* Function Set Command: (8-Bit interface) */
			_Delay_Ms(1); /* No data should be transferred to or from the display during this time */
			
			Lcd_SendCommand( (_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT) | _4BIT_INTERFACE ); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
			
			Lcd_SendCommand( (_4BIT_INTERFACE << _HIGH_NIBBLE_SHIFT) | (Lcd_Config.NumberOfLine << _NBIT) | (Lcd_Config.Font << _FBIT) ); /* Function Set (Interface = 4 -bit, Set N and F for number of lines and character font) */
			
		 	Lcd_SendCommand(_DISPLAY_OFF); /* Display OFF */
			
			Lcd_SendCommand(_CLEAR_DISPLAY); /* Clear Display */
			
			Lcd_SendCommand(_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER); /* Entry Mode Set: */
			
			Lcd_SendCommand(_DISABLE_LCD_CURSOR); /* Display ON (Set C and B for cursor/Blink options.) */
		}
		break;
		
		case _8BIT_INTERFACE: /* 8Bit mode selected */
		{
			
			Lcd_SendCommand = SendCommand_8Bit; /* Set Function */
			Lcd_PutChar = PutData_4Bit; /* Set Function */
			
			/* ------------------- Initialize LCD ------------------- */
			
			_Delay_Ms(_WAIT_FOR_POWER_ON); /* No data should be transferred to or from the display during this time */
			
			Lcd_SendCommand(_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT); /* Function Set Command: (8-Bit interface) */
			_Delay_Ms(_WAIT_FOR_SET_MODE); /* No data should be transferred to or from the display during this time */
			
			Lcd_SendCommand(_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT); /* Function Set Command: (8-Bit interface) */
			_Delay_Ms(1); /* No data should be transferred to or from the display during this time */
			
			Lcd_SendCommand(_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
			
			Lcd_SendCommand( (_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT) | (Lcd_Config.NumberOfLine << _NBIT) | (Lcd_Config.Font << _FBIT) ); /* Function Set (Interface = 8 -bit, Set N and F for number of lines and character font) */
			
			Lcd_SendCommand(_DISPLAY_OFF); /* Display OFF */
			
			Lcd_SendCommand(_CLEAR_DISPLAY); /* Clear Display */
			
			Lcd_SendCommand(_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER); /* Entry Mode Set: */
			
			Lcd_SendCommand(_DISABLE_LCD_CURSOR); /* Display ON (Set C and B for cursor/Blink options.) */
		}
		break;
		
		default:
		/* Your code here */
		break;
	}
	
	/* Function End */
}

void Lcd_PutString(char *str) /* Function for send string to LCD */
{
	
	while (*str != '\0') /* Loop for send data */
	{
		
		Lcd_PutChar(*str); /* Send character */
		str++; /* Select next character */
		
	}
	
}

void Lcd_Clear(void) /* Function for clear LCD */
{
	
	Lcd_SendCommand(_CLEAR_DISPLAY); /* Send clear command */
	Lcd_SendCommand(_RETURN_HOME); /* Send return home command */
	
}

void Lcd_GotoXY(uint8_t column , uint8_t row) /* Function for set x & y address */
{
	
	switch (row)
	{
		case _R0: /* First row selected */
		{
			Lcd_SendCommand(_FIRST_ROW + column); /* Send DD RAM address */
		}
		break;
		case _R1: /* Second row selected */
		{
			Lcd_SendCommand(_SECOND_ROW + column); /* Send DD RAM address */
		}
		break;
		case _R2: /* Third row selected */
		{
			Lcd_SendCommand(_THIRD_ROW + column); /* Send DD RAM address */
		}
		break;
		case _R3: /* Fourth row selected */
		{
			Lcd_SendCommand(_FOURTH_ROW + column); /* Send DD RAM address */
		}
		break;
		
		default:
		/* Your code here */
		break;
	}
	
}

void Lcd_ShiftToLeft(uint8_t shift_number , uint16_t shift_time) /* Function for shift LCD */
{
	
	/* ---------------------- */
	
	#if ( shift_time == 0 )
	
	shift_time = 1;
	
	#endif
	
	if ( shift_time < _WAIT_FOR_SET_MODE )
	{
		shift_time = _WAIT_FOR_SET_MODE;
	}
	
	/* ---------------------- */
	
	for (; shift_number > 0 ; shift_number--) /* Loop for send command */
	{
		
		Lcd_SendCommand(_SHIFT_TO_LEFT); /* Send shift command */
		_Delay_Ms(shift_time); /* Wait for next shift */
	
	}
	
}

void Lcd_ShiftToRight(uint8_t shift_number , uint16_t shift_time) /* Function for shift LCD */
{
	
	/* ---------------------- */
	
	#if ( shift_time == 0 )
	
	shift_time = 1;
	
	#endif
	
	if ( shift_time < _WAIT_FOR_SET_MODE )
	{
		shift_time = _WAIT_FOR_SET_MODE;
	}
	
	/* ---------------------- */
	
	for (; shift_number > 0 ; shift_number--) /* Loop for send command */
	{
		
		Lcd_SendCommand(_SHIFT_TO_RIGHT); /* Send shift command */
		_Delay_Ms(shift_time); /* Wait for next shift */
	
	}
	
}

/* Program End */
