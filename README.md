![Banner](CHLCD.png)

# Character-LCD
Character LCD library for use in AVR - ARM Cortex M

### Version : 1.0.0

- #### Type : Embedded Software.

- #### Support :  
               - AVR series  
               - ARM STM32 series  

- #### Program Language : C/C++

- #### Properties :

- #### Changes :  
               - Add: Support RTOS mode  
               - Add: void Lcd_DefInit(void) function  
               - Modify: Change Lcd_xxx to LCD_xxx in functions and configuration  

               - Add: First STM32Cube Package  

- #### Required Library/Driver :
  GPIO Unit (added in library for AVR) : [GPIO Unit](https://github.com/Majid-Derhambakhsh/gpio-unit)  


### Initialization and de-initialization functions:
```c++
void LCD_Init(void);
void LCD_DefInit(void);
``` 

### LCD operation functions:
```c++
void LCD_PutChar(char character);
void LCD_PutString(char *str);
void LCD_Clear(void);
void LCD_GotoXY(uint8_t column , uint8_t row);
void LCD_ShiftToLeft(uint8_t shift_number , uint16_t shift_time);
void LCD_ShiftToRight(uint8_t shift_number , uint16_t shift_time);
``` 

### Macros:
```c++
#define _LCD_CTRL_PORT GPIOx
#define _LCD_DATA_PORT GPIOx

#define _LCD_DATA_PIN  x
#define _LCD_RS_PIN    x
#define _LCD_RW_PIN    x
#define _LCD_EN_PIN    x
``` 

## How to use this library

### The LCD library can be used as follows:
1.1  LCD configuration in the character_lcd_conf.h header, for example:  
         
```c++
/* ~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~ Data PORT ~~~~~~ */

#define _LCD_CTRL_PORT GPIOA
#define _LCD_DATA_PORT GPIOA

/* ~~~~~~ Data PIN ~~~~~~~ */

#define _LCD_DATA_PIN  3
#define _LCD_RS_PIN    0
#define _LCD_RW_PIN    1
#define _LCD_EN_PIN    2
```  
      
2.1  Initialize:  
        
```c++
LCD_Config.Font = _FONT_5X10;
LCD_Config.Mode = _4BIT_INTERFACE;
LCD_Config.NumberOfLine = _2LINE_DISPLAY;

LCD_Init();
```  
      
3.1  Using LCD operation functions, for example:  
```c++
   int main()
   {
      LCD_Config.Font = _FONT_5X10;
      LCD_Config.Mode = _4BIT_INTERFACE;
      LCD_Config.NumberOfLine = _2LINE_DISPLAY;

      LCD_Init();
      
      /* Show character */
      LCD_Clear();
      LCD_PutChar('A');
      _Delay_Ms(1000);

      while (1)
      {
        
        LCD_Clear();
        LCD_GotoXY(5,0);
        LCD_PutString("Hello");
        LCD_ShiftToLeft(11,500);
        _Delay_Ms(1000);
        
      }
   }
       
```

#### Developer: Majid Derhambakhsh

