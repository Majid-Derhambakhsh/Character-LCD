/*
------------------------------------------------------------------------------
~ File   : character_lcd.c
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

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "character_lcd.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ G Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ G Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ G Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ G Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
LCD_TransmitFuncTypeDef LCD_Transmit;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void LCD_Transmit_4Bit(uint8_t CMD, LCD_TransmitTypeDef TType)
{
	
	#if LCD_MODE == LCD_MODE_4
	
	DELAY_MS(1); /* Wait for transfer previous command */
	
	/* ----------- High Nibble Update ----------- */
	_GPIO_WritePin(LCD_RS_GPIO, (1 << LCD_RS_PIN), TType); /* Set/Reset RS pin */
	_GPIO_WritePin(LCD_RW_GPIO, (1 << LCD_RW_PIN), _GPIO_PIN_RESET); /* Reset RW pin */
	
	#ifdef LCD_DATA_PORT_OPTIMIZE
	
	/* Reset Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, (1 << LCD_D7_PIN)|(1 << LCD_D6_PIN)|(1 << LCD_D5_PIN)|(1 << LCD_D4_PIN), _GPIO_PIN_RESET); /* Reset D4 pin */
	
	/* Update Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, (((CMD >> 7) & 1U) << LCD_D7_PIN)|(((CMD >> 6) & 1U) << LCD_D6_PIN)|(((CMD >> 5) & 1U) << LCD_D5_PIN)|(((CMD >> 4) & 1U) << LCD_D4_PIN), _GPIO_PIN_SET); /* Set D4 pin */
	
	#else
	
	/* Reset Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, (1 << LCD_D4_PIN), _GPIO_PIN_RESET); /* Reset D4 pin */
	_GPIO_WritePin(LCD_D5_GPIO, (1 << LCD_D5_PIN), _GPIO_PIN_RESET); /* Reset D5 pin */
	_GPIO_WritePin(LCD_D6_GPIO, (1 << LCD_D6_PIN), _GPIO_PIN_RESET); /* Reset D6 pin */
	_GPIO_WritePin(LCD_D7_GPIO, (1 << LCD_D7_PIN), _GPIO_PIN_RESET); /* Reset D7 pin */
	
	/* Update Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, (((CMD >> 4) & 1U) << LCD_D4_PIN), _GPIO_PIN_SET); /* Set D4 pin */
	_GPIO_WritePin(LCD_D5_GPIO, (((CMD >> 5) & 1U) << LCD_D5_PIN), _GPIO_PIN_SET); /* Set D5 pin */
	_GPIO_WritePin(LCD_D6_GPIO, (((CMD >> 6) & 1U) << LCD_D6_PIN), _GPIO_PIN_SET); /* Set D6 pin */
	_GPIO_WritePin(LCD_D7_GPIO, (((CMD >> 7) & 1U) << LCD_D7_PIN), _GPIO_PIN_SET); /* Set D7 pin */
	
	#endif
	
	/* Update Control Pin's */
	_GPIO_WritePin(LCD_EN_GPIO, (1 << LCD_EN_PIN), _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(LCD_EN_GPIO, (1 << LCD_EN_PIN), _GPIO_PIN_RESET); /* Reset EN pin */
	
	/* ----------- Low Nibble Update ------------ */
	#ifdef LCD_DATA_PORT_OPTIMIZE
	
	/* Reset Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, (1 << LCD_D7_PIN)|(1 << LCD_D6_PIN)|(1 << LCD_D5_PIN)|(1 << LCD_D4_PIN), _GPIO_PIN_RESET); /* Reset D4 pin */
	
	/* Update Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, (((CMD >> 3) & 1U) << LCD_D7_PIN)|(((CMD >> 2) & 1U) << LCD_D6_PIN)|(((CMD >> 1) & 1U) << LCD_D5_PIN)|((CMD & 1U) << LCD_D4_PIN), _GPIO_PIN_SET); /* Set D4 pin */
	
	#else
	
	/* Reset Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, (1 << LCD_D4_PIN), _GPIO_PIN_RESET); /* Reset D4 pin */
	_GPIO_WritePin(LCD_D5_GPIO, (1 << LCD_D5_PIN), _GPIO_PIN_RESET); /* Reset D5 pin */
	_GPIO_WritePin(LCD_D6_GPIO, (1 << LCD_D6_PIN), _GPIO_PIN_RESET); /* Reset D6 pin */
	_GPIO_WritePin(LCD_D7_GPIO, (1 << LCD_D7_PIN), _GPIO_PIN_RESET); /* Reset D7 pin */
	
	/* Update Data Pin's */
	_GPIO_WritePin(LCD_D4_GPIO, ((CMD & 1U) << LCD_D4_PIN)       , _GPIO_PIN_SET); /* Set D4 pin */
	_GPIO_WritePin(LCD_D5_GPIO, (((CMD >> 1) & 1U) << LCD_D5_PIN), _GPIO_PIN_SET); /* Set D5 pin */
	_GPIO_WritePin(LCD_D6_GPIO, (((CMD >> 2) & 1U) << LCD_D6_PIN), _GPIO_PIN_SET); /* Set D6 pin */
	_GPIO_WritePin(LCD_D7_GPIO, (((CMD >> 3) & 1U) << LCD_D7_PIN), _GPIO_PIN_SET); /* Set D7 pin */
	
	#endif
	
	/* Update Control Pin's */
	_GPIO_WritePin(LCD_EN_GPIO, (1 << LCD_EN_PIN), _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(LCD_EN_GPIO, (1 << LCD_EN_PIN), _GPIO_PIN_RESET); /* Reset EN pin */
	
	#endif
	
}

void LCD_Transmit_8Bit(uint8_t CMD, LCD_TransmitTypeDef TType)
{
	
	#if LCD_MODE == LCD_MODE_8
	
	DELAY_MS(1); /* Wait for transfer previous command */
	
	/* ------------ High Byte Update ------------ */
	_GPIO_WritePin(LCD_RS_GPIO, (1 << LCD_RS_PIN), TType); /* Set/Reset RS pin */
	_GPIO_WritePin(LCD_RW_GPIO, (1 << LCD_RW_PIN), _GPIO_PIN_RESET); /* Reset RW pin */
	
	#ifdef LCD_DATA_PORT_OPTIMIZE
	
	/* Reset Data Pin's */
	_GPIO_WritePin(LCD_D0_GPIO, (1 << LCD_D7_PIN)|
	                            (1 << LCD_D6_PIN)|
	                            (1 << LCD_D5_PIN)|
	                            (1 << LCD_D4_PIN)|
	                            (1 << LCD_D3_PIN)|
	                            (1 << LCD_D2_PIN)|
	                            (1 << LCD_D1_PIN)|
	                            (1 << LCD_D0_PIN), _GPIO_PIN_RESET); /* Reset data pins */
	
	/* Update Data Pin's */
	_GPIO_WritePin(LCD_D0_GPIO, (((CMD >> 7) & 1U) << LCD_D7_PIN)|
	                            (((CMD >> 6) & 1U) << LCD_D6_PIN)|
	                            (((CMD >> 5) & 1U) << LCD_D5_PIN)|
	                            (((CMD >> 4) & 1U) << LCD_D4_PIN)|
	                            (((CMD >> 3) & 1U) << LCD_D3_PIN)|
	                            (((CMD >> 2) & 1U) << LCD_D2_PIN)|
	                            (((CMD >> 1) & 1U) << LCD_D1_PIN)|
	                            ((CMD & 1U) << LCD_D0_PIN), _GPIO_PIN_SET); /* Set data pins */
	
	#else
	
	/* Reset Data Pin's */
	_GPIO_WritePin(LCD_D0_GPIO, (1 << LCD_D0_PIN), _GPIO_PIN_RESET); /* Reset D0 pin */
	_GPIO_WritePin(LCD_D1_GPIO, (1 << LCD_D1_PIN), _GPIO_PIN_RESET); /* Reset D1 pin */
	_GPIO_WritePin(LCD_D2_GPIO, (1 << LCD_D2_PIN), _GPIO_PIN_RESET); /* Reset D2 pin */
	_GPIO_WritePin(LCD_D3_GPIO, (1 << LCD_D3_PIN), _GPIO_PIN_RESET); /* Reset D3 pin */
	_GPIO_WritePin(LCD_D4_GPIO, (1 << LCD_D4_PIN), _GPIO_PIN_RESET); /* Reset D4 pin */
	_GPIO_WritePin(LCD_D5_GPIO, (1 << LCD_D5_PIN), _GPIO_PIN_RESET); /* Reset D5 pin */
	_GPIO_WritePin(LCD_D6_GPIO, (1 << LCD_D6_PIN), _GPIO_PIN_RESET); /* Reset D6 pin */
	_GPIO_WritePin(LCD_D7_GPIO, (1 << LCD_D7_PIN), _GPIO_PIN_RESET); /* Reset D7 pin */
	
	/* Update Data Pin's */
	_GPIO_WritePin(LCD_D0_GPIO, ((CMD & 1U) << LCD_D0_PIN)       , _GPIO_PIN_SET); /* Set D0 pin */
	_GPIO_WritePin(LCD_D1_GPIO, (((CMD >> 1) & 1U) << LCD_D1_PIN), _GPIO_PIN_SET); /* Set D1 pin */
	_GPIO_WritePin(LCD_D2_GPIO, (((CMD >> 2) & 1U) << LCD_D2_PIN), _GPIO_PIN_SET); /* Set D2 pin */
	_GPIO_WritePin(LCD_D3_GPIO, (((CMD >> 3) & 1U) << LCD_D3_PIN), _GPIO_PIN_SET); /* Set D3 pin */
	_GPIO_WritePin(LCD_D4_GPIO, (((CMD >> 4) & 1U) << LCD_D4_PIN), _GPIO_PIN_SET); /* Set D4 pin */
	_GPIO_WritePin(LCD_D5_GPIO, (((CMD >> 5) & 1U) << LCD_D5_PIN), _GPIO_PIN_SET); /* Set D5 pin */
	_GPIO_WritePin(LCD_D6_GPIO, (((CMD >> 6) & 1U) << LCD_D6_PIN), _GPIO_PIN_SET); /* Set D6 pin */
	_GPIO_WritePin(LCD_D7_GPIO, (((CMD >> 7) & 1U) << LCD_D7_PIN), _GPIO_PIN_SET); /* Set D7 pin */
	
	#endif
	
	/* Update Control Pin's */
	_GPIO_WritePin(LCD_EN_GPIO, (1 << LCD_EN_PIN), _GPIO_PIN_SET); /* Set EN pin */
	_GPIO_WritePin(LCD_EN_GPIO, (1 << LCD_EN_PIN), _GPIO_PIN_RESET); /* Reset EN pin */
	
	#endif
	
}

/* ......................... Initialize ........................ */
void LCD_Init(void)
{
	
	DELAY_MS(LCD_POWER_ON_TIME_MS); /* No data should be transferred to or from the display during this time */
	
	#if LCD_MODE == LCD_MODE_4
	
		LCD_Transmit = LCD_Transmit_4Bit; /* Set Function */
		
		/* ------------------- Initialize LCD ------------------- */
		LCD_PutCMD(LCD_MODE_8); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(LCD_SET_MODE_TIME_MS); /* No data should be transferred to or from the display during this time */
	
		LCD_PutCMD(LCD_MODE_8); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(1); /* No data should be transferred to or from the display during this time */
	
		LCD_PutCMD((LCD_MODE_8 << LCD_BIT_4) | LCD_MODE_4); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
	
		LCD_PutCMD((LCD_MODE_4 << LCD_BIT_4) | (LCD_LINES << LCD_BIT_LINES) | (LCD_FONT << LCD_BIT_FONT)); /* Function Set (Interface = 4 -bit, Set N and F for number of lines and character font) */
	
	#else
	
		LCD_Transmit = LCD_Transmit_8Bit; /* Set Function */
		
		/* ------------------- Initialize LCD ------------------- */
		LCD_PutCMD(LCD_MODE_8 << LCD_BIT_4); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(LCD_SET_MODE_TIME_MS); /* No data should be transferred to or from the display during this time */
	
		LCD_PutCMD(LCD_MODE_8 << LCD_BIT_4); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(1); /* No data should be transferred to or from the display during this time */
	
		LCD_PutCMD(LCD_MODE_8 << LCD_BIT_4); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
	
		LCD_PutCMD((LCD_MODE_8 << LCD_BIT_4) | (LCD_LINES << LCD_BIT_LINES) | (LCD_FONT << LCD_BIT_FONT)); /* Function Set (Interface = 8 -bit, Set N and F for number of lines and character font) */
	
	#endif
	
	LCD_PutCMD(LCD_DISPLAY_OFF); /* Display OFF */
	
	LCD_PutCMD(LCD_CLEAR_DISPLAY); /* Clear Display */
	
	LCD_PutCMD(LCD_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER); /* Entry Mode Set: */
	
	LCD_PutCMD(LCD_DISABLE_LCD_CURSOR); /* Display ON (Set C and B for cursor/Blink options.) */
	
}

void LCD_Init2(LCD_TypeDef *pLCD)
{
	
	DELAY_MS(LCD_POWER_ON_TIME_MS); /* No data should be transferred to or from the display during this time */
	
	if (pLCD->Mode == LCD_MODE_4)
	{
		
		LCD_Transmit = LCD_Transmit_4Bit; /* Set Function */
		
		/* ------------------- Initialize LCD ------------------- */
		LCD_PutCMD(LCD_MODE_8); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(LCD_SET_MODE_TIME_MS); /* No data should be transferred to or from the display during this time */
		
		LCD_PutCMD(LCD_MODE_8); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(1); /* No data should be transferred to or from the display during this time */
		
		LCD_PutCMD((LCD_MODE_8 << LCD_BIT_4) | LCD_MODE_4); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
		
		LCD_PutCMD((LCD_MODE_4 << LCD_BIT_4) | (pLCD->DisplayLines << LCD_BIT_LINES) | (pLCD->Font << LCD_BIT_FONT)); /* Function Set (Interface = 4 -bit, Set N and F for number of lines and character font) */
		
	}
	else
	{
		
		LCD_Transmit = LCD_Transmit_8Bit; /* Set Function */
		
		/* ------------------- Initialize LCD ------------------- */
		LCD_PutCMD(LCD_MODE_8 << LCD_BIT_4); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(LCD_SET_MODE_TIME_MS); /* No data should be transferred to or from the display during this time */
		
		LCD_PutCMD(LCD_MODE_8 << LCD_BIT_4); /* Function Set Command: (8-Bit interface) */
		DELAY_MS(1); /* No data should be transferred to or from the display during this time */
		
		LCD_PutCMD(LCD_MODE_8 << LCD_BIT_4); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
		
		LCD_PutCMD((LCD_MODE_8 << LCD_BIT_4) | (pLCD->DisplayLines << LCD_BIT_LINES) | (pLCD->Font << LCD_BIT_FONT)); /* Function Set (Interface = 8 -bit, Set N and F for number of lines and character font) */
		
	}
	
	LCD_PutCMD(LCD_DISPLAY_OFF); /* Display OFF */
	
	LCD_PutCMD(LCD_CLEAR_DISPLAY); /* Clear Display */
	
	LCD_PutCMD(LCD_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER); /* Entry Mode Set: */
	
	LCD_PutCMD(LCD_DISABLE_LCD_CURSOR); /* Display ON (Set C and B for cursor/Blink options.) */
	
}

void LCD_DefInit(void)
{
	
	DELAY_MS(LCD_POWER_ON_TIME_MS); /* No data should be transferred to or from the display during this time */
		
	LCD_Transmit = LCD_Transmit_4Bit; /* Set Function */
	
	/* ------------------- Initialize LCD ------------------- */
	LCD_PutCMD(LCD_MODE_8); /* Function Set Command: (8-Bit interface) */
	DELAY_MS(LCD_SET_MODE_TIME_MS); /* No data should be transferred to or from the display during this time */
	
	LCD_PutCMD(LCD_MODE_8); /* Function Set Command: (8-Bit interface) */
	DELAY_MS(1); /* No data should be transferred to or from the display during this time */
	
	LCD_PutCMD((LCD_MODE_8 << LCD_BIT_4) | LCD_MODE_4); /* Function Set Command: (8-Bit interface) After this command is written, BF can be checked / Function Set: Sets interface to 4 -bit */
	
	LCD_PutCMD((LCD_MODE_4 << LCD_BIT_4) | (LCD_LINES << LCD_BIT_LINES) | (LCD_FONT << LCD_BIT_FONT)); /* Function Set (Interface = 4 -bit, Set N and F for number of lines and character font) */
	
	LCD_PutCMD(LCD_DISPLAY_OFF); /* Display OFF */
	
	LCD_PutCMD(LCD_CLEAR_DISPLAY); /* Clear Display */
	
	LCD_PutCMD(LCD_SHIFT_CURSOR_TO_RIGHT_AFTER_WRITE_CHARACTER); /* Entry Mode Set: */
	
	LCD_PutCMD(LCD_DISABLE_LCD_CURSOR); /* Display ON (Set C and B for cursor/Blink options.) */
	
}

/* ............................................................. */
void LCD_PutString(char *str)
{
	
	while (*str != '\0') /* Loop for send data */
	{
		
		LCD_PutChar(*str); /* Send character */
		str++; /* Select next character */
		
	}
	
}

void LCD_PutStringF(const char *str)
{
	
	#ifdef pgm_read_byte
	
	while (pgm_read_byte(str) != '\0') /* Loop for send data */
	{
		
		LCD_PutChar(pgm_read_byte(str)); /* Send character */
		str++; /* Select next character */
		
	}
	
	#endif // pgm_read_byte
	
}

void LCD_Clear(void)
{
	
	LCD_PutCMD(LCD_CLEAR_DISPLAY); /* Send clear command */
	LCD_PutCMD(LCD_RETURN_HOME); /* Send return home command */
	
}

void LCD_GotoXY(uint8_t Column, uint8_t Row)
{
	
	switch (Row)
	{
		case LCD_ROW_0: /* First Row selected */
		{
			LCD_PutCMD(LCD_ROW_0_ADD + Column); /* Send DD RAM address */
		}
		break;
		case LCD_ROW_1: /* Second Row selected */
		{
			LCD_PutCMD(LCD_ROW_1_ADD + Column); /* Send DD RAM address */
		}
		break;
		case LCD_ROW_2: /* Third Row selected */
		{
			LCD_PutCMD(LCD_ROW_2_ADD + Column); /* Send DD RAM address */
		}
		break;
		case LCD_ROW_3: /* Fourth Row selected */
		{
			LCD_PutCMD(LCD_ROW_3_ADD + Column); /* Send DD RAM address */
		}
		break;
		
		default:
		/* Your code here */
		break;
	}
	
}

void LCD_Shift(uint8_t Shifts, LCD_CMDTypeDef Dir, uint16_t DelayTime)
{
	
	#if DelayTime == 0
	DelayTime = 1;
	#endif
	
	/* ---------------------- */
	if (DelayTime < LCD_SET_MODE_TIME_MS)
	{
		DelayTime = LCD_SET_MODE_TIME_MS;
	}
	
	/* ---------------------- */
	for (; Shifts > 0; Shifts--) /* Loop for send command */
	{
		
		LCD_PutCMD(Dir); /* Send shift command */
		DELAY_MS(DelayTime); /* Wait for next shift */
		
	}
	
}

void LCD_StoreInCGRAM(uint8_t *CharMap, char Code)
{
	
	uint8_t pixel_count = 0;
	//uint8_t cgram_add   = 0x40 | (Code << 3);
	
	/* ----------- CGRAM Address transmit ----------- */
	LCD_PutCMD((0x40 | (Code << 3)));
	
	/* --------------- Lines transmit --------------- */
	for (; pixel_count < 8; pixel_count++)
	{
		LCD_PutChar(CharMap[pixel_count]);
	}
	
	/* ---------------------------------------------- */
	LCD_PutCMD(LCD_ROW_0_ADD);
	
}

void LCD_StoreInCGRAMF(const uint8_t *CharMap, char Code)
{
	
	#ifdef pgm_read_byte
	
	uint8_t pixel_count = 0;
	//uint8_t cgram_add   = 0x40 | (Code << 3);
	
	/* ----------- CGRAM Address transmit ----------- */
	LCD_PutCMD((0x40 | (Code << 3)));
	
	/* --------------- Lines transmit --------------- */
	for (; pixel_count < 8; pixel_count++)
	{
		LCD_PutChar(pgm_read_byte(&CharMap[pixel_count]));
	}
	
	/* ---------------------------------------------- */
	LCD_PutCMD(LCD_ROW_0_ADD);
	
	#endif // pgm_read_byte
	
}

void LCD_PutCustomChar(uint8_t *CharMap, char Code, uint8_t Column, uint8_t Row)
{
	
	/* --------------- Save on CGRAM ---------------- */
	LCD_StoreInCGRAM(CharMap, Code);
	
	/* --------------- Show character --------------- */
	LCD_GotoXY(Column, Row);
	LCD_PutChar(Code);
	
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
