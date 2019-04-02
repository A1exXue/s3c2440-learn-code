#ifndef __S3C2440_H__
#define __S3C2440_H__

#define __REG(x)			(*(volatile unsigned int *)(x))
#define __REG_BYTE(x)		(*(volatile unsigned char *)(x))


#define GPHCON			__REG(0x56000070)
#define GPHUP			__REG(0x56000078)
#define ULCON0			__REG(0x50000000)
#define UCON0			__REG(0x50000004)
#define UTRSTAT0		__REG(0x50000010)
#define UTXH0			__REG_BYTE(0x50000020)
#define URXH0			__REG_BYTE(0x50000024)
#define UBRDIV0			__REG(0x50000028)
#define GPFCON			__REG(0x56000050)
#define GPFDAT			__REG(0x56000054)	
#define BWSCON			__REG(0x48000000)
#define BANKCON6		__REG(0x4800001C)
#define REFRESH			__REG(0x48000024)
#define BANKSIZE		__REG(0x48000028)
#define MRSRB6 			__REG(0x4800002C)



#endif

