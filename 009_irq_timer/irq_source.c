#include "s3c2440.h"
#include "uart.h"

void timer_init(void)
{
	/*
	*step1.Set timer clk
	*	Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}
	*step2.Set initial count value and compare value
	*step3.Manual load and then clear this bit
	*step4.Auto relaod and start timer0
	*/

	TCFG0 |= 99;
	TCFG1 = ((TCFG1 & (~0xf)) | 3);
	TCNTB0 = 31250;
	TCMPB0 = 0;
	TCON |= (1 << 1);
	TCON &= ~(1 << 1);
	TCON |= ((1 << 3) | (1 << 0));
}

void key_eint_init(void)
{
	GPFCON &= ~((3 << 0) | (3 << 4)); /*set GPF0 GPF2 as int pin*/
	GPFCON |= ((2 << 0) | (2 << 4));

	GPGCON &= ~((3 << 6) | (3 << 22));/*set GPG3 GPG11 as int pin*/
	GPGCON |= ((2 << 6) | (2 << 22));

	EXTINT0 |= ((7 << 0) | (7 << 8));
	EXTINT1 |= (7 << 12);/*set eint11 both edge trigger*/
	EXTINT2 |= (7 << 12);/*set eint19 both edge trigger*/

	EINTMASK &= ~((1 << 11) | (1 << 19));
}

void eint0_handle(void)
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

void eint2_handle(void)
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

void eint8_23_handle(void)
{
	if(EINTPEND & (1 << 11))//eint11
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
	else if(EINTPEND & (1 << 19))//eint19
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



volatile unsigned int t_jiffies = 0;
void int_timer0_handle(void)
{
//	t_jiffies ++;
//	print(t_jiffies);
//	puts("\n");
//	printf("t_jiffies = 0x%x\n",t_jiffies);
	//puts("\n");
	GPFDAT = ((GPFDAT & (~(7 << 4))) | (~(t_jiffies << 4)));
}

void irq_source_init(void)
{
	key_eint_init();
//	timer_init();

	irq_register(0,eint0_handle);
	irq_register(2,eint2_handle);
	irq_register(5,eint8_23_handle);
//	irq_register(10,int_timer0_handle);
}



