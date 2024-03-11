/*
 * wh2004.c
 *
 *  Created on: Feb 27, 2024
 *      Author: Chintan Mevada
 */

#include "wh2004.h"

void pulse_en(void){

	GPIOC->ODR |= (1<<EN);
	HAL_Delay(1);
	GPIOC->ODR &= ~(1<<EN);
	HAL_Delay(1);
}

void lcd_write(uint8_t value, uint8_t mode){

	if(mode == cmd){
		GPIOC->ODR &= ~(1<<RS); // RS = 0 for command
	}else{
		GPIOC->ODR |= (1<<RS); // RS = 1 for data
	}

	GPIOA->ODR = (value & 0xF0); // send upper nibble
	pulse_en();
	GPIOA->ODR = ((value & 0x0F)<<4); // send lower nibble
    pulse_en();
}

void lcd_set_cursor(uint8_t row, uint8_t col){

	const uint8_t row_offset[4] = {0x00, 0x40, 0x14, 0x54};
	lcd_write(start_col | (col + row_offset[row]), cmd);
	HAL_Delay(1);
}

void lcd_print(char *str){

	while(*str != '\0'){
		lcd_write(*str, data);
		str++;
	}
}

void lcd_init(void){

    HAL_Delay(1);
    lcd_write(0x33, cmd); // Initializing sequence 1
    HAL_Delay(1);
    lcd_write(0x32, cmd); // Initializing sequence 2
    HAL_Delay(1);
    lcd_write(cmd_4bit_2line, cmd); // 4-Bit, 2-Line, 5x7-Dots
    HAL_Delay(1);
    lcd_write(cmd_disp_on_curs_off, cmd); // Display-On, Cursor-off
    HAL_Delay(1);
    lcd_write(cmd_clear_disp, cmd); // Clear Display
    HAL_Delay(1);
    lcd_write(cmd_entry_mode, cmd); // Entry mode
    HAL_Delay(1);
    lcd_set_cursor(0,0); // set cusor 0-line at 0 Position
}
