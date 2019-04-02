#ifndef __UART_H__
#define __UART_H__

typedef enum{
	CHAR = 0,
	SHORT,
	INT
}DaType;


void uart0_init(void);
int putchar(int c);
int getchar(void);
int puts(const char *s);
void printHex(unsigned int num,DaType type);
#endif



