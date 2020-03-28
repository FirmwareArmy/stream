#include <core/PowerManager.h>
#include <core/Gclk.h>
#include <core/GclkControl.h>
#include <core/Osc8M.h>
#include <core/OscUlp32k.h>
#include <core/PortPinInterrupt.h>
#include <core/SysTick.h>
#include <core/I2c.h>

#include <interrupt_sam_nvic.h>

#include <board.h>

using pin_t=core::pin_t ;

// led
const pin_t led_pin=pin_t::PA20 ;
core::PortPin led(led_pin) ;

// jtag uart
const pin_t jtag_rx_pin=pin_t::PA04 ;
const pin_t jtag_tx_pin=pin_t::PA06 ;
const core::sercom_t jtag_sercom=core::sercom_t::Sercom0 ;
core::Uart jtag_uart(jtag_sercom) ;

void board_init(void)
{
	typedef core::PowerManager::sleep_mode_t pm_sleep_mode_t ;
	typedef core::Osc8M::prescaler_t osc8m_prescaler_t ;
	typedef core::Gclk::source_t gclk_source_t ;
	typedef core::PortPin::input_pull_t pin_input_pull_t ;
	typedef core::GclkControl::gclk_ctrl_t gclk_ctrl_t ;
	typedef core::gclk_t gclk_t ;

	/** clock bus and cpu configuration **/
	core::PowerManager::init({
		.sleep_mode			= pm_sleep_mode_t::Standby,
		.enable_EIC_clock 	= true,
		.enable_PORT_clock	= true,
		.enable_SERCOM0_clock = true,
		.enable_EVSYS_clock = true
	}) ;

	/** oscillators configuration **/
	core::Osc8M().init({
		.on_demand = true,
		.enable 	= true,
		.prescaler 	= osc8m_prescaler_t::Div1
	}) ;

	core::OscUlp32k().init({}) ;	// always on

	/** clocks configuration **/
	core::Gclk::reset() ;
	// Main clock
	core::Gclk(gclk_t::GCLK0).init({
		.source 		= gclk_source_t::OSC8M,
		.enable 		= true,
		.run_in_standby = false,
	}) ;

	// Sercom clock
	core::Gclk(gclk_t::GCLK1).init({
		.source 			= gclk_source_t::OSC8M,
		.enable 			= true,
		.run_in_standby 	= false,
	}) ;

	// 32k clock
	core::Gclk(gclk_t::GCLK2).init({
		.source 		= gclk_source_t::OSCULP32K,
		.enable 		= true,
		.run_in_standby = true,
	}) ;

	/** Peripherals configuration **/
	// configure sercom clocks
	core::GclkControl(gclk_ctrl_t::GCLK_SERCOMx_SLOW).init({
		.enable = true,
		.source = gclk_t::GCLK2		// The EIC clock source is set on the 32khz clock to allow receiving irq during standby
	}) ;
	core::GclkControl(gclk_ctrl_t::GCLK_SERCOM0_CORE).init({
		.enable = true,
		.source = gclk_t::GCLK1
	}) ;

	// configure pin interrupts
	core::PortPinInterrupt::reset() ;
	core::GclkControl(gclk_ctrl_t::GCLK_EIC).init({
		.enable = true,
		.source = gclk_t::GCLK2		// The EIC clock source is set on the 32khz clock to allow receiving irq during standby
	}) ;
	core::PortPinInterrupt::enable_interrupts(true) ;

	// shutdown all unused pins to save power
	core::Port(core::port_t::A).shutdown() ;
	core::Port(core::port_t::B).shutdown() ;

	// if the PA24 and PA25 pins are not connected, it is recommended to enable a pull-up on PA24 andPA25 through input GPIO mode. The aim is to avoid an eventually extract power consumption(<1mA) due to a not stable level on pad
	core::PortPin(pin_t::PA24).init_input({ .pull=pin_input_pull_t::PullUp }) ;
	core::PortPin(pin_t::PA25).init_input({ .pull=pin_input_pull_t::PullUp }) ;

	// init SysTick to enable synchronous time counting
	core::SysTick().init() ;

	// init led
	led.init() ;

	// init jtag uart
	jtag_uart.init({
		.rx_pin 		= jtag_rx_pin,
		.tx_pin 		= jtag_tx_pin,
		.baud_rate 		= 115200,
		.enable			= false
	}) ;

	cpu_irq_enable() ;
	// enable hard fault irq
	NVIC_EnableIRQ(HardFault_IRQn) ;
}
