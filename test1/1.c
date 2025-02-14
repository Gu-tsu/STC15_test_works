#include<STC15Fxxxx.h>
#define ON 0;
#define OFF 1;
sbit led1=P3^0;
sbit led2=P3^1;
sbit led3=P4^6;
sbit led4=P4^7;
sbit led5=P1^6;
sbit led6=P1^7;
void delay(unsigned int xms)				
{
	unsigned int i,j;
	for(i=xms;i>0;i--)		      
		for(j=110;j>0;j--);
}
void main()
{
  while(1)
  {

		P1M1=0;P1M0=0;
		
		led1=ON;
		delay(2000);
		led1=OFF;

		led2=ON;
		delay(2000);
		led2=OFF;

		led3=ON;
		delay(2000);
		led3=OFF;

		led4=ON;
		delay(2000);
		led4=OFF;
		
		led5=ON;
		delay(2000);
		led5=OFF;

		led6=ON;
		delay(2000);
		led6=OFF;

		led5=ON;
		delay(2000);
		led5=OFF;

		led4=ON;
		delay(2000);
		led4=OFF;

		led3=ON;
		delay(2000);
		led3=OFF;

		led2=ON;
		delay(2000);
		led2=OFF;
		
  }
}


