/*
 * Final_Project.c
 *
 * Created: 26/11/2020 22:23:47
 * Author: Guillermo Cortés Orellana & Omar Bin Rahman 
 */ 

/***********************************************************************
 * 
 * System security door AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) Guillermo Cortés Orellana & Omar Bin Rahman
 *
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB4									// AVR pin where green LED GREEN is connected
#define LED_RED PB3										// AVR pin where green LED RED is connected
#define DOOR   PB5										// AVR pin where green RELAY is connected
#define SPEAKER PB2										// AVR pin where green SPEAKER is connected

#ifndef F_CPU
#define F_CPU 16000000									// CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>										// AVR device-specific IO definitions (IN/OUT)
#include <avr/interrupt.h>								// Interrupts standard C library for AVR-GCC
#include <stdlib.h>										// C library. Needed for conversion function
#include <util/delay.h>									// Functions for busy-wait delay loops 

#include "gpio.h"										// GPIO library for AVR-GCC
#include "timer.h"										// Timer library for AVR-GCC
#include "lcd.h"										// Peter Fleury's LCD library
#include "keypad.h"										// Keypad library
#include "uart.h"										// Peter Fleury's UART library

/* Variables ---------------------------------------------------------*/
uint8_t password1 [4] =  {1, 2, 3, 4};					// Password for Mrs. Paula
uint8_t password2 [4] =  {1, 0, 1, 0};					// Password for Mr. Fryza
uint8_t password3 [4] =  {2, 8, 1, 0};					// Password for Mr. Guillermo
uint8_t password4 [4] =  {1, 3, 0, 3};					// Password for Mr. Omar

