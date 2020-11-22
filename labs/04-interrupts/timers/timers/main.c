/***********************************************************************
 * 
 * Control LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_RED  PB5
#define LED_BLUE  PB4
#define LED_GREEN  PB3

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle one LED
 * on the Multi-function shield using the internal 8- or 16-bit 
 * Timer/Counter.
 */
int main(void)
{
    /* Configuration of LED(s) */
    GPIO_config_output(&DDRB, LED_RED);
    GPIO_write_low(&PORTB, LED_RED);
	
	/* Configuration of LED(s) */
	GPIO_config_output(&DDRB, LED_BLUE);
	GPIO_write_low(&PORTB, LED_BLUE);
	
	/* Configuration of LED(s) */
	GPIO_config_output(&DDRB, LED_GREEN);
	GPIO_write_low(&PORTB, LED_GREEN);

    /* Configuration of 8-bit Timer/Counter0
     * Set prescaler and enable overflow interrupt */
    TIM0_overflow_16us();
    TIM0_overflow_interrupt_enable();

    /* Configuration of 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
    TIM1_overflow_4s();
    TIM1_overflow_interrupt_enable();
	
	 /* Configuration of 8-bit Timer/Counter2
     * Set prescaler and enable overflow interrupt */
     TIM2_overflow_16ms();
     TIM2_overflow_interrupt_enable();

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
 * ISR starts when Timer/Counter0 overflows. Toggle D2 LED on 
 * Multi-function shield. */
ISR(TIMER0_OVF_vect)
{
	// WRITE YOUR CODE HERE
	GPIO_toggle(&PORTB,LED_RED);
}

/**
 * ISR starts when Timer/Counter1 overflows. Toggle D1 LED on 
 * Multi-function shield. */
ISR(TIMER1_OVF_vect)
{
    // WRITE YOUR CODE HERE
	GPIO_toggle(&PORTB,LED_BLUE);
}

/**
 * ISR starts when Timer/Counter2 overflows. Toggle D3 LED on 
 * Multi-function shield. */
ISR(TIMER2_OVF_vect)
{
	// WRITE YOUR CODE HERE
	GPIO_toggle(&PORTB,LED_GREEN);
}
