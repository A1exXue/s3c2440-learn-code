#include "uart.h"
#include "s3c2440.h"
#include "mem.h"
int main(void)
{
	unsigned char c;
	unsigned char i;
	unsigned int led_cnt = 0;
	led_init();
	uart0_init();
	GPFDAT &=~(1 << 5);
	puts("Hello world!\n\r");
	GPFDAT &= ~(1 << 6);
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



