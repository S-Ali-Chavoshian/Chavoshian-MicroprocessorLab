#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"

int main(void)
{
  DDRD = 0xFF;
  DDRC = 0xFF;
  Lcd8_Init();
  Lcd8_Set_Cursor(1,1);
  Lcd8_Write_String("Hello World");
  while(1)
  {   
  }
  
}