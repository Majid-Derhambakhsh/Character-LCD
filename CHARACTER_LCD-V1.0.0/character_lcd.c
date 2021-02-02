/*
------------------------------------------------------------------------------
~ File   : character_lcd.c
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

#include "character_lcd.h"

/* --------------------- Struct ---------------------- */

ALCD_InitTypeDef LCD_Config; /* Structure for config LCD */

/* ---------------------- Types ---------------------- */

LCDCommandFunc_TypeDef LCD_SendCommand; /* Create Send Command function */
LCDPutCharFunc_TypeDef LCD_PutChar; /* Create Put Char function */

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
void LCD_4BitModeInit(void)
{
	
	LCD_SendCommand = SendCommand_4Bit; /* Set Function */
	LCD_PutChar = PutData_4Bit; /* Set Function */
	
	/* ------------------- Initialize LCD ------------------- */
	
	_Delay_Ms(_WAIT_FOR_POWER_ON); /* No data should be transferred to or from the display during this time */
	
	LCD_SendCommand(_8BIT_INTERFACE); /* Function Set Command: (8-Bit interface) */
	_Delay_Ms(_WAIT_FOR_SET_MODE); /* No data should be transferred to or from the display during this time */
	
	LCD_SendCommand(_8BIT_INTERFACE); /* Function Set Command: (8-Bit interface) */
	_Delay_Ms(1); /* No data should be transferred to or from the display during this time */
	
	LCD_SendCommand( (_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT) | _4BIT_INTERFACE ); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
	
	LCD_SendCommand( (_4BIT_INTERFACE << _HIGH_NIBBLE_SHIFT) | (LCD_Config.NumberOfLine << _NBIT) | (LCD_Config.Font << _FBIT) ); /* Function Set (Interface = 4 -bit, Set N and F for number of lines and character font) */
	
	LCD_SendCommand(_DISPLAY_OFF); /* Display OFF */
	
	LCD_SendCommand(_CLEAR_DISPLAY); /* Clear Display */
	
	LCD_SendCommand(_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER); /* Entry Mode Set: */
	
	LCD_SendCommand(_DISABLE_LCD_CURSOR); /* Display ON (Set C and B for cursor/Blink options.) */
	
}
void LCD_8BitModeInit(void)
{
	
	LCD_SendCommand = SendCommand_8Bit; /* Set Function */
	LCD_PutChar = PutData_4Bit; /* Set Function */
	
	/* ------------------- Initialize LCD ------------------- */
	
	_Delay_Ms(_WAIT_FOR_POWER_ON); /* No data should be transferred to or from the display during this time */
	
	LCD_SendCommand(_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT); /* Function Set Command: (8-Bit interface) */
	_Delay_Ms(_WAIT_FOR_SET_MODE); /* No data should be transferred to or from the display during this time */
	
	LCD_SendCommand(_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT); /* Function Set Command: (8-Bit interface) */
	_Delay_Ms(1); /* No data should be transferred to or from the display during this time */
	
	LCD_SendCommand(_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
	
	LCD_SendCommand( (_8BIT_INTERFACE << _HIGH_NIBBLE_SHIFT) | (LCD_Config.NumberOfLine << _NBIT) | (LCD_Config.Font << _FBIT) ); /* Function Set (Interface = 8 -bit, Set N and F for number of lines and character font) */
	
	LCD_SendCommand(_DISPLAY_OFF); /* Display OFF */
	
	LCD_SendCommand(_CLEAR_DISPLAY); /* Clear Display */
	
	LCD_SendCommand(_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER); /* Entry Mode Set: */
	
	LCD_SendCommand(_DISABLE_LCD_CURSOR); /* Display ON (Set C and B for cursor/Blink options.) */
	
}

void LCD_Init(void) /* Function for initialize LCD */
{
		
	switch (LCD_Config.Mode)
	{
		case _4BIT_INTERFACE: /* 4Bit mode selected */
		{
			
			LCD_4BitModeInit();
		}
		break;
		
		case _8BIT_INTERFACE: /* 8Bit mode selected */
		{
			
			LCD_8BitModeInit();
		}
		break;
		
		default:
		/* Your code here */
		break;
	}
	
	/* Function End */
}

void LCD_DefInit(void) /* Function for initialize LCD */
{
	
	LCD_Config.Font = _FONT_5X10;
	LCD_Config.Mode = _4BIT_INTERFACE;
	LCD_Config.NumberOfLine = _2LINE_DISPLAY;
	
	LCD_4BitModeInit();
	
}

void LCD_PutString(char *str) /* Function for send string to LCD */
{
	
	while (*str != '\0') /* Loop for send data */
	{
		
		LCD_PutChar(*str); /* Send character */
		str++; /* Select next character */
		
	}
	
}

void LCD_Clear(void) /* Function for clear LCD */
{
	
	LCD_SendCommand(_CLEAR_DISPLAY); /* Send clear command */
	LCD_SendCommand(_RETURN_HOME); /* Send return home command */
	
}

void LCD_GotoXY(uint8_t column , uint8_t row) /* Function for set x & y address */
{
	
	switch (row)
	{
		case _R0: /* First row selected */
		{
			LCD_SendCommand(_FIRST_ROW + column); /* Send DD RAM address */
		}
		break;
		case _R1: /* Second row selected */
		{
			LCD_SendCommand(_SECOND_ROW + column); /* Send DD RAM address */
		}
		break;
		case _R2: /* Third row selected */
		{
			LCD_SendCommand(_THIRD_ROW + column); /* Send DD RAM address */
		}
		break;
		case _R3: /* Fourth row selected */
		{
			LCD_SendCommand(_FOURTH_ROW + column); /* Send DD RAM address */
		}
		break;
		
		default:
		/* Your code here */
		break;
	}
	
}

void LCD_ShiftToLeft(uint8_t shift_number , uint16_t shift_time) /* Function for shift LCD */
{
	
	/* ---------------------- */
	if ( shift_time < _WAIT_FOR_SET_MODE )
	{
		shift_time = _WAIT_FOR_SET_MODE;
	}
	
	/* ---------------------- */
	
	for (; shift_number > 0 ; shift_number--) /* Loop for send command */
	{
		
		LCD_SendCommand(_SHIFT_TO_LEFT); /* Send shift command */
		_Delay_Ms(shift_time); /* Wait for next shift */
	
	}
	
}

void LCD_ShiftToRight(uint8_t shift_number , uint16_t shift_time) /* Function for shift LCD */
{
	
	/* ---------------------- */
	if ( shift_time < _WAIT_FOR_SET_MODE )
	{
		shift_time = _WAIT_FOR_SET_MODE;
	}
	
	/* ---------------------- */
	
	for (; shift_number > 0 ; shift_number--) /* Loop for send command */
	{
		
		LCD_SendCommand(_SHIFT_TO_RIGHT); /* Send shift command */
		_Delay_Ms(shift_time); /* Wait for next shift */
	
	}
	
}

/* Program End */
