/*
 * TrafficLights.c
 *
 * Created: 19-Apr-22 1:52:52 PM
 *  Author: ezz_a
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "DIO.h"
#define F_CPU 8000000UL
#define STOP_TIME 15
#define READY 5
#define GO_TIME 15


volatile int counter = 0;
void _VECTOR(10) (void) __attribute__ ((signal,used));


int main(void)
{
	LCD_vInit();
	sei();
	timer0_CTC_init_intr();
	DIO_vSetPinDir('D',0,1);
	DIO_vSetPinDir('D',1,1);
	DIO_vSetPinDir('D',2,1);
	int time;
	char display;
	LCD_vSend_string("TIME: ");
    while(1)
    {
		time = counter/100;
		if(time < STOP_TIME)
		{
			display = STOP_TIME - time;
			DIO_vWrite('D',2,0);
			DIO_vWrite('D',0,1); //red led on
			LCD_movecursor(1,6);
			LCD_vSend_char(display/10 + 48);
			LCD_vSend_char(display%10 + 48);
		}
		
		else if(time < STOP_TIME+READY)
		{
			display = READY - (time - STOP_TIME);
			DIO_vWrite('D',0,0); //red led off
			DIO_vWrite('D',1,1); //yello led on
			LCD_movecursor(1,7);
			LCD_vSend_char(display%10 + 48);
		}
		
		else if(time < GO_TIME+READY+STOP_TIME)
		{
			display = GO_TIME - (time - READY - STOP_TIME);
			DIO_vWrite('D',1,0);
			DIO_vWrite('D',2,1);
			LCD_movecursor(1,6);
			LCD_vSend_char(display/10 + 48);
			LCD_vSend_char(display%10 + 48);
		}
    }
	
}


void _VECTOR(10) (void)
{
	if(counter >= 3500) counter=0;
	else counter++;
}