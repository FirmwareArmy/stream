#pragma once

#include <textstream.h>

class OutputStream : public TextStream
{
public:
	OutputStream() ;

	void put_byte(uint8_t c) ;

	typedef void (*output_callback_t)(uint8_t c) ;
	void set_output_callback(output_callback_t print_char) ;

protected:
	output_callback_t _print_char ;
} ;
