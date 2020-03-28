#pragma once

#include <core.h>

#include <core/PortPin.h>
#include <core/Uart.h>

// led
extern core::PortPin led ;

// jtag uart
extern core::Uart jtag_uart ;


void board_init(void) ;
