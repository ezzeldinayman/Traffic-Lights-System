/*
 * Timers.c
 *
 * Created: 19-Apr-22 1:54:33 PM
 *  Author: ezz_a
 */ 
#include "std_macros.h"
#include <avr/interrupt.h>

void timer0_CTC_init_intr()
{
	//Wave Generation mode (CTC MODE)
	SET_BIT(TCCR0,WGM01);
	//Compare Match Value
	OCR0 = 80;
	//prescaler
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS00);
	//interrupt enable
	SET_BIT(TIMSK,OCIE0);
	
}