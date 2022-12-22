/*********************************************************
 *
 * Simple LCD Driver using Raspbery  pi
 * FILE : gpio_driver.h
 * Date : 17/12/2022
 *
 * ****************************************************/

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H
#include <linux/gpio.h>

#define HIGH_VALUE 1
#define LOW_VALUE 0


#define GPIO_DIR_IN 0
#define GPIO_DIR_OUT 1

#define GPIO_HIGH_VALUE 1
#define GPIO_LOW_VALUE 0

void gpio_pin_configuration(int gpio_pin, int direction);
void gpio_write_value(int gpio_pin_no, int value);
void gpio_pin_free(int gpio_pin);

#endif
