#pragma once

#include <textstream.h>
#include <stdint.h>
#include <stddef.h>

class StringStream : public TextStream
{
public:
	StringStream(char* buff, size_t size) ;

	void put_byte(uint8_t c) ;
	uint8_t read_byte() ;

	void left() ;

	void clear() ;

	size_t size() const ;
	const char* c_str() const ;
protected:
	char* _buff ;
	size_t _rpos ;
	size_t _wpos ;
	size_t _size ;

} ;
