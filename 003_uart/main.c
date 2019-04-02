#include "uart.h"
#include "s3c2440.h"
int main(void)
{
	unsigned char c;
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



