/*
 * file_handle.c
 *
 *  Created on: Feb 28, 2024
 *      Author: Chintan Mevada
 */

#include "file_handle.h"
#include "usb_host.h"

extern ApplicationTypeDef Appli_state;

FATFS sdfs, usbfs;
FIL sd_file, usb_file;
FRESULT fresult;
FILINFO sd_info, usb_info;
char file1[max_file][13];
char menu[2][8] = { "SD CARD", "USB" };
char receive_data[data_size];
char source[16], dest[16];
char menu_up_down = 0;
UINT bytes_read, bytes_write;
uint8_t file_count = 0, rows = 0, selected_file_index = 0, menu_index = 0,
		current_page = 0, i;
extern uint8_t last_state_pin1, last_state_pin2;
extern char sd, usb, c;

UINT src_file_size, dest_file_size;

FRESULT sd_mount(void) {
	fresult = f_mount(&sdfs, SDPath, 0);
	return fresult;
}

FRESULT sd_unmount(void) {
	fresult = f_mount(NULL, SDPath, 0);
	return fresult;
}

FRESULT usb_mount(void) {
	fresult = f_mount(&usbfs, USBHPath, 0);
	return fresult;
}

FRESULT usb_unmount(void) {
	fresult = f_mount(NULL, USBHPath, 0);
	return fresult;
}

FRESULT scan_sd(char *pat) {

	DIR dir;
	int found = 0, i = 0;
	for (int k = 0; k < max_file; k++) {
		memset(file1[k], '\0', 13);
	}
	file_count = 0;
	fresult = f_opendir(&dir, pat);  // Open the directory
	if (fresult == FR_OK) {
		while (1) {
			fresult = f_readdir(&dir, &sd_info);  //  Read a directory item
			if (fresult
					!= FR_OK|| sd_info.fname[0] == 0 || file_count >= max_file) {
				break;  //Break on error, end of dir, or max_file reached
			}
			if (sd_info.fattrib & AM_DIR)  //It is a directory
			{
				if ((strcmp("SYSTEM~1", sd_info.fname))) {
					continue; // Skip directories not matching "SYSTEM~1"
				}
			} else // It is a file
			{
				if (strcmp(file1[i], sd_info.fname) == 0) {
					found = 1;
					i++;
					continue; // skip if file name is already exist
				} else {
					found = 0;
				}
				if (!(found)) {
					strncpy(file1[file_count], sd_info.fname, 13); // Copy filename to file1
					file_count++; // Increment file count
				}
			}
		}
		f_closedir(&dir); //  Close the directory

		lcd_write(cmd_clear_disp, cmd); // Clear display
		update_display();
	}
	return fresult;
}

FRESULT scan_usb(char *pat) {

	DIR dir;
	int found = 0, i = 0;
	for (int k = 0; k < max_file; k++) {
		memset(file1[k], '\0', 13);
	}
	file_count = 0;
	fresult = f_opendir(&dir, pat);  // Open the directory
	if (fresult == FR_OK) {
		while (1) {
			fresult = f_readdir(&dir, &usb_info);  //  Read a directory item
			if (fresult
					!= FR_OK|| usb_info.fname[0] == 0 || file_count >= max_file) {
				break;  //Break on error, end of dir, or max_file reached
			}
			if (usb_info.fattrib & AM_DIR)  //It is a directory
			{
				if ((strcmp("SYSTEM~1", usb_info.fname))) {
					continue; // Skip directories not matching "SYSTEM~1"
				}
			} else // It is a file
			{
				if (strcmp(file1[i], usb_info.fname) == 0) {
					found = 1;
					i++;
					continue; // skip if file name is already exist
				} else {
					found = 0;
				}
				if (!(found)) {
					strncpy(file1[file_count], usb_info.fname, 13); // Copy filename to file1
					file_count++; // Increment file count
				}
			}
		}
		f_closedir(&dir); //  Close the directory

		lcd_write(cmd_clear_disp, cmd); // Clear display
		update_display();
	}
	return fresult;
}

/*
 FRESULT scan_file(char *pat) {
 DIR dir;
 char path[4];

 memset(path, '\0', sizeof(path)); // clear buffer
 sprintf(path, "%s", pat);
 fresult = f_opendir(&dir, path); // Open the directory
 if (fresult == FR_OK) {
 for (;;) {
 fresult = f_readdir(&dir, &sd_info); // Read a directory item
 if (fresult != FR_OK || sd_info.fname[0] == 0 || file_count >= max_file) {
 break; // Break on error or end of dir
 }
 if (sd_info.fattrib & AM_DIR) // It is a directory
 {
 if ((strcmp("SYSTEM~1 ", sd_info.fname))) {
 continue;
 }
 } else // It is a file
 {
 strncpy(file1[file_count], sd_info.fname, 13);
 file_count++;
 }
 }
 f_closedir(&dir);
 sd_unmount();


 }
 return fresult;
 }
 */

void update_display(void) {
	uint8_t start_index = current_page * MAX_FILES_PER_PAGE;
	uint8_t end_index = start_index + MAX_FILES_PER_PAGE;
	for (uint8_t i = start_index; i < end_index && i < file_count; i++) {
		uint8_t display_index = i - start_index;
		lcd_set_cursor(display_index, 0); // Set cursor position for next line
		if (i == selected_file_index) {
			lcd_print("~ "); // Mark selected file with asterisk
		} else {
			lcd_print("  ");
		}
		lcd_print(file1[i]); // Send filename to LCD
	}
}

