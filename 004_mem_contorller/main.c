#include "uart.h"
#include "s3c2440.h"
#include "mem.h"
int main(void)
{
	volatile unsigned char *p = ((volatile unsigned char *)(0x30000000));
	unsigned char c;
	unsigned char i;
	unsigned int led_cnt = 0;
	//uart0_init();
	//GPFDAT &=~(1 << 5);
	puts("Hello world!\n\r");
	//GPFDAT &= ~(1 << 6);
	c = 'A';
	(*(volatile unsigned int *)p) = 0x12345678;

	for(i = 0 ; i < 4;i ++)
	{
		printHex((unsigned int)(p[i]),CHAR);
		puts("\n\r");
	}

	printHex((unsigned int)(*(unsigned int *)p),INT);
	puts("\n\r");
	while(1)
	{
		c = getchar();
		if(c == '\n')
		{
			putchar('\r');
		}
		else if(c == '\r')
		{
			putchar('\n');
		}
		putchar(c);
	}
	return 0;
}



