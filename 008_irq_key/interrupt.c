#include "s3c2440.h"
#include "uart.h"

void irq_source_init(void)
{
	GPFCON &= ~((3 << 0) | (3 << 4)); /*set GPF0 GPF2 as int pin*/
	GPFCON |= ((2 << 0) | (2 << 4));

	GPGCON &= ~((3 << 6) | (3 << 22));/*set GPG3 GPG11 as int pin*/
	GPGCON |= ((2 << 6) | (2 << 22));
	
	EXTINT0 |= ((7 << 0) | (7 << 8));
	EXTINT1 |= (7 << 12);/*set eint11 both edge trigger*/
	EXTINT2 |= (7 << 12);/*set eint19 both edge trigger*/

	EINTMASK &= ~((1 << 11) | (1 << 19));

	/*EINTPEND can be used to distinguish int soerce*/
}

void irq_controller_init(void)
{
	INTMSK &= ~((1) | (1 << 2) | (1 << 5));
}


void irq_handle(void)
{
//	puts("irq_handle\n");
	int bit = INTOFFSET;
	if(bit == 0)
	{
		if(GPFDAT & (1 << 0))
		{
		 	GPFDAT |= (1 << 4);
		}
		else
		{
			GPFDAT &= ~(1 << 4);
		}
	}
	else if(bit == 2)
	{
		if(GPFDAT & (1 << 2))
		{
			GPFDAT |= (1 << 5);
		}
		else
		{
			GPFDAT &= ~(1 << 5);
		}
	}
	else if(bit == 5)
	{
		if(EINTPEND & (1 << 11))
		{
			if(GPGDAT & (1 << 3))
			{
				GPFDAT |= (1 << 6);
			}
			else
			{
				GPFDAT &= ~(1 << 6);
			}
			EINTPEND |= (1 << 11);
		}
		else if(EINTPEND & (1 << 19))
		{
			if(GPGDAT & (1 << 11))
			{
				GPFDAT |= (7 << 4);
			}
			else
			{
				GPFDAT &= ~(7 << 4);
			}
			EINTPEND |= (1 << 19);
		}
		else
			EINTPEND |= EINTPEND;
	}

	/*clear irq : clear from source*/
	SRCPND |= (1 << bit);
	INTPND |= (1 << bit);
}



