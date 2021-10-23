  
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "Dig_Clock.h"

struct clock c;


int timer2_count=0;

ISR (TIMER2_OVF_vect)
{
	if(timer2_count!=122)
	{
		timer2_count++;
		return;
	}
	TCNT2=256-18;
	Clock_addSecond(&c);
	timer2_count=0;
}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	
	TCNT2= 256-18;
	TCCR2 = (1<<CS21) | (1<<CS20);
	TIMSK =(1 << TOIE2);
	sei();
	
	//init the clock
	c.sec=0;
	c.min=0;
	c.hour=0;
	
	Lcd8_Init();
	Lcd8_Set_Cursor(1,1);
	Lcd8_Write_String("00:00:00");
	while(1)
	{
    
	}
}