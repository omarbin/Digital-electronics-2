/* Defines -----------------------------------------------------------
Omar Bin Rahman, BUT 
5 LED lights when the push button is enable in Knight rider style.
*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected 
#define LED_RED     PC0     // AVR pin where red LED is connected
#define LED_BLUE    PC2     // AVR pin where blue LED is connected
#define LED_YELLOW  PC3     // AVR pin where yellow LED is connected
#define LED_ORANGE  PC4     // AVR pin where orange LED is connected
#define BTN         PD0     // AVR pin where push button is connected
#define BLINK_DELAY 200    // delay in ms
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
    /* GREEN LED */
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_GREEN);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_GREEN);

    /* RED, BLUE, YELLOW, ORANGE LED */
    // WRITE YOUR CODE HERE
	    DDRC = DDRC | (1<<LED_RED) | (1<<LED_BLUE) | (1<<LED_YELLOW) | (1<<LED_ORANGE); 
	    PORTC = PORTC | (1<<LED_RED); // Turn OFF
	    PORTC = PORTC | (1<<LED_BLUE); // Turn OFF
	    PORTC = PORTC | (1<<LED_YELLOW); // Turn OFF
	    PORTC = PORTC | (1<<LED_ORANGE); // Turn OFF

/* PUSH BUTTON */ 
        DDRD = DDRD & ~(1<<BTN); //input 
		PORTD = PORTD | (1<<BTN); //enable internal pull-up
    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        // WRITE YOUR CODE HERE
		if (bit_is_set(PIND, BTN)) //set instead of clear
		{
			PORTB = PORTB ^ (1<<LED_GREEN); // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTB = PORTB & ~(1<<LED_GREEN); // TURN OFF
			
			PORTC = PORTC ^ (1<<LED_RED);    // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | (1<<LED_RED);   // TURN OFF
			
			PORTC = PORTC ^ (1<<LED_BLUE);   // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | (1<<LED_BLUE);   // TURN OFF
			
			PORTC = PORTC ^ (1<<LED_YELLOW);   // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | (1<<LED_YELLOW);   // TURN OFF
			
			PORTC = PORTC ^ (1<<LED_ORANGE);   // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | (1<<LED_ORANGE);   // TURN OFF
			
			//now starts to go backwards
			PORTC = PORTC ^ (1<<LED_YELLOW);   // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | (1<<LED_YELLOW);   // TURN OFF
			PORTC = PORTC ^ (1<<LED_BLUE);   // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | (1<<LED_BLUE);   // TURN OFF
			PORTC = PORTC ^ (1<<LED_RED);    // TURN ON
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | (1<<LED_RED);   // TURN OFF
		}

    }

    // Will never reach this
    return 0;
}