#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include<avr/interrupt.h>
#define CLK 16000000L

#define D0 eS_PORTB0
#define D1 eS_PORTB1
#define D2 eS_PORTB2
#define D3 eS_PORTB3
#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTA6
#define EN eS_PORTA7

#include "lcd.h"
#include "keypad.h"

int main(void)
{
	unsigned char i;
	DDRB = 0xFF;
	DDRA = 0xFF;
	
	Lcd8_Init();
	Lcd8_Set_Cursor(0,1);
	
	keypad_init();
	while(1)
	{
		i = key_scan();
		if(i != 255){ 
			i=i+48;
			Lcd8_Write_Char(i);
    }  
    }
}