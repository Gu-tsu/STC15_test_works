#include	"STC15Fxxxx.H"
#define MAIN_Fosc		22118400L	
#define DIS_DOT		0x20
#define DIS_BLACK	0x10
#define DIS_		0x11

#define		Timer0_Reload	(65536UL -(MAIN_Fosc / 1000))		
u8 code t_display[]={					
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black	 -     H    J	 K	  L	   N	o   P	 U     t    G    Q    r   M    y
	0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
	0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};	//0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

u8 code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};	
sbit	P_HC595_SER   = P4^0;	
sbit	P_HC595_RCLK  = P5^4;
sbit	P_HC595_SRCLK = P4^3;	

u8 	LED8[8];		
u8	display_index;	
u16	msecond;		

u16	Test_cnt;	
u8	SleepDelay;

void	delay_ms(u8 ms);
void	Display(void);
void 	DisplayScan(void);

void main(void)
{
	u8	i;
	
	P0M1 = 0;	P0M0 = 0;	
	P1M1 = 0;	P1M0 = 0;
	P2M1 = 0;	P2M0 = 0;	
	P3M1 = 0;	P3M0 = 0;	
	P4M1 = 0;	P4M0 = 0;	
	P5M1 = 0;	P5M0 = 0;
	P6M1 = 0;	P6M0 = 0;
	P7M1 = 0;	P7M0 = 0;	

	display_index = 0;
	for(i=0; i<8; i++)	LED8[i] = DIS_BLACK;	
	
	Test_cnt = 1000;	
	SleepDelay = 0;
	LED8[4] = 1;
	LED8[5] = 0;
	LED8[6] = 0;
	LED8[7] = 0;
	
	EA = 1;		
	while(1)
	{
		delay_ms(1);	
		DisplayScan();
		
		if(++msecond >= 500)	                                             
		{
			msecond =0;		
			Test_cnt--;			
			LED8[4] = Test_cnt / 1000;
			LED8[5] = (Test_cnt % 1000) / 100;
			LED8[6] = (Test_cnt % 100) / 10;
			LED8[7] = Test_cnt % 10;

			if(++SleepDelay >= 3)
			{
				SleepDelay = 0;

				if(INT0 && INT1)	
				{
					SleepDelay = 0;
					P_HC595_SER = 0;
					for(i=0; i<16; i++)		
					{
						P_HC595_SRCLK = 1;
						P_HC595_SRCLK = 0;
					}
					P_HC595_RCLK = 1;
					P_HC595_RCLK = 0;	

					IE1  = 0;
					IE0  = 0;	
					EX1 = 1;	
					EX0 = 1;

					IT0 = 1;	
				//	IT0 = 0;		//INT0 ??,?????	
					IT1 = 1;		//INT1 ?????		
				//	IT1 = 0;		//INT1 ??,?????	

					PCON |= 0x02;	
					_nop_();
					_nop_();
					_nop_();
				}
			}
		}
	}
} 

void  delay_ms(u8 ms)
{
     u16 i;
	 do{
	      i = MAIN_Fosc / 12000;
		  while(--i)	;   
     }while(--ms);
}


void INT0_int (void) interrupt INT0_VECTOR	
{
	EX0 = 0;	
	IE0 = 0;
}

void INT1_int (void) interrupt INT1_VECTOR	
{
	EX1 = 0;	
	IE1 = 0;	
}

void Send_595(u8 dat)
{		
	u8	i;
	for(i=0; i<8; i++)
	{
		dat <<= 1;
		P_HC595_SER   = CY;
		P_HC595_SRCLK = 1;
		P_HC595_SRCLK = 0;
	}
}
void DisplayScan(void)
{	
	Send_595(~T_COM[display_index]);				
	Send_595(t_display[LED8[display_index]]);	
	P_HC595_RCLK = 1;
	P_HC595_RCLK = 0;						
	if(++display_index >= 8)	display_index = 0;	
}







