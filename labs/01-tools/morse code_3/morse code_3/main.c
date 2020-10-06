/* Defines -----------------------------------------------------------
Omar Bin Rahman, BUT
Program that detects morse code by observing the time duration the LED is switched on for. 
DOT (.) for 3s 
Dash (-) for 5s 
Space ( ) for 7s //space means move to next letter
SHORT_DELAY for 1 second gaps in between morse codes   
*/
#define LED_GREEN   PC2     // AVR pin where green LED is connected
#define SHORT_DELAY_dot 3000      // Delay in miliseconds for DOT 
#define SHORT_DELAY_dash 5000     // for DASH
#define SHORT_DELAY_space 7000    // for SPACE
#define SHORT_DELAY     1000   // time for which the LED is off in between morse codes
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Variables ---------------------------------------------------------*/

/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
void dot(){
	PORTC = PORTC | (1<<LED_GREEN);
	_delay_ms(SHORT_DELAY_dot);
	PORTC = PORTC & ~(1<<LED_GREEN);
}

void dash(){
	PORTC = PORTC | (1<<LED_GREEN);
	_delay_ms(SHORT_DELAY_dash);
	PORTC = PORTC & ~(1<<LED_GREEN);
}

void space(){
	PORTC = PORTC | (1<<LED_GREEN);
	_delay_ms(SHORT_DELAY_space);
	PORTC = PORTC & ~(1<<LED_GREEN);
}

      //MORSE CODE FOR DE2: -.. . ..---
	  
int main()
{
	int i; // integer used in for loop. 

    // Set pin as output in Data Direction Register
    // DDRC = DDRC or 0000 0100
    DDRC = DDRC | (1<<LED_GREEN);

    // Set pin LOW in Data Register (LED off)
    // PORTC = PORTC and 1111 1011
    PORTC = PORTC & ~(1<<LED_GREEN);

    // Infinite loop
    while (1)
    {
	dash();
	_delay_ms(SHORT_DELAY);

for (i=0;i<2;i++){
	dot();
	_delay_ms(SHORT_DELAY);
}
	space();
	_delay_ms(SHORT_DELAY);

	dot();
	_delay_ms(SHORT_DELAY);

	space();
	_delay_ms(SHORT_DELAY);

for (i=0;i<2;i++){
	dot();
	_delay_ms(SHORT_DELAY);
}
for (i=0;i<3;i++){
	dash();
	_delay_ms(SHORT_DELAY);
}
    }
    // Will never reach this
    return 0;
}


