#include "s3c2440.h"
#include "led.h"
#include "uart.h"
void uart0_init(void)
{
	//LED1(ON);
	GPHCON &= ~((3 << 4) | (3 << 6));
	GPHCON |= ((2 << 4) | (2 << 6));//pin : txd 0 , Rxd0
	GPHUP &= ~((1 << 2) | (1 << 3));
				
	UCON0 = 5;//uart clk = pclk
	UBRDIV0 = 26;//baud = 115200
	ULCON0 = 3;//8n1
	GPFDAT &=~(1 << 4);
	//LED1(ON);
}
int putchar(int c)
{
	while(!(UTRSTAT0 & (1 << 2)));
	UTXH0 = (unsigned char)c;
//	LED2(ON);
}

int getchar(void)
{
	while(!(UTRSTAT0 & (1 << 0)));
	return URXH0;
//	LED4(ON);
}

int puts(const char *s)
{
	while(*s)
	{
		putchar(*s);
		s ++;
	}
}

void print(unsigned int num)
{
	int i,num_temp;
	puts("0x");
	for(i = 28;i >= 0;i -= 4)
	{
		num_temp = ((num >> i) & 0xf);
		if(num_temp >= 0 && num_temp <= 9)
		{
			putchar((num_temp + '0'));
		}
		else if(num_temp >= 10 && num_temp <= 15)
		{
			putchar((num_temp - 10 + 'a'));
		}
	}
}

void printHex(unsigned int num,DaType type)
{
	int i;
	int num_temp;
	switch(type)
	{
		case CHAR:
			i = 4;
			break;
		case SHORT:
			i = 12;
			break;
		case INT:
			i = 28;
			break;
	}
	puts("0x");
	for(;i >= 0;i -= 4)
	{
		num_temp = ((num >> i) & 0xf);
		if(num_temp >= 0 && num_temp <= 9)
		{
			putchar((num_temp + '0'));
		}
		else if(num_temp >= 10 && num_temp <= 15)
		{
			putchar((num_temp - 10 + 'a'));
		}
	}
}


