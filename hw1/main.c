#include "reg51.h"
#define TIMS 3036
sfr AUXR  =0x8E;
sfr AUXR2 =0x8F;
sfr CLK_DIV	=	0x97;

sfr P4	= 0xC0;
sfr P1M1 = 0x91;	
sfr P1M0 = 0x92;	

sbit led0=P4^6;
sbit led1=P4^7;
sbit led2=P1^6;
sbit led3=P1^7;

int m=0;

void timer_0() interrupt 1
{
		m++;
}
main()
{
	P1M1=0;P1M0=0;
	
	CLK_DIV=0x04;
	TL0=TIMS;
	TH0=TIMS>>8;
	AUXR&=0x7F;
	AUXR2|=0x01;
	TMOD=0x00;
	TR0=1;
	ET0=1;
	EA=1;
	while(1)
	{
		if(m>3)
			m=0;
		switch(m)
		{
			case 0:
				led0=0;
				led3=1;
			break;
			case 1:
				led1=0;
				led0=1;
			break;
			case 2:
				led2=0;
				led1=1;
			break;
			case 3:
				led3=0;
				led2=1;
			break;
		}
}
}