/*
 * wh2004.h
 *
 *  Created on: Feb 27, 2024
 *      Author: Chintan Mevada
 */

#ifndef WH2004_H_
#define WH2004_H_

#include "main.h"

#define cmd 0
#define data 1
#define start_col 0x80

#define RS 4
#define EN 5

/*
 * LCD Initialization Command
 */
#define cmd_clear_disp				0x01
#define cmd_8bit_1line				0x30
#define cmd_8bit_2line				0x38
#define cmd_4bit_1line				0x20
#define cmd_4bit_2line				0x28
#define cmd_entry_mode				0x06
#define cmd_disp_off_curs_off		0x08
#define cmd_disp_on_curs_on			0x0E
#define cmd_disp_on_curs_off		0x0C
#define cmd_disp_off_curs_blink		0x0F
#define cmd_shift_disp_left			0x18
#define cmd_shift_disp_right		0x1C
#define cmd_shift_curs_left			0x10
#define cmd_shift_curs_right		0x14

void pulse_en(void);
void lcd_write(uint8_t value, uint8_t mode);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(char *str);
void lcd_init(void);

#endif /* WH2004_H_ */
