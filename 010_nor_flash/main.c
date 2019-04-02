#include "uart.h"
#include "led.h"
#include "s3c2440.h"
#include "mem.h"
#include "irq_source.h"
#include "nor_flash.h"

int main(void)
{
	unsigned char c;
	unsigned char i;
	int j = 0;
	unsigned int led_cnt = 0;
	
	puts("Hello world!\n\r");
	led_init();
	uart0_init();
	//puts("helo\n");
	//irq_source_init();
	GPFDAT &=~(1 << 5);
	//puts("Hello world!\n\r");
	
	printf_test();

	GPFDAT &= ~(1 << 6);
	while(1)
	{
		nor_flash_test();
	//	puts("HELLO WORLD\n\r");
/*		
		c = getchar();
		if(c == '\n')
		{
			putchar('\r');
		}
		else if(c == '\r')
		{
			putchar('\n');
		}
		putchar(c);*/
	}
	return 0;
}



