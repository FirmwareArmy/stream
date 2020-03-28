#pragma once

#include <stream.h>


class TextStream : public Stream
{
public:
	TextStream() ;

protected:

} ;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"

TextStream& operator<<(TextStream& stream, char) ;
TextStream& operator<<(TextStream& stream, uint8_t) ;

TextStream& operator<<(TextStream& stream, const char*) ;

TextStream& operator<<(TextStream& stream, int32_t) ;
TextStream& operator<<(TextStream& stream, uint32_t) ;

/**
 * Print a float -999.99 < val < 999.99
 */
struct float3p2_float_t { float v ; } ;
float3p2_float_t float3p2(float) ;
TextStream& operator<<(TextStream& stream, float3p2_float_t) ;

/**
 * Print a number with a prefix and a unit
 * ex: 0.0154 for unit A -> prints 15.4mA
 */
struct prefix_float_t { float v ; const char* unit ; } ;
prefix_float_t prefix(float, const char* unit) ;
TextStream& operator<<(TextStream& stream, prefix_float_t) ;


struct bin8_uint32_t { uint32_t v ; } ;
bin8_uint32_t bin8(uint32_t) ;
TextStream& operator<<(TextStream& stream, bin8_uint32_t) ;

struct bin16_uint32_t { uint32_t v ; } ;
bin16_uint32_t bin16(uint32_t) ;
TextStream& operator<<(TextStream& stream, bin16_uint32_t) ;

struct bin32_uint32_t { uint32_t v ; } ;
bin32_uint32_t bin32(uint32_t) ;
TextStream& operator<<(TextStream& stream, bin32_uint32_t) ;


struct hex8_uint32_t { uint32_t v ; } ;
hex8_uint32_t hex8(uint32_t) ;
TextStream& operator<<(TextStream& stream, hex8_uint32_t) ;

struct hex16_uint32_t { uint32_t v ; } ;
hex16_uint32_t hex16(uint32_t) ;
TextStream& operator<<(TextStream& stream, hex16_uint32_t) ;

struct hex32_uint32_t { uint32_t v ; } ;
hex32_uint32_t hex32(uint32_t) ;
TextStream& operator<<(TextStream& stream, hex32_uint32_t) ;


// read opérators
TextStream& operator>>(TextStream& stream, uint32_t& v) ;
TextStream& operator>>(TextStream& stream, int32_t& v) ;

#pragma GCC diagnostic pop
