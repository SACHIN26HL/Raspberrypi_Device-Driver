/********************************************
 * Simple LCD Driver
 * File : lcd_driver.c
 * Date : 17/12/2022
 * Author : 
 * *****************************************/

#include "lcd_driver.h"
#include "gpio_driver.h"
#include <linux/delay.h>



void lcd_and_gpio_pin_init(void)
{
	pr_info("lcd_and_gpio_pin_init function\n");

	gpio_pin_configuration(GPIO_RS, GPIO_DIR_OUT);
	//gpio_pin_configuration(GPIO_RW, GPIO_DIR_OUT);
	gpio_pin_configuration(GPIO_EN, GPIO_DIR_OUT);

	gpio_pin_configuration(GPIO_D4, GPIO_DIR_OUT);
	gpio_pin_configuration(GPIO_D5, GPIO_DIR_OUT);
	gpio_pin_configuration(GPIO_D6, GPIO_DIR_OUT);
	gpio_pin_configuration(GPIO_D7, GPIO_DIR_OUT);

}
void lcd_and_gpio_pin_free(void)
{
	gpio_pin_free(GPIO_RS);
	//gpio_pin_free(GPIO_RW);
	gpio_pin_free(GPIO_EN);

	gpio_pin_free(GPIO_D4);
	gpio_pin_free(GPIO_D5);
	gpio_pin_free(GPIO_D6);
	gpio_pin_free(GPIO_D6);
}

void lcd_init(void)
{
	pr_info("Lcd init function\n");
/*	// Initialise display
	lcd_byte(0x33,LCD_CMD) # 110011 Initialise
	lcd_byte(0x32,LCD_CMD) # 110010 Initialise
	lcd_byte(0x06,LCD_CMD) # 000110 Cursor move direction
	lcd_byte(0x0C,LCD_CMD) # 001100 Display On,Cursor Off, Blink Off
	lcd_byte(0x28,LCD_CMD) # 101000 Data length, number of lines, font size
	lcd_byte(0x01,LCD_CMD) # 000001 Clear display	
*/
	uint8_t command = 0;

	command = 0x33;
	lcd_send_command(command);

	command = 0x32;
	lcd_send_command(command);
	

	command = ENTRY_MODE;
	lcd_send_command(command);

	command = DISP_ON_CUR_BLINKING;
	lcd_send_command(command);

	command = LINE2_4BIT;
	lcd_send_command(command);
	
	command = CLEAR_DISP_SCR;
	lcd_send_command(command);
	msleep(100);

	command = 0x80;
	lcd_send_command(command);
	msleep(100);
	char *str = "     WelComE    ";
	lcd_print_string(str);
	pr_info("welcome string send\n");
}

void lcd_enable(void)
{
	gpio_write_value(GPIO_EN,LCD_ENABLE);
	msleep(2); //2ms delay
	gpio_write_value(GPIO_EN,LCD_DISABLE);

}

void lcd_send_command(uint8_t command)
{
	lcd_set_rs_command();
	//lcd_enable();

	//first send the msb nibble
	uint8_t command_msb;
	command_msb = ((command >> 4) & 0x0f);
	
	gpio_write_value(GPIO_D4, ((command_msb >> 0) & (0x01)));
	gpio_write_value(GPIO_D5, ((command_msb >> 1) & (0x01)));
	gpio_write_value(GPIO_D6, ((command_msb >> 2) & (0x01)));
	gpio_write_value(GPIO_D7, ((command_msb >> 3) & (0x01)));
	lcd_enable();
	
	uint8_t command_lsb;
	command_lsb = (command & 0x0f);

	gpio_write_value(GPIO_D4, ((command_lsb >> 0) & (0x01)));
	gpio_write_value(GPIO_D5, ((command_lsb >> 1) & (0x01)));
	gpio_write_value(GPIO_D6, ((command_lsb >> 2) & (0x01)));
	gpio_write_value(GPIO_D7, ((command_lsb >> 3) & (0x01)));
	lcd_enable();
	msleep(10);
}


void lcd_print_char(uint8_t data)
{
	lcd_set_rs_data();
	//lcd_enable();

	//first send the msb nibble data
	uint8_t data_msb;
	data_msb = ((data >> 4) & 0x0f);

	gpio_write_value(GPIO_D4, ((data_msb >> 0) & (0x01)));
	gpio_write_value(GPIO_D5, ((data_msb >> 1) & (0x01)));
	gpio_write_value(GPIO_D6, ((data_msb >> 2) & (0x01)));
	gpio_write_value(GPIO_D7, ((data_msb >> 3) & (0x01)));
	lcd_enable();

	//second send the lsb nibble data
	uint8_t data_lsb;
	data_lsb = (data & 0x0f);

	gpio_write_value(GPIO_D4, ((data_lsb >> 0) & (0x01)));
	gpio_write_value(GPIO_D5, ((data_lsb >> 1) & (0x01)));
	gpio_write_value(GPIO_D6, ((data_lsb >> 2) & (0x01)));
	gpio_write_value(GPIO_D7, ((data_lsb >> 3) & (0x01)));
	lcd_enable();
	msleep(100);
}


void lcd_print_string(char *message)
{
	pr_info("In lcd_print_string\n");
	int count =0;
	lcd_send_command(CLEAR_DISP_SCR);
	lcd_send_command(0x80); // line 1

	lcd_set_rs_data();
	do
	{
		lcd_print_char((uint8_t) *message);
		message++;
		count++;
		if(count == 16)
		{
			lcd_set_rs_command();
			lcd_send_command(0xC0); // line 2
			msleep(10);
			lcd_set_rs_data();
		}

	}while(*message != '\0');

}

void lcd_set_cursor(uint8_t row, uint8_t column)
{
}

void lcd_set_rs_command(void)
{
	/*RS = 0 instruction/command mode*/
	gpio_write_value(GPIO_RS, COMMAND_MODE);
}

void lcd_set_rs_data(void)
{
	/*RS = 1 data mode*/
	gpio_write_value(GPIO_RS, DATA_MODE);
}

