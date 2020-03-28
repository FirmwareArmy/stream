#pragma once

#include <outputstream.h>

void enable_jtag() ;
void disable_jtag() ;

extern OutputStream jtag_stream ;

#ifdef DEBUG
#	define debug(expr) jtag_stream << expr
#else
#	define debug(expr)
#endif

