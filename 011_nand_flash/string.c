#include "string.h"
#include "uart.h"

int str2int(char *str,int *value)
{
	
	char value_arr[32];
	char value_len = 0;
	char flag = DECIMALISM; 
	int i;
	
	*value = 0;
	if(*str == '0' && *(str+1) == 'x')
	{
		flag = HEXADECIMAL;
		str+=2; 
	}

	while(*str)
	{
		if(*str >= '0' && *str <= '9')
		{
			value_arr[value_len ++] = *str - '0';
		}
		else if((*str >= 'a' && *str <= 'f'))
		{
			value_arr[value_len ++] = *str - 'a' + 10;
			flag = HEXADECIMAL;
		}
		else if((*str >= 'A' && *str <= 'F'))
		{
			value_arr[value_len ++] = *str - 'A' + 10;
			flag = HEXADECIMAL;
		}
		else 
		{
			if(*str == 'h' || *str == 'H')
			{
				flag = HEXADECIMAL;
			}
			else if(*str == 'o' || *str == 'O')
			{
				flag = OCTAL;
			}
			else if(*str == 'b' || *str == 'B')
			{
				flag = BINARY;
			}
			break;
		}
		str ++;

	}


	if(value_len > 0)
	{
		switch(flag)
		{
			case HEXADECIMAL:
		//		printf("hex : ");
				for(i = 0;i < value_len;i ++)
				{
		//			printf("%d ",value_arr[i]);
					*value = (*value << 4) +  value_arr[i];
				}
				break;
			case DECIMALISM:
		//		printf("dec : ");
				for(i = 0;i < value_len;i ++)
				{
		//			printf("%d ",value_arr[i]);
					*value = *value * 10 + value_arr[i];
				}
				break;
			case OCTAL:
				for(i = 0;i < value_len;i ++)
				{
					*value = (*value << 3) + value_arr[i];
				}
				break;
			case BINARY:
				for(i = 0;i < value_len;i++)
				{
					*value = (*value << 1) + value_arr[i];
				}
				break;
			
		}
		//printf("\n\r");
		return 1;
	}
	return 0;
}


