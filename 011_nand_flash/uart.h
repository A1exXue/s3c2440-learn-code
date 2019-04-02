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
void print(unsigned int num);
int gets(char *s);
int key_gets(char *s);
int key_getuint(void);
void printHex(unsigned int num,DaType type);
int printf(const char *format,...);
void printf_test(void);
#endif



