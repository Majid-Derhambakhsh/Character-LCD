# Character-Lcd
Character LCD library for use in AVR - ARM Cortex M

### Version : 0.2.0

- #### Type : Embedded Software.

- #### Support :  
               - AVR series  
               - ARM STM32 series  

- #### Program Language : C/C++

- #### Properties :

### Initialization and de-initialization functions:
```c++
void Lcd_Init(void);
``` 

### LCD operation functions:
```c++
void Lcd_PutChar(char character);
void Lcd_PutString(char *str);
void Lcd_Clear(void);
void Lcd_GotoXY(uint8_t column , uint8_t row);
void Lcd_ShiftToLeft(uint8_t shift_number , uint16_t shift_time);
void Lcd_ShiftToRight(uint8_t shift_number , uint16_t shift_time);
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
Lcd_Config.Font = _FONT_5X10;
Lcd_Config.Mode = _4BIT_INTERFACE;
Lcd_Config.NumberOfLine = _2LINE_DISPLAY;

Lcd_Init();
```  
      
3.1  Using LCD operation functions, for example:  
```c++
   int main()
   {
      Lcd_Config.Font = _FONT_5X10;
      Lcd_Config.Mode = _4BIT_INTERFACE;
      Lcd_Config.NumberOfLine = _2LINE_DISPLAY;

      Lcd_Init();
      
      /* Show character */
      Lcd_Clear();
      Lcd_PutChar('A');
      _Delay_Ms(1000);

      while (1)
      {
        
        Lcd_Clear();
        Lcd_GotoXY(5,0);
        Lcd_PutString("Hello");
        Lcd_ShiftToLeft(11,500);
        _Delay_Ms(1000);
        
      }
   }
       
```

#### Developer: Majid Derhambakhsh

