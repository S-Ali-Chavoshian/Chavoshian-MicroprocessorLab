#include <avr/io.h>
#include <avr/interrupt.h>

int SevenSegNumber[10] = {0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 ,0b01111111 ,0b01101111};
int PORT_C_Values[4] = {0b11110111 , 0b11111011, 0b11111101, 0b11111110};
int i = 0;
int j = 0;

ISR(TIMER0_OVF_vect)
{
 j++;
 if (j > 4) {
  j = 0;
 }

 int digit = 0;
 int currentNumber = i;
 for (int tmp = j; tmp > 0; tmp--){
  currentNumber = currentNumber / 10;
 }
 digit = currentNumber % 10;

 PORTC = PORT_C_Values[j];
 PORTD = SevenSegNumber[digit];
 TCNT0 = 0xB2;
}

ISR (TIMER1_OVF_vect)
{
 i++;
 if (i > 9999) {
  i = 0;
 }
 TCNT1 = 63974;
}


int main( void )
{
 DDRD = 0xFF;
 DDRC = 0xFF;

 TCNT1 = 63974;   // for 1 sec at 16 MHz 
 TCCR1A = 0x00;
 TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
 TIMSK = (1 << TOIE1) | (1<<TOIE0);   // Enable timer1 and timer0 overflow interrupt
 TCNT0 = 0xB2;    // Load TCNT0, count for 10ms
 TCCR0 = (1<<CS02) | (1<<CS00); // Start timer0 with /1024 prescaler
 sei();
 while(1);
}