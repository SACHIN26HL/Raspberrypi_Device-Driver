/**********************************************
 *
 * Lcd Simple Driver Raspberry pi
 * File :lcd_driver.h
 * Author: --
 * Date : 17/12/2022
 *
 ********************************************/

#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "gpio_driver.h"

#define HIGH 1
#define LOW 0

/*Raspberrypi GPIO Pin used to connect with LCD Display */

#define GPIO_RS 7
#define GPIO_RW 
#define GPIO_EN 8

/*Lcd data line matching with LCD*/
#define GPIO_D0
#define GPIO_D1
#define GPIO_D2
#define GPIO_D3
#define GPIO_D4 25
#define GPIO_D5 24 
#define GPIO_D6 23
#define GPIO_D7 18

/*=========Regiter Selection ==========*/
/* Instruction Reg and Data Reg        */

#define COMMAND_MODE 0     
#define DATA_MODE 1	

/**********LCD Commands*****************/
/*    LHD162A  LCD Display             */

#define CLEAR_DISP_SCR 0x01

/* Function set  8bit line 5x7 Dots*/
#define LINE1_8BIT 0x30
#define LINE2_8BIT 0x38

/* Function set 4 bit line 5x7 Dots*/
#define LINE1_4BIT 0x20
#define LINE2_4BIT 0x28

#define ENTRY_MODE 0x06
#define LCD_ENABLE 1
#define LCD_DISABLE 0

#define DISP_OFF_CUR_OFF 0x08
#define DISP_ON_CUR_ON 0x0E
#define DISP_ON_CUR_OFF 0x0C
#define DISP_ON_CUR_BLINKING 0x0F

#define SHIFT_ENTIRE_DIS_LEFT 0x18
#define SHIFT_ENTIRE_DIS_RIGHT 0x1C
#define MOVE_CUR_LEFT_ONE_CHAR 0x10
#define MOVE_CUR_RIGHT_ONE_CHAR 0x14

#define FORCE_CUR_BEG_1ST_ROW 0x80
#define FORCE_CUR_BEG_2ND_ROW 0xC0

void lcd_and_gpio_pin_init(void);
void lcd_and_gpio_pin_free(void);
void lcd_init(void);
void lcd_enable(void);
void lcd_send_command(uint8_t command);
void lcd_print_char(uint8_t data);
void lcd_print_string(char *message);
void lcd_set_cursor(uint8_t row, uint8_t column);
void lcd_set_rs_command(void);
void lcd_set_rs_data(void);


#endif








