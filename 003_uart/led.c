#include "s3c2440.h"


void led_init(void)
{
	GPFCON = 0x5500;
	GPFDAT = 0xf0;
}



