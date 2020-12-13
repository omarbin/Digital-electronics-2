/*
 * gpio.c
 *
 * Created: 10/13/2020 11:16:12 PM
 *  Author: piash
 */ 
/* Includes ----------------------------------------------------------*/
#include "gpio.h"

/* Function definitions ----------------------------------------------*/
/* Output */
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name | (1<<pin_num);
}
/*--------------------------------------------------------------------*/
/* input_nopull */
void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name & ~(1<<pin_num);             // Data Direction Register
	*reg_name++;                                       // Change pointer to Data Register
	*reg_name = *reg_name & ~(1<<pin_num);             // Data Register
}
/*--------------------------------------------------------------------*/
/* input_pullup */
void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name & ~(1<<pin_num);            // Data Direction Register
	*reg_name++;                                      // Change pointer to Data Register
	*reg_name = *reg_name | (1<<pin_num);             // Data Register
}

/*--------------------------------------------------------------------*/
/* write_low */
void GPIO_write_low(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name & ~(1<<pin_num);            //clear bit (and not)
}

/*--------------------------------------------------------------------*/
/* write_high */
void GPIO_write_high(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name | (1<<pin_num);             //set bit (or)
	
}

/*--------------------------------------------------------------------*/
/* toggle */
void GPIO_toggle(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name ^ (1<<pin_num);            //toggle bit (xor)

}
/*--------------------------------------------------------------------*/
/* read */
uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num)
{
	uint8_t result = 0;
	if (bit_is_clear(*reg_name, pin_num))           //works when push button is ON
	{
		result = 1;
	}
	return result;
}
