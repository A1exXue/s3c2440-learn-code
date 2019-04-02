#include "nand_flash.h"
#include "uart.h"
#include "s3c2440.h"


void nand_flash_init(void)
{
	//Initialize the timing sequence;
	NFCONF = (NFCONF&(~(7 << 8)) | (1 << 8));
	//initial ECC;Disable chip select;Enable Nand flash controller;
	NFCONT |= (1 << 4) | (1 << 1) | (1 << 0);
}

void _nand_select(void)
{
	NFCONT &= ~(1 << 1);
}

void _nand_deselect(void)
{
	NFCONT |= (1 << 1);
}

unsigned char _nand_read(void)
{
	return NFDATA;
}

void _nand_cmd(unsigned char cmd)
{
	NFCMMD = cmd;
}

void _nand_addr(unsigned char addr)
{
	NFADDR = addr;
}

void _nand_write(unsigned char data)
{
	NFDATA = data;
}

void _nand_wait_ready(void)
{
	while(!(NFSTAT & 0x1));
}

void scan_nand_flash(void)
{
	unsigned char buf[5],i;
	_nand_select();
	_nand_cmd(0x90);
	_nand_addr(0x00);
	for(i = 0;i < 5;i ++)
		buf[i] = _nand_read();
	_nand_deselect();

	printf("Maker id:%x\n\rDevice id:%x\n\r",buf[0],buf[1]);
	printf("Page size:%dKB\n\rBlock size:%dKB\n\r",(1 << (buf[2] & 0x3)),(64 << ((buf[2] >> 4) & 0x03)));
}

unsigned int nand_valid_blk_table[2048];
unsigned int nand_valid_blk_len;


void nand_valid_block_table_init(void)
{
	unsigned int page = 0;
	unsigned int block = 0;
	unsigned int block_invalid_number = 0;
	unsigned int block_valid_number = 0;
	nand_valid_blk_len = 0;
	_nand_select();
	while(1)
	{
		if(page >= 0x10000000)
		{
			break;
		}
		_nand_cmd(0x00);
		_nand_addr(2048 & 0xff); 
		_nand_addr((2048 >> 8) & 0xff);
		_nand_addr(page & 0xff); 
		_nand_addr((page >> 8) & 0xff);
		_nand_addr((page >> 16) & 0xff);
		_nand_cmd(0x30);
		_nand_wait_ready();
		if(_nand_read() != 0xff)//invalid block
		{
			block = page & (~0x1ffff);
			page = block + 0x20000;//point to next block
			block_invalid_number ++;
			continue;
		}
		else
		{
			page ++;
			if((page & 0x1ffff) > 1)//valid block
			{
				block = page & (~0x1ffff);
				nand_valid_blk_table[nand_valid_blk_len ++] = block;		
			//	printf("%x:%d\n\r",block,nand_valid_blk_len);
				page = block + 0x20000;
				block_valid_number ++;
				continue;
			}
		}
	}
	_nand_deselect();
	puts("Nand flash valid block table initial success!!\n\r");
	printf("Invalid nand flash block number is: %d\n\r",block_invalid_number);
	printf("Valid nand flash block number is: %d\n\r",block_valid_number);
}

void read_nand_flash(unsigned int addr,unsigned char *buf,unsigned int len)
{
	unsigned int page = addr / 2048;
	unsigned int col = (addr & (2048 - 1));
	unsigned int i = 0;
	_nand_select();
	
	
	while(1)
	{

		_nand_cmd(0x00);
		_nand_addr(col & 0xff);
		_nand_addr((col >> 8) & 0xff);
		_nand_addr(page & 0xff);
		_nand_addr((page >> 8) & 0xff);
		_nand_addr((page >> 16) & 0xff);
		_nand_cmd(0x30);
		_nand_wait_ready();
		for(;(col < 2048) && (i < len);col ++)
		{
			buf[i] = _nand_read();
		}
		if(i == len)
			break;

		page ++;
		col = 0;
	}
	
	

	_nand_deselect();
}


void nand_flash_test(void)
{
	char s[32];
	__attribute__((aligned(4))) unsigned char buf[2048];
	//init
	nand_flash_init();
	nand_valid_block_table_init();
	//menu
	printf("s:Scan nand flash\n\r");
	printf("r:Read nand flash\n\r");
	printf("e:erase nand flash\n\r");
	printf("w:write nand flash\n\r");
	printf("Please input your choice to test nand flash:");
	key_gets(s);

	switch(s[0])
	{
		case 's':
		case 'S':
			scan_nand_flash();
			break;
		case 'r':
		case 'R':
	//		read_nand_flash(0,);
			break;
		case 'w':
		case 'W':
			break;
		case 'e':
		case 'E':
			break;
		default :
			return;
	}


}