void menu_display(void) {
	uint8_t start_index = 0;
	uint8_t end_index = 2;
	for (uint8_t i = start_index; i < end_index; i++) {
		uint8_t display_index = i - start_index;
		lcd_set_cursor(display_index, 0); // Set cursor position for next line
		/*if (selected_file_index >= 2) {
			menu_index = 0;
		}*/
		if (i == menu_index) {
			lcd_print("~ "); // Mark selected file with asterisk
		} else {
			lcd_print("  ");
		}
		lcd_print(menu[i]); // Send filename to LCD
	}
}

/*
 void copy_selected_file(const char *source_file, const char *destination_file) {

 const char *input_file = source_file;
 const char *output_file = destination_file;

 // Mount sd card
 sd_mount();

 // Read File
 fresult = f_open(&sd_file, input_file, FA_READ | FA_OPEN_ALWAYS);
 if (fresult == FR_OK) {
 fresult = f_read(&sd_file, receive_data, sizeof(receive_data),(UINT*) bytes_read);
 if (fresult == FR_OK) {
 f_close(&sd_file);
 }
 }
 fresult = f_open(&sd_file, output_file, FA_WRITE | FA_OPEN_ALWAYS);
 if (fresult == FR_OK) {
 fresult = f_write(&sd_file, receive_data, strlen(receive_data),(UINT*) bytes_write);
 if (fresult == FR_OK) {
 lcd_write(cmd_clear_disp, cmd);
 lcd_set_cursor(0, 4);
 lcd_print(file1[selected_file_index]);
 lcd_set_cursor(1, 3);
 lcd_print("FILE COPY 100%");
 f_close(&sd_file);
 }
 }
 sd_unmount();
 }
 */

bool TransferDataBlockWise(const char *source_file_name,
		const char *destination_file_name) {
	int result = false;
	// Open the source file for reading
	fresult = f_open(&sd_file, (const char*) source_file_name,
			FA_READ | FA_OPEN_ALWAYS);
	// Open the destination file for writing
	fresult = f_open(&usb_file, (const char*) destination_file_name,
			FA_WRITE | FA_OPEN_ALWAYS);

	// Read and write data block by block
	src_file_size = f_size(&sd_file);
	UINT total_bytes = src_file_size;

	while (total_bytes > 0) {
		// Read data from the source file
		if (f_read(&sd_file, receive_data, data_size, &bytes_read) != FR_OK)
			;

		// Check for read error or end of file
		if (bytes_read <= 0) {
			break;
		}

		// Write data to the destination file
		if (f_write(&usb_file, receive_data, bytes_read, &bytes_write) != FR_OK)
			;

		// Check for write error
		if (f_error(&usb_file) != FR_OK) {
			// Handle write error
			break;
		}

		total_bytes -= bytes_read;
		if (total_bytes == 0) {
			dest_file_size = f_size(&usb_file);
		}

	}

	if (src_file_size == dest_file_size) {
		result = true;
	} else {
		if ((fresult = f_unlink(destination_file_name)) == FR_OK) {
			result = false;
		}
	}
	// Close the files
	f_close(&sd_file);
	f_close(&usb_file);
	return result;
}

/* Button Handler Function Defination */
void button_up_handler(void) {
	if (sd == 1 || usb == 1) {
		if (selected_file_index > 0) {
			selected_file_index--;
			if (selected_file_index < current_page * MAX_FILES_PER_PAGE) {
				current_page--;
				lcd_write(cmd_clear_disp, cmd);
			}
			update_display();
		}
	} else {
		if (menu_up_down == 1) {
			if (menu_index > 0) {
				menu_index--;
				lcd_write(cmd_clear_disp, cmd);
			}
			menu_display();
			menu_up_down = 0;
		}
	}
}

void button_down_handler(void) {
	if (sd == 1 || usb == 1) {
		if (selected_file_index < file_count - 1) {
			selected_file_index++;
			if (selected_file_index >= (current_page + 1) * MAX_FILES_PER_PAGE) {
				current_page++;
				lcd_write(cmd_clear_disp, cmd);
			}
			update_display();
		}
	}else{
		if(c == 1){
			if (menu_up_down == 0) {
				if (menu_index == 0) {
					menu_index++;
					lcd_write(cmd_clear_disp, cmd);
				}
				menu_display();
				menu_up_down = 1;
			}
		}
	}
}

void button_select_handler(void) {
	// Clear Buffer
	memset(source, '\0', sizeof(source));
	memset(dest, '\0', sizeof(dest));
	// Copy Usb and Sd path
	sprintf(source, SDPath, 4);
	sprintf(dest, USBHPath, 4);
	// Concat two string
	strcat(source, file1[selected_file_index]);
	strcat(dest, file1[selected_file_index]);
	// Call transfer function
	if (TransferDataBlockWise(source, dest) == true) {
		// Clear Buffer
		memset(source, '\0', sizeof(source));
		memset(dest, '\0', sizeof(dest));
		// Copy Usb and Sd path
		sprintf(source, "%uB", src_file_size);
		sprintf(dest, "%uB", dest_file_size);
		lcd_write(cmd_clear_disp, cmd);
		lcd_set_cursor(0, 0);
		lcd_print(file1[selected_file_index]);
		lcd_set_cursor(1, 0);
		lcd_print("FILE Copy 100%");
		lcd_set_cursor(2, 0);
		lcd_print("Src Size:");
		lcd_set_cursor(2, 10);
		lcd_print(source);
		lcd_set_cursor(3, 0);
		lcd_print("Det Size:");
		lcd_set_cursor(3, 10);
		lcd_print(dest);

		c = 1;
	}
}

void button_menu_handler(void) {
	lcd_write(cmd_clear_disp, cmd);
	menu_display();
}

