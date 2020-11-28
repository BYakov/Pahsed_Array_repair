
#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _LED_H_
	#include "led.h"
#endif

void LED_Configure(void)
{
	// Clear disable B0, B1
	AT91C_BASE_PIOB->PIO_PDR = ~(AT91C_PIO_PB0 | AT91C_PIO_PB1);
	AT91C_BASE_PIOB->PIO_PER = (AT91C_PIO_PB0 | AT91C_PIO_PB1); 

	// Enable output B0, B1
	AT91C_BASE_PIOB->PIO_OER = (AT91C_PIO_PB0 | AT91C_PIO_PB1);

	// Enable write B0, B3
	AT91C_BASE_PIOB->PIO_OWER = (AT91C_PIO_PB0 | AT91C_PIO_PB1);
	AT91C_BASE_PIOB->PIO_OWDR = ~(AT91C_PIO_PB0 | AT91C_PIO_PB1);
}

void LED_toggle_red(void)
{
	unsigned int state = AT91C_BASE_PIOB->PIO_ODSR;
	if( state & AT91C_PIO_PB0 ) {
		AT91C_BASE_PIOB->PIO_ODSR = (state & ~AT91C_PIO_PB0);
	} else {
		AT91C_BASE_PIOB->PIO_ODSR = (state | AT91C_PIO_PB0);
	}
}

void LED_toggle_green(void)
{
	unsigned int state = AT91C_BASE_PIOB->PIO_ODSR;
	if( state & AT91C_PIO_PB1 ) {
		AT91C_BASE_PIOB->PIO_ODSR = (state & ~AT91C_PIO_PB1);
	} else {
		AT91C_BASE_PIOB->PIO_ODSR = (state | AT91C_PIO_PB1);
	}
}

void LED_green_on(void)
{
	AT91C_BASE_PIOB->PIO_ODSR &= ~AT91C_PIO_PB1;
}

void LED_red_on(void)
{
	AT91C_BASE_PIOB->PIO_ODSR &= ~AT91C_PIO_PB0;
}

void LED_green_off(void)
{
	AT91C_BASE_PIOB->PIO_ODSR |= AT91C_PIO_PB1;
}

void LED_red_off(void)
{
	AT91C_BASE_PIOB->PIO_ODSR |= AT91C_PIO_PB0;
}

void LED_all_toggle(void)
{
	unsigned int state = AT91C_BASE_PIOB->PIO_ODSR;
	unsigned int mask = AT91C_PIO_PB1 | AT91C_PIO_PB0;
	if( state & mask  ) {
		AT91C_BASE_PIOB->PIO_ODSR = (state & ~mask);
	} else {
		AT91C_BASE_PIOB->PIO_ODSR = (state | mask);
	}
}

void LED_toggle(int color)
{
	switch(color) {
		case LED_RED: LED_toggle_red(); break;
		case LED_GREEN: LED_toggle_green(); break;
		case LED_ALL:
			LED_toggle_red();
			LED_toggle_green(); 
		break;
	}
}
