#include "jtag.h"

#include <board.h>

OutputStream jtag_stream ;

extern "C" {
	void print_char(uint8_t c) ;
}

void enable_jtag()
{
	// init debug uart
	jtag_uart.enable(true) ;

	jtag_stream.set_output_callback(print_char) ;
}

void disable_jtag()
{
	jtag_uart.enable(false) ;
}

extern "C" {
	void print_char(uint8_t c)
	{
		jtag_uart.write(c) ;
	}
}
