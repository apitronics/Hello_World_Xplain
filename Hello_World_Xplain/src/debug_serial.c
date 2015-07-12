/*
* debug_serial.c
*
* Created: 5/21/2015 1:25:22 AM
*  Author: Colin
*/
#include "debug_serial.h"
#include <samd21_xplained_pro.h>



static struct usart_config config_master_usart;



void configure_debug_serial(void)
{
	usart_get_config_defaults(&config_master_usart);
	config_master_usart.baudrate    = 9600;
	config_master_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_master_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_master_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_master_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_master_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	
	while (usart_init(&usart_master_instance,
		EDBG_CDC_MODULE, &config_master_usart) != STATUS_OK) {
	}
	
	usart_enable(&usart_master_instance);
}

enum status_code print(const char *str){
	uint16_t strsize = 0;
	for (uint16_t i = 0; i<0xFFFF; i++)
	{
		if (str[i] == '\0')
		{
			strsize = i+1;
			break;
		}
	}
	return usart_write_buffer_wait(&usart_master_instance, str, strsize);
}


enum status_code println(const char *str){
	const char ln[]="\r\n";
	uint16_t strsize = 0;
	for (uint16_t i = 0; i<0xFFFF; i++)
	{
		if (str[i] == '\0')
		{
			strsize = i+1;
			break;
		}
	}
	usart_write_buffer_wait(&usart_master_instance, str, strsize);
	return usart_write_buffer_wait(&usart_master_instance, ln, sizeof(ln));
	
}


enum status_code printnum(int num){
	char num_output[12];
	itoa(num, &num_output, 10);
	return usart_write_buffer_wait(&usart_master_instance, num_output, sizeof(num_output));
}

enum status_code printlnnum(int num){
	char num_output[12];
	itoa(num, &num_output, 10);
	usart_write_buffer_wait(&usart_master_instance, num_output, sizeof(num_output));
	char ln[]="\r\n";
	return usart_write_buffer_wait(&usart_master_instance, ln, sizeof(ln));
}

enum status_code printflt(float numflt){
	//default assume 2 decimal places
	long num = (long)(numflt*100);
	char num_output[15] = {'\0'};
	itoa(num, &num_output, 10);
	for (uint8_t i = 2; i<(15-1); i++)
	{
		if (num_output[i] == '\0')
		{
			num_output[i+1] =	'\0';
			if(num<=9){
				num_output[i]	=	num_output[i-2]; //not really sure why this works
				num_output[i-1] =	'0';
			}
			else{
				num_output[i]	=	num_output[i-1];
				num_output[i-1] =	num_output[i-2];
			}
			num_output[i-2] =	'.';
			break;
		}
	}
	return usart_write_buffer_wait(&usart_master_instance, num_output, sizeof(num_output));
}

enum status_code printlnflt(float numflt){
	//default assume 2 decimal places
	long num = (long)(numflt*100);
	char num_output[15] = {'\0'};
	itoa(num, &num_output, 10);
	for (uint8_t i = 2; i<(15-1); i++)
	{
		if (num_output[i] == '\0')
		{
			num_output[i+1] =	'\0';
			if(num<=9){
				num_output[i]	=	num_output[i-2]; //not really sure why this works
				num_output[i-1] =	'0';
			}
			else{
				num_output[i]	=	num_output[i-1];
				num_output[i-1] =	num_output[i-2];
			}
			num_output[i-2] =	'.';
			break;
		}
	}
	usart_write_buffer_wait(&usart_master_instance, num_output, sizeof(num_output));
	char ln[]="\r\n";
	return usart_write_buffer_wait(&usart_master_instance, ln, sizeof(ln));
}

enum status_code printbin(uint16_t num){
	if(num < 256){
		return _printbin8(num);
	}
	
	char bin_str[17];
	bin_str[0] = '\0'; // we will reverse this string
	for (uint8_t i = 0; i<16; i++)
	{
		if ((num >> i) & 1)
		{
			bin_str[i+1] = '1';
		}
		else{
			bin_str[i+1] = '0';
		}
	}
	revstr(&bin_str, 17);
	
	char obin[]="b";
	usart_write_buffer_wait(&usart_master_instance, obin, sizeof(obin));
	return print(&bin_str);
}

enum status_code printlnbin(uint16_t num){
	if(num < 256){
		return _printlnbin8(num);
	}
	
	char bin_str[17];
	bin_str[0] = '\0'; // we will reverse this string
	for (uint8_t i = 0; i<16; i++)
	{
		if ((num >> i) & 1)
		{
			bin_str[i+1] = '1';
		}
		else{
			bin_str[i+1] = '0';
		}
	}
	revstr(&bin_str, 17);
	char obin[]="b";
	usart_write_buffer_wait(&usart_master_instance, obin, sizeof(obin));
	return println(&bin_str);
}

enum status_code _printbin8(uint8_t num){
	char bin_str[9];
	bin_str[0] = '\0'; // we will reverse this string
	for (uint8_t i = 0; i<9; i++)
	{
		if ((num >> i) & 1)
		{
			bin_str[i+1] = '1';
		}
		else{
			bin_str[i+1] = '0';
		}
	}
	revstr(&bin_str, 9);
	char obin[]="b";
	usart_write_buffer_wait(&usart_master_instance, obin, sizeof(obin));
	return print(&bin_str);
}

enum status_code _printlnbin8(uint8_t num){
	char bin_str[9];
	bin_str[0] = '\0'; // we will reverse this string
	for (uint8_t i = 0; i<9; i++)
	{
		if ((num >> i) & 1)
		{
			bin_str[i+1] = '1';
		}
		else{
			bin_str[i+1] = '0';
		}
	}
	revstr(&bin_str, 9);
	char obin[]="b";
	usart_write_buffer_wait(&usart_master_instance, obin, sizeof(obin));
	return println(&bin_str);
}


enum status_code writechar(char outbyte){
	char outstring[] = {outbyte, '\0'};
	return usart_write_buffer_wait(&usart_master_instance, outstring, sizeof(outstring));
}

void revstr(uint8_t *str, uint16_t length){
	length--;
	uint8_t temp;
	
	if(length==1){
		temp = str[0];
		str[0] = str[1];
		str[1] = temp;
		return;
	}
	for(uint16_t x = 0; x < (length/2); x++){
		temp = str[x];
		str[x]=str[length-x];
		str[length-x]=temp;
	}
	return;
}