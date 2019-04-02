#include "s3c2440.h"
#include "uart.h"
#include "string.h"

#define NOR_FLASH_BASE	0     /*nor flash --> bank0*/



void __nor_write_word(unsigned int base,unsigned int offset,unsigned short value)
{
	unsigned short *p = (unsigned short *)(base + (offset << 1));
	*p = value;
}


void nor_write_word(unsigned int offset,unsigned short value)
{
	__nor_write_word(NOR_FLASH_BASE,offset,value);
}


unsigned int __nor_read_word(unsigned int base,unsigned int offset)
{
	unsigned short *p = (unsigned short *)(base + (offset << 1));
	return *p;
}

unsigned int nor_read_word(unsigned int offset)
{
	return __nor_read_word(NOR_FLASH_BASE,offset);
}

void scan_nor_flash(void)
{
	/*1)Get the vendor ID.
	 *2)Get the device ID.
	 *3)Get the start address of each section.
	 */
	unsigned int i,j,k = 0;
	unsigned int size;
	unsigned int base = 0,vendor,device;
	unsigned int region_num,block_num,block_size;
	unsigned short string[4];
	/*get id*/
	nor_write_word(0x555,0xaa);
	nor_write_word(0x2aa,0x55);
	nor_write_word(0x555,0x90);
	vendor = nor_read_word(0);
	device = nor_read_word(1);
	nor_write_word(0,0xf0);

	printf("vendor id : 0x%02x,device id : 0x%04x\n\r",vendor,device);

	/*enter cfi mode*/
	nor_write_word(0x55,0x98);
	for(i = 0;i < 3;i ++)
	{
		string[i] = nor_read_word(0x10 + i);
	}
	string[3] = '\0';
	char s[4];
	for(i = 0;i < 4;i ++)
	{
		s[i] = (char)(string[i]);
	}
	printf("%s\n\r",s);

	/*get size*/	
	size = (1 << nor_read_word(0x27));
	printf("size = 0x%x,size = %dM\n\r",size,size / (1024 * 1024));

	/*get erase region in device*/
	region_num = nor_read_word(0x2c);
	printf("region number = %d\n\r",region_num);


	unsigned int region_base = 0x2d;
	for(j = 0;j < region_num;j ++)
	{
		block_num = nor_read_word(region_base) + (nor_read_word(region_base + 1) << 8) + 1;
		//	printf("block number in region = %d\n\r",block_num);
		block_size = (nor_read_word(region_base + 2) + (nor_read_word(region_base + 3) << 8)) * 256;
		//	printf("block size in region = %d\n\r",block_size);
		region_base += 4;

		for(i = 0;i < block_num;i ++)
		{
			//	base += block_size;
			printf("%x    ",base);
			base += block_size;
			k ++;
			if(k % 5 == 0) 
				printf("\n\r");
		}
	}
	/*exit CFI MODE*/
	nor_write_word(0x0,0xf0);
}

void read_nor_flash(void)
{
	/*get addr*/
	unsigned int addr;
	unsigned char str[32];
	unsigned int i,j;
	unsigned char *p;
	unsigned char value[16];
	printf("Please input an address:");	
	//gets(str);
	//printf("%s\n\r",str);
	//str2int(str,&addr);
	addr = key_getuint();
	printf("addr = 0x%x\n\r",addr);

	printf("Nor_data:\n\r");
	p = (unsigned char *)addr; //at cpu side

	for(i=0;i < 4;i++)
	{
		for(j=0;j < 16;j++)
		{
			value[j] = *p;
			p ++;
			printf("%02x ",value[j]);
		}

		printf("\t; ");

		for(j=0;j < 16;j++)
		{
			if(value[j] >= 0x20 && value[j] <= 0x7e)
			{
				putchar(value[j]);
			}
			else
			{
				putchar('.');
			}
		}

		printf("\n\r");
	}
}

void wait_ready(unsigned int addr)
{
	unsigned int pre,now;
	pre = nor_read_word(addr>>1);
	now = nor_read_word(addr>>1);
	while((pre & (1 << 6)) != (now & (1 << 6)))
	{
		pre = now;
		now = nor_read_word(addr>>1);
	}
}

void write_nor_flash(void)
{
	unsigned int addr,i,j,value;
	unsigned char str[32];
	unsigned char data[128];
	printf("Please input an address of sector to write:");
	addr = key_getuint();
	//printf("%s\n\r",str);
	//str2int(str,&addr);
	printf("addr = 0x%x\n\r",addr);

	printf("Please input the data to write to:");
	key_gets(data);
	printf("writing ...\n\r");
	i = 0;
	j = 1;
	while(data[i] != 0 && data[j] != 0)
	{
		value = data[i] + (data[j] << 8);
		nor_write_word(0x555,0xaa);
		nor_write_word(0x2aa,0x55);
		nor_write_word(0x555,0xa0);
		nor_write_word((addr>>1),value);
		wait_ready(addr);
		i += 2;
		j += 2;
		addr += 2;
	}

	value = data[i];
	nor_write_word(0x555,0xaa);
	nor_write_word(0x2aa,0x55);
	nor_write_word(0x555,0xa0);
	nor_write_word((addr>>1),value);
	wait_ready(addr);
	nor_write_word(0,0xf0);
}


void erase_nor_flash(void)
{
	unsigned int addr;
	unsigned char str[32];
	printf("Please input an address of sector to erase:");
	addr = key_getuint();
	printf("addr = 0x%x\n\r",addr);

	nor_write_word(0x555,0xaa);
	nor_write_word(0x2aa,0x55);
	nor_write_word(0x555,0x80);
	nor_write_word(0x555,0xaa);
	nor_write_word(0x2aa,0x55);
	nor_write_word((addr>>1),0x30);//at cpu side

	printf("erasing ...\n\r");
	wait_ready(addr);//at cpu side
	nor_write_word(0,0xf0);
}



void nor_flash_test(void)
{
	char s[32];
	printf("s:Scan nor flash\n\r");
	printf("r:Read nor flash\n\r");
	printf("e:erase nor flash\n\r");
	printf("w:write nor flash\n\r");
	printf("Please input your choice to test nor flash:");
	key_gets(s);
	//printf("%c\n\r",s[0]);
	switch(s[0])
	{
		case 's':
		case 'S':
			scan_nor_flash();
			break;
		case 'r':
		case 'R':
			read_nor_flash();
			break;
		case 'w':
		case 'W':
			write_nor_flash();
			break;
		case 'e':
		case 'E':
			erase_nor_flash();
			break;
		default :
			return;
	}
}


