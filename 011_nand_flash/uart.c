#include "s3c2440.h"
#include "led.h"
#include "uart.h"
#include "string.h"
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


int gets(char *s)
{
	*s = 0;
	while(1)
	{
		*s = getchar();
		if(*s == '\n' || *s == '\r')
		{
			*s = '\0';
			break;
		}
		s ++;
	}
	return 0;
}

int key_gets(char *s)
{
	int len;
	while(1)
	{
		*s = getchar();
		len ++;
		putchar(*s);
		if(*s == '\n')
		{
			*s = '\0';
			putchar('\r');
			break;
		}
		else if(*s == '\r')
		{
			*s = '\0';
			putchar('\n');
			break;
		}
		s ++;
	}
	return len;
}


int key_getuint(void)
{
	int value = 0;
	char str[32];
	char *s = str;
	while(1)
	{
		*s = getchar();
		putchar(*s);
		if(*s == '\n')
		{
			*s = '\0';
			putchar('\r');
			break;
		}
		else if(*s == '\r')
		{
			*s = '\0';
			putchar('\n');
			break;
		}
		s ++;
	}
	str2int(str,&value);
	return value;
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
void printhex(unsigned int num,char pre_char,char format_width)
{
	int i,num_temp;
	int offset;
	char pre_char_flag = 1,start_flag = 0;
	//puts("0x");
	if(pre_char == 0)
		pre_char_flag = 0;
	if(format_width == 0)
		offset = 28;
	else 
		offset = (format_width - 1)<< 2;
	for(i = offset;i >= 0;i -= 4)
	{
		num_temp = ((num >> i) & 0xf);
		if(num_temp >= 0 && num_temp <= 9)
		{
			if((num_temp == 0) && pre_char_flag)
			{
				putchar(pre_char);
				start_flag = 1;
			}
			else
			{
				if(start_flag == 0)
				{
					if(i != 0)
					{
						if(num_temp == 0)
							if(format_width == 0)
								continue;
					}
				}
				if(num_temp != 0)
					start_flag = 1;
				pre_char_flag = 0;
				putchar((num_temp + '0'));
			}
		}
		else if(num_temp >= 10 && num_temp <= 15)
		{
			start_flag = 1;
			pre_char_flag = 0;
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

void printint(unsigned int num,char pre_char,char format_width)
{
	char ascii[32];
	int i,len = 0;
	char pre_char_flag = 1,format_width_flag = 1;
	if(pre_char == 0)
		pre_char_flag = 0;
	if(format_width == 0)
		format_width_flag = 0;

	if(num <= 0x7fffffff)
	{
		while(1)
		{
			ascii[len ++] = (num % 10 + '0');
			num /= 10;

			if(num == 0)
			{
				while(format_width_flag)
				{
					if(len < format_width && pre_char_flag)
					{
						ascii[len ++] = pre_char;
					}
					else
						break;
				}
				break;
			}
			if(len == format_width && format_width_flag)
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
				while(format_width_flag)
				{   
					if(len < format_width && pre_char_flag)
					{   
						ascii[len ++] = pre_char;
					}   
					else
						break;
				}

				ascii[len ++] = '-';
				break;
			}
			if(len == format_width && format_width_flag)
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

void printuint(unsigned int num,char pre_char,char format_width)
{
	char ascii[16];
	int i,len = 0;
	char pre_char_flag = 1,format_width_flag = 1;
	if(pre_char == 0)
		pre_char_flag = 0;
	if(format_width == 0)
		format_width_flag = 0;
	while(1)
	{
		ascii[len ++] = (num % 10 + '0');
		num /= 10; 
		if(num == 0)
		{
			while(format_width_flag)
			{
				if(len < format_width && pre_char_flag)
				{
					ascii[len ++] = pre_char;
				}
				else
					break;
			}


			break;
		}
		if(len == format_width && format_width_flag)
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
	char pre_char,out_flag,format_width;
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
			out_flag = 1;
			pre_char = 0;
			format_width = 0;
			//format_index = 0;
			while(out_flag)
			{
				switch(*(format+1))
				{
					case 'd':
						if((unsigned int)p & 3)
							p = (char *)(((unsigned int)p & 0xfffffffe) + 4);
						printint(*(unsigned int *)(p),pre_char,format_width);
						p += sizeof(int);
						format ++;
						out_flag = 0;
						break;
					case 'u':
						if((unsigned int)p & 3)
							p = (char *)(((unsigned int)p & 0xfffffffe) + 4);
						printuint(*(unsigned int *)(p),pre_char,format_width);
						p += sizeof(int);
						format ++;
						out_flag = 0;
						break;
					case 'x':
						if((unsigned int)p & 3)
							p = (char *)(((unsigned int)p & 0xfffffffe) + 4);
						printhex(*(unsigned int*)(p),pre_char,format_width);
						p += sizeof(int);
						format ++;
						out_flag = 0;
						break;
					case 'c':
						putchar(*(char*)(p));
						p += 4;//??
						format ++;
						out_flag = 0;
						break;
					case 's':
						if((unsigned int)p & 3)
							p =(char *)(((unsigned int )p & 0xfffffffe) + 4);
						puts(*(char **)(p));
						p += sizeof(char *);
						format ++;
						out_flag = 0;
						break;
					default:
						switch(*(format + 2))
						{
							case 'd':
							case 'u':
							case 'x':
							case 'c':
							case 's':
								format_width = *(format + 1) - '0';
								format ++;
								//	out_flag = 0;
								break;
							default :
								//format ++;
								pre_char = *(format + 1);
								format ++;
								break;

						}
						break;
				}
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
	printf("string = %s\n,char = %c,intvalue = %d,uintvalue = %u,hexvalue = %x,char = %c\n",str,cc,value,value,value,cc);
	printf("value02u = %02u\n",value);
	printf("value02d = %02d\n",value);
	printf("value08x = %08x\n",value);
	printf("value02x = %02x\n",value);
}


#endif



