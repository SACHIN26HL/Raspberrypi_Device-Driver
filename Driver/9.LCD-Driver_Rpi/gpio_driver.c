/**************************************
 *
 * simple LCD Driver
 * FIle : gpio_driver.c
 * Date : 18/12/2022
 * Author : 
 * ****************************************/
#include "gpio_driver.h"
#include "lcd_driver.h"

#include <linux/gpio.h>

void gpio_pin_configuration(int GPIO_pin, int direction)
{
	pr_info("gpio pin : %d\n", GPIO_pin);
	//Checking the GPIO is valid or not
	if(gpio_is_valid(GPIO_pin) == 0){
		pr_info("GPIO %d is not valid\n", GPIO_pin);
	}

	//Requesting the GPIO
	if(gpio_request(GPIO_pin,"GPIO_21") < 0){

	}

	//configure the GPIO as output
	gpio_direction_output(GPIO_pin, 0);

//	r_gpio:
//  	gpio_free(GPIO_pin);

}


void gpio_write_value(int GPIO_pin_no, int value)
{
	pr_info("gpio write pin : %d  value : %d\n", GPIO_pin_no, value);
	//set the GPIO pin value is HIGH/LOW
	gpio_set_value(GPIO_pin_no, value);


}


void gpio_pin_free(int gpio_pin)
{
	//free gpio pin
	gpio_free(gpio_pin);
}
