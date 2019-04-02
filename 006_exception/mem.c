#include "s3c2440.h"

void nor_flash_init(void)
{
	
}

void sdram_init(void)
{
	BWSCON = 0x22000000;//bit width = 32,
	BANKCON6 = 0x18001;//Trcd = 20ns = 2HCLK,column number =  9,
//	BANKCON7 = 0x18001;
	REFRESH = 0x008004f5;//Trp = 20ns = 2HCLK,Tsrc = 40ns,fresh count = 0x4f5
	
	BANKSIZE = 0xb1;//burst = 1,power dowm = 1,sclk = 1,size = 64M
	MRSRB6 = 0x30;
//	MRSRB7 = 0x30;
}

int sdram_test(void)
{
	int i;
	volatile unsigned char *p = ((volatile unsigned char *)0x30000000);
	for(i = 0;i < 100;i ++)
		p[i] = 0x55;
	for(i = 0;i < 100;i ++)
		if(p[i] != 0x55)
			return 1;
		else
			return 0;
}

void run_test(void)
{
	if(!sdram_test())
	{
		GPFDAT &= ~(1 << 5);
	}
}
