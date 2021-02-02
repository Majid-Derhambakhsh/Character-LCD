/*
------------------------------------------------------------------------------
~ File   : gpio_unit.h
~ Author : Majid Derhambakhsh
~ Version: V0.2.1
~ Created: 11/27/2019 03:57:00 AM
~ Brief  :
~ Support:
		   E-Mail : Majid.Derhambakhsh@gmail.com (subject: Embedded Library Support)

		   Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:

~ Attention  :

~ Changes    :
				Improve: Code for CVAVR compiler
------------------------------------------------------------------------------
*/

#ifndef __GPIO_UNIT_H_
#define __GPIO_UNIT_H_

/* ----------- Includes ----------- */

/*----------------------------------------------------------*/

#ifdef __CODEVISIONAVR__  /* Check compiler */

#include <io.h>            /* Import AVR IO library */

/*----------------------------------------------------------*/

#elif defined(__GNUC__)   /* Check compiler */

#include <avr/io.h>        /* Import AVR IO library */

/*----------------------------------------------------------*/

#else                     /* Compiler not found */

#error Compiler not supported  /* Send error */

#endif

/*----------------------------------------------------------*/

#include <stdint.h>

/* ------------ Define ------------ */

#define _GPIO_PIN_SET   1 /* Define for write state */
#define _GPIO_PIN_RESET 0 /* Define for write state */

/* --------- By Compiler ---------- */

#ifdef __CODEVISIONAVR__  /* CVAVR compiler */

typedef uint8_t  register_t;

/* -------------------------------- */

#elif defined(__GNUC__)   /* GCC compiler */

typedef volatile uint8_t  register_t;

#endif

/* ----------- Prototypes ----------- */

void GPIO_WritePin(register_t *GPIOx , uint8_t GPIO_Pin , uint8_t PinState); /* Function for write data to output */
/*
	Guide   :
			 Parameters    :
							GPIOx    :  where x can be (A..F) to select the 
										GPIO peripheral for Atmega - Tiny family.
										
							GPIO_Pin :  specifies the port bit to be written. 
										This parameter can be one of (1 << x) where x can be (0..7).
										
							PinState :  specifies the value to be written to the selected bit.
										This parameter can be one of the values:
											
											_GPIO_PIN_RESET: to clear the port pin.
											_GPIO_PIN_SET: to set the port pin.
							
			 Return Values :
							
	Example :
			 GPIO_WritePin( &PORTA , 0xFF , _GPIO_PIN_SET );
			 GPIO_WritePin( &PORTA , 0xFF , _GPIO_PIN_RESET );
*/

void GPIO_ClearPin(register_t *GPIOx , uint8_t GPIO_Pin); /* Function for clear pin */
/*
	Guide   :
			 Parameters    :
							GPIOx    :  where x can be (A..F) to select the 
										GPIO peripheral for Atmega - Tiny family.
							
							GPIO_Pin :  specifies the port bit to be written. 
										This parameter can be (0..7).
			 Return Values :
							
	Example :
			 GPIO_ClearPin( &PORTA , 2 );
*/

uint8_t GPIO_ReadPin(register_t *GPIOx , uint8_t GPIO_Pin); /* Function for read pin state */
/*
	Guide   :
			 Parameters    :
							GPIOx    :  where x can be (A..F) to select the 
										GPIO peripheral for Atmega - Tiny family.
										
							GPIO_Pin :  specifies the port bit to be written. 
										This parameter can be (0..7).
							
			 Return Values :
							
	Example :
			 GPIO_ReadPin( &PINA , 3 );
*/

uint8_t GPIO_ReadPort(register_t *GPIOx); /* Function for read port value */
/*
	Guide   :
			 Parameters    :
							GPIOx    :  where x can be (A..F) to select the 
										GPIO peripheral for Atmega - Tiny family.
							
			 Return Values :
							PINx Register value.
							
	Example :
			 uint8_t port_value;
			 
			 port_value = GPIO_ReadPort( &PINA );
*/

void GPIO_TogglePin(register_t *GPIOx , uint8_t GPIO_Pin); /* Function for toggle pin */
/*
	Guide   :
			 Parameters    :
							GPIOx    :  where x can be (A..F) to select the 
										GPIO peripheral for Atmega - Tiny family.
										
							GPIO_Pin :  specifies the port bit to be written. 
										This parameter can be (0..7).
							
			 Return Values :
							
	Example :
			 GPIO_TogglePin( &PORTA , 3 );
*/

uint8_t GPIO_ReadRegister(register_t *REGISTERx); /* Function for read register value */
/*
	Guide   :
			 Parameters    :
							REGISTERx    :  Select the GPIO Register for Atmega - Tiny family.
			 Return Values :
							Register x value.
							
	Example :
			 uint8_t register_value;
			 
			 port_value = GPIO_ReadRegister( &DDRA );
*/

#endif /* __GPIO_UNIT_H_ */
