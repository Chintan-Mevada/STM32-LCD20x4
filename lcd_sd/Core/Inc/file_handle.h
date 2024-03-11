/*
 * file_handle.h
 *
 *  Created on: Feb 28, 2024
 *      Author: PC
 */

#ifndef INC_FILE_HANDLE_H_
#define INC_FILE_HANDLE_H_

#include "fatfs.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"
#include "wh2004.h"

#define max_file 256
#define MAX_FILES_PER_PAGE 4
#define data_size 25600

#define sw1_read HAL_GPIO_ReadPin(ext_sw_1_GPIO_Port, ext_sw_1_Pin)
#define sw2_read HAL_GPIO_ReadPin(ext_sw_2_GPIO_Port, ext_sw_2_Pin)
#define sw3_read HAL_GPIO_ReadPin(ext_sw_3_GPIO_Port, ext_sw_3_Pin)
#define sw4_read HAL_GPIO_ReadPin(ext_sw_4_GPIO_Port, ext_sw_4_Pin)


FRESULT sd_mount(void);
FRESULT sd_unmount(void);
FRESULT usb_mount(void);
FRESULT usb_unmount(void);
FRESULT scan_file(char* pat);
FRESULT scan_sd(char* pat);
FRESULT scan_usb(char* pat);
void update_display(void);
void menu_display(void);
void copy_selected_file(const char* source_file, const char* destination_file);
bool TransferDataBlockWise(const char *source_file_name, const char *destination_file_name);

/* Button Handler function declaration */
void button_up_handler(void);
void button_down_handler(void);
void button_select_handler(void);
void button_menu_handler(void);

#endif /* INC_FILE_HANDLE_H_ */
