#pragma once

#include <cstdint>


class Stream
{
public:
	Stream() ;

	virtual void put_byte(uint8_t c) ;
	virtual uint8_t read_byte() ;
protected:

} ;
