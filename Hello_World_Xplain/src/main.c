/**
 * \file
 *
 * \brief SAM USART Quick Start
 *
 * Copyright (C) 2012-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <debug_serial.h>


int main(void)
{
	system_init();
	delay_init();
	

	configure_debug_serial();
	
	
	println("hello world");

	for (uint16_t i = 1; i != 0; i=i<<1)
	{
		printlnnum(i);
		delay_ms(100);

	}
	
	for (int16_t i = 1; i != 0; i=i<<1)
	{
		printnum(i);
		print(", ");
		delay_ms(100);

	}
	
	println("");
	
	for (long i = 1; i != 0; i=i<<1)
	{
		printlnnum(i);
		delay_ms(100);

	}
	
	for (uint16_t i = 1; i<= 0xFFFF; i = i*2+1)
	{
		printlnbin(i);
		delay_ms(100);
		if (i >= 0xFFFF) break;
	}

	println("fun with floats");

	print(" 0.091->");
	printlnflt(0.091);
	print(" ");
	print(" 0.91->");
	printlnflt(0.91);
	print(" ");
	print(" 9.10->");
	printlnflt(9.10);
	print(" ");
	print(" 91.0->");
	printlnflt(91.0);
	print(" ");
	print(" 910.0->");
	printlnflt(910.0);
	print(" ");
	print(" 9100.0->");
	printlnflt(9100.0);
	print(" ");
	print(" 91000.0->");
	printlnflt(91000.0);
	print(" ");
	print(" 910000.0->");
	printlnflt(910000.0);
	println("");
	
	char bigA = 65;
	char smlL = 108;
	writechar(bigA);
	writechar(smlL);
	writechar(smlL);
	
	
}
