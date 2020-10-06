/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PC2     // AVR pin where green LED is connected
#define SHORT_DELAY_dot 3000      // Delay in miliseconds
#define SHORT_DELAY_dash 6000
#define SHORT_DELAY_space 9000
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include <stdio.h>

/* Variables ---------------------------------------------------------*/
int i;

/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
void dot(){
	_delay_ms(SHORT_DELAY_dot);
}

void dash(){
	_delay_ms(SHORT_DELAY_dash);
}

void space(){
	_delay_ms(SHORT_DELAY_space);
}
/**
        -.. . ..---
 * Toggle one LED and use the function from the delay library.
 */
int main()
{

    // Set pin as output in Data Direction Register
    // DDRC = DDRC or 0000 0100
    DDRC = DDRC | (1<<LED_GREEN);

    // Set pin LOW in Data Register (LED off)
    // PORTC = PORTC and 1111 1011
    PORTC = PORTC & ~(1<<LED_GREEN);

    // Infinite loop
    while (1)
    {
for (i=0;i<1;i++){
	void dash();
}
for (i=0;i<2;i++){
	void dot();
}
for (i=0;i<1;i++){
	void space();
}
for (i=0;i<1;i++){
	void dot();
}
for (i=0;i<1;i++){
	void space();
}
for (i=0;i<2;i++){
	void dot();
}
for (i=0;i<3;i++){
	void dash();
}

        // Invert LED in Data Register
        // PORTC = PORTC xor 0000 0100
        PORTC = PORTC ^ (1<<LED_GREEN);
    }

    // Will never reach this
    return 0;
}
