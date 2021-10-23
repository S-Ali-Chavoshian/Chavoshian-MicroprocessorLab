#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>

struct clock{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
};

char* Int_toString(uint8_t i)
{
	char str[2];
	sprintf(str, "%02d", i);
	return str;
}

void Clock_addHour(struct clock *c)
{
	if(c->hour==23)
		c->hour=0;
	else
		c->hour+=1;
	Lcd8_Set_Cursor(1,1);
	Lcd8_Write_String(Int_toString(c->hour));
}
void Clock_addMinute(struct clock *c)
{
	if(c->min==59)
	{
		Clock_addHour(c);
		c->min=0;
	}
	else
		c->min+=1;
	Lcd8_Set_Cursor(1,4);
	Lcd8_Write_String(Int_toString(c->min));
}
void Clock_addSecond(struct clock *c)
{
	if(c->sec==59)
	{
		Clock_addMinute(c);
		c->sec=0;
	}
	else
		c->sec+=1;
	Lcd8_Set_Cursor(1,7);
	Lcd8_Write_String(Int_toString(c->sec));
}
bool Clock_compare(struct clock *c1,struct clock *c2)
{
	if(c1->sec==c2->sec && c1->min==c2->min && c1->hour==c2->hour)
		return true;
	return false;
}