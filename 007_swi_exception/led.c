#include "s3c2440.h"


void led_init(void)
{
	GPFCON = 0x5500;
	GPFDAT = 0xf0;
}

void turn_on_led(void)
{
	GPFDAT = 0x00;
}

