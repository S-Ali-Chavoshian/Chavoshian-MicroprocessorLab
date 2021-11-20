#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#define CLK 16000000L

unsigned int i=0;

void step(int t)
{
	switch(t)
	{
		case 1:
			PORTC = 0x09;
			break;
		case 2:
			PORTC = 0x0A;
			break;
		case 3:
			PORTC = 0x06;
			break;
		case 0:
			PORTC = 0x05;
			break;
	}
}

void adc_init()
{
	DDRA = 0x00;
	ADMUX = (1<<REFS0); // AREF = AVcc
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // ADC Enable and prescaler of 128
}
uint16_t adc_read(uint8_t ch)
{
 
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch;

	ADCSRA |= (1<<ADSC); // start single conversion
 
	while(ADCSRA & (1<<ADSC));// wait for conversion to complete
	return (ADC);
}


ISR (TIMER0_OVF_vect)
{
	TCNT0= 177;
	step(i%4);
	i++;
}
int main(void)
{
	
	uint16_t adc_result0;
	int temp;
	DDRC=0xff;
	
	TCNT0= 177;
	TCCR0 = (1<<CS02) | (1<<CS00);//clk/1024
	TIMSK =(1 << TOIE0);
	sei();
	
	TCCR0 &= ~(1<<CS02);//disable timer
	TCCR0 &= ~(1<<CS00);
	
	adc_init();
	while(1)
	{
		 adc_result0 = adc_read(0);
		 temp=adc_result0/2.01; 
		if(temp > 20.0)
			TCCR0 = (1<<CS02) | (1<<CS00);//clk/1024
		else
		{
			TCCR0 &= ~(1<<CS02);//disable timer
			TCCR0 &= ~(1<<CS00);
		}
    }
}