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

#if 1
void printhex(unsigned int num)
{
	int i,num_temp;
	//puts("0x");
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

#if 0
unsigned int uint_division(unsigned int dividend,unsigned int divisor)
{
	int i = 0;
	//unsigned int value = 0;
	while(1)
	{
		if(dividend > divisor)
		{
			dividend -= divisor;
			i ++; 
		}
		else
			break;

	}
	return i;
}

unsigned int uint_remainder(unsigned int dividend,unsigned int divisor)
{
	//int i = 0;
	//unsigned int value = 0;
	while(1)
	{
		if(dividend >= divisor)
			dividend -= divisor;
		else
			break;
	}
	return dividend;
}

#endif

void printint(unsigned int num)
{
	char ascii[32];
	int i,len = 0;
	if(num <= 0x7fffffff)
	{
		while(1)
		{
			ascii[len ++] = (num % 10 + '0');
			num /= 10;

			if(num == 0)
				break;
		}
	}
	else
	{
		num = (~num + 1);
		while(1)
		{
			ascii[len ++] = (num % 10 + '0');
			num /= 10;
			if(num == 0)
			{
				ascii[len ++] = '-';
				break;
			}
		}
	}

	for(i = len - 1;i >= 0;i --)
	{
		putchar(ascii[i]);
	}
}

void printuint(unsigned int num)
{
	char ascii[16];
	int i,len = 0;
	while(1)
	{
		ascii[len ++] = (num % 10 + '0');
		num /= 10; 
		if(num == 0)
			break;
	}
	for(i = len - 1;i >= 0;i --) 
	{
		putchar(ascii[i]);
	}

}




int printf(const char *format,...)
{
	int i;
	char *p = (char *)&format;
	p = p + sizeof(char *);

	//      p = (char *)&format;
	//      p = p + sizeof(char *);

	while(*format)
	{
		if(*format != '%')
		{
			putchar(*format);
		}
		else
		{
			switch(*(format+1))
			{
				case 'd':
					if((unsigned int)p & 3)
						p = (char *)(((unsigned int)p & 0xfffffffe) + 4);
					printint(*(unsigned int *)(p));
					p += sizeof(int);
					format ++;
					break;
				case 'u':
					if((unsigned int)p & 3)
						p = (char *)(((unsigned int)p & 0xfffffffe) + 4);
					printuint(*(unsigned int *)(p));
					p += sizeof(int);
					format ++;
					break;
				case 'x':
					if((unsigned int)p & 3)
						p = (char *)(((unsigned int)p & 0xfffffffe) + 4);
					printhex(*(unsigned int*)(p));
					p += sizeof(int);
					format ++;
					break;
				case 'c':
					putchar(*(char*)(p));
					p += 4;//??
					format ++;
					break;
				case 's':
					if((unsigned int)p & 3)
						p =(char *)(((unsigned int )p & 0xfffffffe) + 4);
					puts(*(char **)(p));
					p += sizeof(char *);
					format ++;
					break;
			}
		}
		format ++;
	}
}


void printf_test(void)
{
	unsigned int value = 0xffffffff;	
	char *str = "ni hao zhong guo";
	char cc = 'C';
	printf("string = %s,char = %c,intvalue = %d,uintvalue = %u,hexvalue = %x,char = %c\n",str,cc,value,value,value,cc);
}


#endif



