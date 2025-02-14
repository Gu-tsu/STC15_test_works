#include <stdio.h>
//#include <STC15F2K60S2.H>
#include <reg52.h>
#define TIMS 3036
sfr P4 = 0xc0;//
sfr AUXR = 0x8e;
sfr AUXR2 = 0x8f;
sfr CLK_DIV = 0x97;
sfr P4M0 = 0xb4;//
sfr P4M1 = 0xb3;//

sbit P46 = P4^6;
sbit P47 = P4^7;

void timer_0() interrupt 1
{
	P46 = ~P46;
	P47 = ~P47;
}
void IO_init(void)
{
	P4M0 = 0;
	P4M1 = 0;
	P46 = 0;
	P47 = 0;
}
void timer_init(void)
{
	CLK_DIV = 0x03;
	TL0 = TIMS;
	TH0 = TIMS;//TH0 = TIMS>>8;
	AUXR &= 0x7f;
	AUXR2 |= 0x01;
	
	TMOD = 0x00;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}
void main(void)
{
	IO_init();
	timer_init();
	
	while(1);
}