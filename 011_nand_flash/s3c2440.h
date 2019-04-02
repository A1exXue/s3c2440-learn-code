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
#define GPGCON			__REG(0x56000060)
#define GPGDAT			__REG(0x56000064)

#define EXTINT0			__REG(0x56000088)
#define EXTINT1			__REG(0x5600008c)
#define EXTINT2			__REG(0x56000090)
#define EINTMASK		__REG(0x560000a4)
#define EINTPEND		__REG(0x560000a8)

#define SRCPND			__REG(0X4A000000)
#define INTMSK			__REG(0X4A000008)
#define INTPND			__REG(0X4A000010)
#define INTOFFSET		__REG(0x4A000014)
#define BWSCON			__REG(0x48000000)

#define BANKCON6		__REG(0x4800001C)
#define REFRESH			__REG(0x48000024)
#define BANKSIZE		__REG(0x48000028)
#define MRSRB6 			__REG(0x4800002C)

#define TCFG0			__REG(0x51000000)
#define TCFG1			__REG(0x51000004)
#define TCON			__REG(0x51000008)
#define TCNTB0			__REG(0x5100000C)
#define TCMPB0			__REG(0x51000010)
#define TCNTO0			__REG(0x51000014)

#define NFCONF			__REG(0x4E000000)
#define NFCONT			__REG(0x4E000004)
#define NFCMMD			__REG_BYTE(0x4E000008)
#define NFADDR			__REG_BYTE(0x4E00000C)
#define NFDATA			__REG_BYTE(0x4E000010)
#define NFMECCD0		__REG(0x4E000014)
#define NFMECCD1		__REG(0x4E000018)
#define NFSECCD			__REG(0x4E00001C)
#define NFSTAT			__REG(0x4E000020)
#define NFESTAT0		__REG(0x4E000024)
#define NFESTAT1		__REG(0x4E000028)
#define NFMECC0			__REG(0x4E00002C)
#define NFMECC1                 __REG(0x4E000030)
#define NFSECC			__REG(0x4E000034)
#define NFSBLK			__REG(0x4E000038)
#define NFEBLK			__REG(0x4E00003C)












#endif

