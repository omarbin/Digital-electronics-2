/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function

/* Defines -------------------------------------------------------------*/ 
#define COL1 1 
#define COL2 11

/*variables -------------------------------------------------------------*/ 
uint8_t customChar[6*8] = {
	//addr 0: 00000
	0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
	//addr 1: 10000
	0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,
	//addr 2: 11000
	0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,
	//addr 3: 11100
	0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100,
	//addr 4: 11110
	0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110,
	//addr 5: 11111
	0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,	 
};

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
	
    // Put string(s) at LCD display
	lcd_gotoxy(COL1, 0); lcd_puts("00:00.0");   //Stopwatch
	lcd_gotoxy(COL2, 0); lcd_putc('a');         // Seconds^2
	lcd_gotoxy(COL1, 1); lcd_putc('b');         //progress bar
	lcd_gotoxy(COL2, 1); lcd_putc('c');         // Rotating text
	
	//Custom character generator 
	//Set pointer to beginning of CGRAM memory
	lcd_command(1 << LCD_CGRAM);
	for (uint8_t i =0; i < 6*8 ; i++)
	{
		//store all new chars to memory line by line
		lcd_data(customChar[i]);
	}
	
	//Set pointer to beginning of DDRAM memory
	lcd_command(1 << LCD_DDRAM);
	//lcd_gotoxy(COL1, 1);
	// Display first custom character
	lcd_putc(0); 

    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Enable interrupt and set the overflow prescaler to 16 ms
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	
	TIM0_overflow_16ms();
    TIM0_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */

ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
    static uint8_t tens = 0;          // Tenths of a second
    static uint8_t secs = 0;          // Seconds
	static uint8_t mins = 0;          // Minutes
    char lcd_string[2] = "00";       // String for converting numbers by itoa()
	char lcd_longstring[4];
	
	lcd_gotoxy(COL1 + tens, 1);
	lcd_putc(number_of_overflows);
	
    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;
		//update tenth of seconds
		tens++;
		if (tens>=10) 
		{
			tens=0;
			//update seconds 
			secs++;			
			if (secs >= 60)
			{
				secs=0;
				//update minutes
				mins++;
				if (mins >= 60)
				{
					mins=0;
				}
				
				//display minutes
				lcd_gotoxy(COL1, 0);
				if (mins < 10)
				lcd_putc('0');
				itoa(mins, lcd_string, 10);
				lcd_puts(lcd_string);
				
				//seconds^2
				lcd_gotoxy(COL2, 0);
				lcd_puts("    ");
			}
					
			// display seconds
			lcd_gotoxy(COL1 + 3, 0);
			
			if (secs < 10)
			   lcd_putc('0');
			itoa(secs, lcd_string, 10);
			lcd_puts(lcd_string);
			
			//display seconds^2
			lcd_gotoxy(COL2, 0);
			itoa(secs*secs, lcd_longstring, 10);
			lcd_puts(lcd_longstring); 
	    }
		
		// display hundredth of seconds 
		lcd_gotoxy(COL1 + 6, 0);
		// convert cnt0 in decimal to string 
		itoa(tens, lcd_string, 10);
		lcd_puts(lcd_string);
    }
	
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t symbol = 0;
	static uint8_t position = 0;
	
	lcd_gotoxy(COL1 + position, 1); 
	lcd_putc(symbol);
	
	symbol++;
	if (symbol >= 6) 
	{
		symbol = 0;
		position++;
		if (position >= 10)
		{
			position = 0;
			lcd_gotoxy(COL1, 1);
			lcd_puts("          ");
		}	
	}
	
}
