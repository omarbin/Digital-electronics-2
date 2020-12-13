/*
 * gpio.c
 *
 * Created: 02/12/2020 21:06:48
 *  Author: Guillermo Cortés Orellana & Omar Bin Rahman  
 */ 

/***********************************************************************
 * 
 * keypad library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) Guillermo Cortés Orellana & Omar Bin Rahman 
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include "keypad.h"
#include "gpio.h"

/* Function definitions ----------------------------------------------*/

/*************************************************************************
*  Set different rows and column of the keypad as output 
*  and input respectively 
*
*  Input:   none
*
*  Returns:  none
*************************************************************************/
void keypad_setup_pin(void)
{	
	/************************ CONFIGURATION OF KEYPAD-ROWS ************************/
	/* PIN PC0 -> ROW1 */
	GPIO_config_output(&DDRC, ROW1);						// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW1);							// Put in HIGH level
	
	/* PIN PC1 -> ROW2 */
	GPIO_config_output(&DDRC, ROW2);						// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW2);							// Put in HIGH level
	
	/* PIN PC2 -> ROW3 */
	GPIO_config_output(&DDRC, ROW3);						// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW3);							// Put in HIGH level
	
	/* PIN PC3 -> ROW4 */
	GPIO_config_output(&DDRC, ROW4);						// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW4);							// Put in HIGH level
	
	/*********************** CONFIGURATION OF KEYPAD-COLUMNS ***********************/
	/* PIN PD3 -> COL1 */
	GPIO_config_input_pullup(&DDRD, COL1);					// Set pin as INPUT in Data Direction Register... (PIN -> INPUT)
	
	/* PIN PC5 -> COL2 */
	GPIO_config_input_pullup(&DDRC, COL2);					// Set pin as INPUT in Data Direction Register... (PIN -> INPUT)
	
	/* PIN PC4 -> COL3 */
	GPIO_config_input_pullup(&DDRC, COL3);					// Set pin as INPUT in Data Direction Register... (PIN -> INPUT)		
}

/*************************************************************************
*  Get which key is pushed
*
*  Input:   none
*
*  Returns:  Control value (1 to 11) which shows which key is pushed (digits 0 to 9, * and #)
*************************************************************************/
uint8_t keypad_scan(void)
{ 
	uint8_t key = 12;
	
	for(uint8_t i = 0; i<=3; i++)                           // Loop to go over different ROWS
	{							
		if(i==0)                                            // First iteration
		{																						
			GPIO_write_high(&PORTC, ROW4);					// Put ROW4 in HIGH level
			GPIO_write_low(&PORTC, ROW1);					// Put ROW1 in LOW level	
		}
		else if(i==1)                                       // Second iteration
		{																					
			GPIO_write_high(&PORTC, ROW1);					// Put ROW1 in HIGH level
			GPIO_write_low(&PORTC, ROW2);					// Put ROW2 in LOW level
		}
		else if(i==2)                                       // Third iteration
		{										
			GPIO_write_high(&PORTC, ROW2);					// Put ROW2 in HIGH level
			GPIO_write_low(&PORTC, ROW3);					// Put ROW3 in LOW level
		}
		else if(i==3)                                       // Fourth iteration
		{										
			GPIO_write_high(&PORTC, ROW3);					// Put ROW3 in HIGH level
			GPIO_write_low(&PORTC, ROW4);					// Put ROW4 in LOW level
		}
		
		for(uint8_t j = 0; j<=2; j++)                       // Loop to go over different COLUMNS
		{						
			if (GPIO_read(&PIND,COL1) == 1)					// Read the value of COLUMN1 and compare it to '1' in order to know which key is pushed
			{
				if (i == 0)									// Previous first iteration (ROW1 in LOW level)
				{
					key = 1;								// We push key '1'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW1);			// Put ROW1 in HIGH level again
				}
				else if(i == 1)                             // Previous second iteration (ROW2 in LOW level)
				{							
					key = 4;								// We push the key '4'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW2);			// Put ROW2 in HIGH level again
				}
				else if(i == 2)                             // Previous third iteration (ROW3 in LOW level)
				{							
					key = 7;								// We push the key '7'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW3);			// Put ROW3 in HIGH level again
				}
				else if(i == 3)                             // Previous fourth iteration (ROW4 in LOW level)
				{							
					key = 10;								// We push the key '*'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW4);			// Put ROW4 in HIGH level again
				}
			}
			else if(GPIO_read(&PINC,COL2) == 1)             // Read the value of COLUMN2 and compare it to '1' in order to know which key is pushed
			{		
				if (i == 0)									// Previous first iteration (ROW1 in LOW level)
				{
					key = 2;								// We push the key '2'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW1);			// Put ROW1 in HIGH level again	
				}
				else if(i == 1)                             // Previous second iteration (ROW2 in LOW level)
				{							
					key = 5;								// We push the key '5'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW2);			// Put ROW2 in HIGH level again
				}
				else if(i == 2)                             // Previous third iteration (ROW3 in LOW level)
				{							
					key = 8;								// We push the key '8'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW3);			// Put ROW3 in HIGH level again	
				}
				else if(i == 3)                             // Previous fourth iteration (ROW4 in LOW level)
				{								
					key = 0;								// We push the key '0'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW4);			// Put ROW4 in HIGH level again
				}
			}
			else if(GPIO_read(&PINC,COL3) == 1)             // Read the value of COLUMN3 and compare it to '1' in order to know which key is pushed
			{			
				if (i == 0)									// Previous first iteration (ROW1 in LOW level)
				{
					key = 3;								// We push the key '3'
					i=4;									// End of first loop	
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW1);			// Put ROW1 in HIGH level again
				}
				else if(i == 1)                             // Previous second iteration (ROW2 in LOW level)
				{							
					key = 6;								// We push the key '6'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW2);			// Put ROW2 in HIGH level again
				}
				else if(i == 2)                             // Previous third iteration (ROW3 in LOW level)
				{							
					key = 9;								// We push the key '9'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW3);			// Put ROW3 in HIGH level again
				}
				else if(i == 3)                             // Previous fourth iteration (ROW4 in LOW level)
				{							
				
					key = 11;								// We push the key '#'
					i=4;									// End of first loop
					j=3;									// End of second loop
					GPIO_write_high(&PORTC, ROW4);			// Put ROW4 in HIGH level again
				}
			}												// end 'if' for  COLuMNS	
		}													// end 2º 'for'
	}														// end 1º 'for'
	return key;												// Return the value of the key which is pushed
}