/*
 * keypad.h
 *
 * Created: 27/11/2020 20:21:51
 *  Author: Guillermo Cortés Orellana & Omar Bin Rahman 
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

/***********************************************************************
 * 
 * KEYPAD library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) Guillermo Cortés Orellana & Omar Bin Rahman
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/**
 * @file  keypad.h
 * @brief KEYPAD library for AVR-GCC.
 *
 * @details
 * The library contains functions for controlling keypad
 *
 * @note
 * Based on AVR Libc Reference Manual. Tested on ATmega328P (Arduino Uno),
 * 16 MHz, AVR 8-bit Toolchain 3.6.2.
 * 
 * @copyright (c) 2019-2020 Guillermo Cortés Orellana & Omar Bin Rahman
 * This work is licensed under the terms of the MIT license.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>

/* Defines -----------------------------------------------------------*/
/**
 * @brief - Defines the interface of rows and columns of the keypad
 *
 */
#define ROW1 PC0
#define ROW2 PC1
#define ROW3 PC2
#define ROW4 PC3

#define COL1 PD3
#define COL2 PC5
#define COL3 PC4

/* Function prototypes -----------------------------------------------*/
/**
 * @brief - Set different rows and column of the keypad as output and
 *			input respectively
 *			
 */
void keypad_setup_pin(void);

/**
 * @brief - Get which key is pushed
 *
 * @return uint8_t - Control value (1 to 11) which shows which key is pushed
 *			
 */
uint8_t keypad_scan(void);


#endif /* KEYPAD_H_ */