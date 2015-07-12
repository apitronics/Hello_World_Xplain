/*
 * debug_serial.h
 *
 * Created: 5/21/2015 1:25:38 AM
 *  Author: Colin
 */ 
#include <compiler.h>



#if USART_CALLBACK_MODE == true
#  include <sercom_interrupt.h>
#endif


#ifndef DEBUG_SERIAL_H_
#define DEBUG_SERIAL_H_


#include <usart.h>
#include <compiler.h>
#include <sercom.h>
#include <pinmux.h>

#include <itoa.h>

struct usart_module usart_master_instance;


void configure_debug_serial( void );
enum status_code print(const char *str);
enum status_code println(const char *str);
enum status_code printnum(int num);
enum status_code printlnnum(int num);
enum status_code writechar(char outbyte);




enum status_code printbin(uint16_t num);
enum status_code _printbin8(uint8_t num);
enum status_code printlnbin(uint16_t num);
enum status_code _printlnbin8(uint8_t num);

enum status_code printflt(float numflt);
enum status_code printlnflt(float numflt);

void revstr(uint8_t *str, uint16_t length);



#endif /* DEBUG_SERIAL_H_ */