/* Main function -----------------------------------------------------*/
int main(void)
{
	/*************************** Configuration of LEDs ***************************/
	
	/*LED_GREEN*/
	GPIO_config_output(&DDRB, LED_GREEN);				// Set LED GREEN as an output
	GPIO_write_low(&PORTB, LED_GREEN);					// Initially led OFF because active HIGH
	
	/*LED_RED*/
	GPIO_config_output(&DDRB, LED_RED);					// Set LED RED as an output
	GPIO_write_low(&PORTB, LED_RED);					// Initially led OFF because active HIGH
	
	/*********************** Configuration of the DOOR (RELAY) **********************/
	
	GPIO_config_output(&DDRB, DOOR);					// Set pin of the DOOR as an output
	GPIO_write_high(&PORTB, DOOR);						// Initially the door is closed (DOOR = '1')
	
	/************************* Configuration of the SPEAKER *************************/
	
	GPIO_config_output(&DDRB, SPEAKER);					// Set pin of the SPEAKER as an output
	GPIO_write_low(&PORTB, SPEAKER);					// Initially the SPEAKER is OFF (SPEAKER = '0')
		
	/************************* Configuration pins of KEYPAD *************************/
	
	keypad_setup_pin();									// Set the different keys of keypad
	
	/**************************** Configuration of LCD ******************************/
	
	// Initialize LCD display
	lcd_init(LCD_DISP_ON);
	
	// Put string(s) at LCD display
	lcd_gotoxy(0, 0);
	lcd_puts("Welcome to CorBin ST ");	
	lcd_puts("                   ");
	lcd_puts("Enter your code:");
	lcd_puts("    ");
	lcd_puts("        ----");	
	
	/************************** Configuration of TIMERs **************************/
	
	/*TIMER/COUNTER0*/
	// Configure Timer/Counter0 to Carry out scan on the keypad each 16 us
	// Enable interrupt and set the overflow prescaler to 16 us
    TIM0_overflow_16us();
    TIM0_overflow_interrupt_enable();
	
	/*TIMER/COUNTER1*/ 
	// Configure Timer/Counter1 to Open the door, play a sound on the speaker and turn on LED GREEN.
	// Disable interrupt because we don't use it at this moment
	TIM1_overflow_1s();
	TIM1_overflow_interrupt_disable();
	
	/*TIMER/COUNTER2*/
	// Configure Timer/Counter2 for the Waiting state to suspend the program for 5 seconds
	// Disable interrupt because we don't use it at this moment
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_disable();
	
	// Enables interrupts by setting the global interrupt mask
	sei();

	/*********************************** UART **********************************/
		
	// Initialize UART to asynchronous, 8N1, 9600
	uart_init(UART_BAUD_SELECT(9600, F_CPU));	
	
	while (1) 
    {
		 /* Empty loop. All subsequent operations are performed exclusively 
          * inside interrupt service routines ISRs */
    }
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter0 overflows. 
 * Carry out scan on the keypad each 16 us */
ISR(TIMER0_OVF_vect)
{	
	static uint8_t counter = 0;							// Counter to control which digit of the password we have introduced (first digit, second digit...)
	static uint8_t attempt = 0;							// Counter to control how many times we have introduced wrong password
	static uint8_t password [4] = "    ";				// Array to stock different characters we introduce in the keypad
		
	static uint8_t counter2 = 0;						// Counter to prove we have introduced 4 digits of our password,
														// to enable one ISR and to disable another ISR												
											
	static	uint32_t counter3 = 0;						// Counter to control no more than 5 seconds
														// elapse since we introduce the first character
			
	if(counter3 >= 1)									// Condition to start to control 5 seconds period
	{
		counter3++;
		
		if(counter3 == 10000)                           /* Condition to restart the process if we reach 5 seconds without  
														   completing the password since we push one or more keys */ 
		{
			counter3 = 0;								// Restart 'counter3'
			
			counter = 0;								// Restart 'counter'
			
			password [0] = 0;							// Put 0 value in position 0 of the array (restart)
			password [1] = 0;							// Put 0 value in position 1 of the array (restart)
			password [2] = 0;							// Put 0 value in position 2 of the array (restart)
			password [3] = 0;							// Put 0 value in position 3 of the array (restart)
			
			GPIO_write_high(&PORTB, LED_RED);			// Turn on LED RED to show the user spent more than 5 seconds to introduce the password 
			
			lcd_clrscr();								// Clear display and show new message
			lcd_puts("TIME IS UP.         ");
			lcd_puts("Try again.");	
			
			_delay_ms(2000);							// Wait 2 secs (2000 ms) and show new message
			
			lcd_clrscr();								// Clear display and show new message
			lcd_puts("Welcome to CorBin ST ");
			lcd_puts("                   ");
			lcd_puts("Enter your code:");
			lcd_puts("    ");
			lcd_puts("        ----");
			
			GPIO_write_low(&PORTB, LED_RED);			// Turn off previous LED RED  
		}
	}
	
	if((keypad_scan() != 12) & (counter == 0))			// Condition used for prove first digit of the password has been introduced    
	{
		lcd_gotoxy(0, 0);								// Display *--- 
		lcd_puts("Welcome to CorBin ST ");
		lcd_puts("                   ");
		lcd_puts("Enter your code:");
		lcd_puts("    ");
		lcd_puts("        *---");
		
		password [0] = keypad_scan();					// Stock first digit of the password in position 0 of the array
		
		while(keypad_scan() != 12){}					// Control the way we push the button. 
														// If the user holds the push button, the micro will only read one pulsation
		
		counter++;										// Increment 'counter' to prove first digit has been introduced
		counter3++;										// Increment counter3 to validate previous 'if' condition	
	}
	
	else if((keypad_scan() != 12) & (counter == 1))	    // Condition used for prove second digit of the password has been introduced
	{
		lcd_gotoxy(0, 0);								// Display **-- 
		lcd_puts("Welcome to CorBin ST ");
		lcd_puts("                   ");
		lcd_puts("Enter your code:");
		lcd_puts("    ");
		lcd_puts("        **--");
		
		password [1] = keypad_scan();					// Stock second digit of the password in position 1 of the array
		
		while(keypad_scan() != 12){}					// Control the way we push the button.
														// If the user holds the push button, the micro will only read one pulsation		
		
		counter++;										// Increment 'counter' to prove second digit has been introduced
	}
	
	else if((keypad_scan() != 12) & (counter == 2))	    // Condition used for prove third digit of the password has been introduced
	{
		lcd_gotoxy(0, 0);								// Display ***-
		lcd_puts("Welcome to CorBin ST ");
		lcd_puts("                   ");
		lcd_puts("Enter your code:");
		lcd_puts("    ");
		lcd_puts("        ***-");
		
		password [2] = keypad_scan();					// Stock third digit of the password in position 2 of the array
		
		while(keypad_scan() != 12){}					// Control the way we push the button.
														// If the user holds the push button, the micro will only read one pulsation	
		
		counter++;										// Increment 'counter' to prove third digit has been introduced	
	}
	
	else if((keypad_scan() != 12) & (counter == 3))	    // Condition used for prove fourth digit of the password has been introduced
	{	
		lcd_gotoxy(0, 0);								// Display ****
		lcd_puts("Welcome to CorBin ST ");
		lcd_puts("                   ");
		lcd_puts("Enter your code:");
		lcd_puts("    ");
		lcd_puts("        ****");
		
		password [3] = keypad_scan();					// Stock fourth digit of the password in position 3 of the array
		
		while(keypad_scan() != 12){}					// Control the way we push the button.
														// If the user holds the push button, the micro will only read one pulsation		

		counter++;										// Increment 'counter' to prove fourth digit has been introduced
	}
	
	if(counter == 4)									// Condition used for prove the 4 digits of the password have been introduced
	{
		counter = 0;		
		
		// Compare if introduced password is equal to one of the correct passwords
		if((password[0]==password1[0]) & (password[1]==password1[1]) & (password[2]==password1[2]) & (password[3]==password1[3]))
		{	
			counter2++;									// Increment 'counter2' to prove it has introduced some of the correct passwords
			
			counter3 = 0;
			
			lcd_clrscr();								// Clear display and show welcome corresponding message
			lcd_puts("Welcome Mrs. Paula");
			
			uart_puts("OPEN DOOR - User: Mrs. Paula ");	// Welcome information message - UART
			uart_puts("\r\n");
		}
		
		// Compare if introduced password is equal to one of the correct passwords
		else if((password[0]==password2[0]) & (password[1]==password2[1]) & (password[2]==password2[2]) & (password[3]==password2[3]))
		{	
			counter2++;									// Increment 'counter2' to prove it has introduced some of the correct passwords
			
			counter3 = 0;
			
			lcd_clrscr();								// Clear display and show welcome corresponding message
			lcd_puts("Welcome Mr. Fryza");
			
			uart_puts("OPEN DOOR - User: Mr. Fryza ");	// Welcome information message - UART
			uart_puts("\r\n");
		}
		
		// Compare if introduced password is equal to one of the correct passwords
		else if((password[0]==password3[0]) & (password[1]==password3[1]) & (password[2]==password3[2]) & (password[3]==password3[3]))
		{	
			counter2++;									// Increment 'counter2' to prove it has introduced some of the correct passwords
			
			counter3 = 0;
			
			lcd_clrscr();								// Clear display and show welcome corresponding message
			lcd_puts("Welcome Mr. Cortes");
			
			uart_puts("OPEN DOOR - User: Mr. Cortes ");	// Welcome information message - UART
			uart_puts("\r\n");
		}
				 	
		// Compare if introduced password is equal to one of the correct password
		else if((password[0]==password4[0]) & (password[1]==password4[1]) & (password[2]==password4[2]) & (password[3]==password4[3]))
		{	
			counter2++;									// Increment 'counter2' to prove it has introduced some of the correct passwords
			
			counter3 = 0;
			
			lcd_clrscr();								// Clear display and show welcome corresponding message
			lcd_puts("Welcome Mr. Omar");
			
			uart_puts("OPEN DOOR - User: Mr. Omar ");	// Welcome information message - UART
			uart_puts("\r\n");
		}
					
		// Case in which the user has entered an incorrect password
		else
		{	
			counter3 = 0;			
			
			password [0] = 0;							// Put 0 value in position 0 of the array (restart)
			password [1] = 0;							// Put 0 value in position 1 of the array (restart)
			password [2] = 0;							// Put 0 value in position 2 of the array (restart)
			password [3] = 0;							// Put 0 value in position 3 of the array (restart)
			
			attempt++;									// Increment number of attempts (Maximum 3)
			
			GPIO_write_high(&PORTB, LED_RED);			// Turn on LED RED to show the user introduced wrong password
			
			if(attempt < 3)							    // Check if the number of wrong password is < 3 and in that case, display message
			{
				lcd_clrscr();
				lcd_puts("WRONG PASSWORD.     ");
				lcd_puts("Try again.");
								
				_delay_ms(2000);						// Wait 2 secs (2000 ms) and show new message
				
				lcd_clrscr();							// Clear display and show new message
				lcd_puts("Welcome to CorBin ST ");
				lcd_puts("                   ");
				lcd_puts("Enter your code:");
				lcd_puts("    ");
				lcd_puts("        ----");
			}	
					
			GPIO_write_low(&PORTB, LED_RED);			
		}		
	}
	
	if(counter2 == 1)									// Case in which the user has entered correct password
	{
		counter2 = 0;
		
		attempt = 0;
		
		//TIM0_overflow_16us();
		TIM0_overflow_interrupt_disable();				// Disable current ISR - TIM0_overflow_16us()
		
		//TIM1_overflow_1s();
		TIM1_overflow_interrupt_enable();				// Enable ISR - TIM1_overflow_1s()		
	}
	
	if(attempt == 3)									// Case in which the user has entered incorrect password for 3 times
	{
		attempt = 0;
		
		counter2 = 0;
		
		lcd_clrscr();									// Clear display and show new message
		lcd_puts("WRONG PASSWORD.     ");  
		lcd_puts("Try again in 5 secs.");
		
		//TIM0_overflow_16us();
		TIM0_overflow_interrupt_disable();				// Disable current ISR - TIM0_overflow_16us()
		
		//TIM2_overflow_16ms();
		TIM2_overflow_interrupt_enable();				// Enable ISR - TIM2_overflow_16ms()
	}			
	
}

/**
 * ISR starts when Timer/Counter1 overflows. 
 * Open the door, play a sound on the speaker and turn on LED GREEN.
 * This ISR will be reach only in the case the user introduced correct password */
ISR(TIMER1_OVF_vect)
{	
	static uint8_t counterDoor = 0;						// Counter to control the time the door remains open
	
	if(counterDoor == 0)
	{	
		GPIO_write_low(&PORTB, DOOR);					// Open the door (DOOR = '0') for 5 seconds
		GPIO_write_high(&PORTB, LED_GREEN);				// LED GREEN on because active HIGH for 5 seconds
		GPIO_write_high(&PORTB, SPEAKER);				// Play a sound on the SPEAKER for 5 seconds	
	}	
	
	if(counterDoor == 5)								// 5 seconds wait
	{
		counterDoor = 0;
		
		GPIO_write_high(&PORTB, DOOR);					// Close the door (DOOR = '1')
		GPIO_write_low(&PORTB, LED_GREEN);				// LED GREEN off because active HIGH
		GPIO_write_low(&PORTB, SPEAKER);				// Mute the SPEAKER
		
		TIM1_overflow_interrupt_disable();				// Disable current ISR - TIM1_overflow_1s()		
		TIM0_overflow_interrupt_enable();				// Enable again ISR - TIM0_overflow_16us()
		
		lcd_clrscr();									// Clear display and show new message
		lcd_puts("Welcome to CorBin ST ");
		lcd_puts("                   ");
		lcd_puts("Enter your code:");
		lcd_puts("    ");
		lcd_puts("        ----");				
		
		counterDoor = -1;								// Next time we enable the interrupt, it will be the value of 'counterDoor'
														// in order to increment in the following line and reach '0' value
	}
	
	counterDoor++;
}

/**
 * ISR starts when Timer/Counter2 overflows. 
 * Waiting state. Suspend the program for 5 seconds.
 * This ISR will be reach only in the case the user introduced incorrect password for 3 times */
ISR(TIMER2_OVF_vect)
{
	static uint16_t counterPassword = 0;				// Counter to control the time the program remains suspended	
														  
	if((counterPassword == 0) | (counterPassword == 62) | (counterPassword == 124) | (counterPassword == 186) | (counterPassword == 248))
	{									
		GPIO_toggle(&PORTB, LED_RED);					// Blink LED RED simulating alarm each 1 second (0; 62 * 16ms = 992ms ~ 1s)
		GPIO_toggle(&PORTB, SPEAKER);					// Alternate SPEAKER (on/off) simulating alarm each 1 second
	}
	
	if(counterPassword == 312)							// 312 * 16ms = 4992ms ~ 5s
	{
		counterPassword = 0;
		
		GPIO_write_low(&PORTB, LED_RED);				// LED RED off because active HIGH
		
		TIM2_overflow_interrupt_disable();				// Disable current ISR - TIM2_overflow_16ms()
		TIM0_overflow_interrupt_enable();				// Enable again ISR - TIM0_overflow_16us()
		
		lcd_clrscr();									// Clear display and show new message
		lcd_puts("Welcome to CorBin ST ");
		lcd_puts("                   ");
		lcd_puts("Enter your code:");
		lcd_puts("    ");
		lcd_puts("        ----");
		
		counterPassword = -1;							// Next time we enable the interrupt, it will be the value of 'counterPassword'
														// in order to increment in the following line and reach '0' value
	}
	
	counterPassword++;	
}

