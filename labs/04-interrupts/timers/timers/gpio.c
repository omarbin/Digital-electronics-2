/*
 * gpio.c
 *
 * Created: 10/13/2020 11:16:12 PM
 *  Author: piash
 */ 
/* Includes ----------------------------------------------------------*/
#include "gpio.h"

/* Function definitions ----------------------------------------------*/
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name | (1<<pin_num);
}
/*--------------------------------------------------------------------*/
/* GPIO_config_input_nopull */
void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name & ~(1<<pin_num);  // Data Direction Register
	*reg_name++;                    // Change pointer to Data Register
	*reg_name = *reg_name & ~(1<<pin_num);   // Data Register
}
/*--------------------------------------------------------------------*/
void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name & ~(1<<pin_num);  // Data Direction Register
	*reg_name++;                    // Change pointer to Data Register
	*reg_name = *reg_name | (1<<pin_num);   // Data Register
}

/*--------------------------------------------------------------------*/
void GPIO_write_low(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name & ~(1<<pin_num); //clear bit (and not)
}

/*--------------------------------------------------------------------*/
/* GPIO_write_high */
void GPIO_write_high(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name | (1<<pin_num); //set bit (or)
	
}

/*--------------------------------------------------------------------*/
/* GPIO_toggle */
void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name ^ (1<<pin_num); //toggle bit (xor)

}
/*--------------------------------------------------------------------*/
/* GPIO_read */
uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num)
{
	uint8_t result = 0;
	if (bit_is_clear(*reg_name, pin_num))
	{
		result = 1;
	}
	return result;
}
