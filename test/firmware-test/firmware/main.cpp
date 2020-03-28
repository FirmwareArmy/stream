#include <board.h>
#include <jtag.h>

void setup()
{
	board_init() ;

	enable_jtag() ;

//	system_interrupt_enable_global() ;
}

uint32_t i=0 ;
void loop()
{
	debug("Hello world " << i << "\n") ;
	i++ ;
}
