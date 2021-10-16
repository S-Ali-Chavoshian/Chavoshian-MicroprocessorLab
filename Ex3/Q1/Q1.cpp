#include <avr/io.h>
#include <avr/interrupt.h>

int SevenSegNumber[10] = {0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 ,0b01111111 ,0b01101111};
int i = 0;
ISR (TIMER1_OVF_vect)
{
	i++;
	if (i > 9) {
		i = 0;
	}
	PORTD = SevenSegNumber[i];
    TCNT1 = 63974;
}


int main( void )
{
	DDRD=0xFF;

	TCNT1 = 63974;   // for 1 sec at 16 MHz	
	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
	TIMSK = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	sei();
	while(1);
}