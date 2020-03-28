#include <outputstream.h>

OutputStream::OutputStream()
	: TextStream()
{
}

void OutputStream::put_byte(uint8_t c)
{
	if(_print_char)
		_print_char(c) ;
}

void OutputStream::set_output_callback(output_callback_t print_char)
{
	_print_char = print_char ;
}
