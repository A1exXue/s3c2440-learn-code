#ifndef __STRING_H__
#define __STRING_H__

typedef enum
{
	DECIMALISM = 0,
	HEXADECIMAL,
	OCTAL,
	BINARY
}number_t;


int str2int(char *str,int *value);


#endif

