.text
.global _start
_start:
	/*关闭看门狗*/
	ldr r0,=0x53000000
	mov r1,#0
	str r1,[r0]

	/*初始化时钟
	*1.LOCKTIME使用默认值
	*2.CLKDIVN配置HDIVN、PDIVN使得 FCLK : HCLK : PCLK = 8 : 2 : 1,即HCLK = 100Hz,PCLK = 50Hz
	*3.注意:需要设置CPU工作于异步模式
	*4.MPLLCON配置MDIV = 0x5c、PDIV = 0x1、SDIV = 0x01使得PLL输出400MHz的FCLK
	*一旦设置MPLLCON，CPU会锁定locktime直到FCLK稳定后，切换到FCLK执行(因此MPLLCON必须最后再设置)
	*/
	ldr r0,=0x4C000000
	ldr r1,=0xffffffff
	str r1,[r0]
	ldr r0,=0x4C000014
	ldr r1,=0x5
	str r1,[r0]
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000  //#R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0
	ldr r0,=0x4C000004
	ldr r1,=0x0005c011
	str r1,[r0]

	/*判断当前的flash类型,并设置sp*/
	ldr r0,=0x0
	ldr r1,=0x2
	ldr r3,[r0]		/*读出0地址处内容备份*/
	str r1,[r0]		/*向0地址中写入2*/
	ldr r2,[r0]		/*从0地址中读出修改后的内容*/
	cmp r1,r2		/*比较0地址的内容是否被修改*/
	ldr sp,=0x40000000+4096		/*不相等，则为nor启动，设置栈指针位内部SRAM的顶部地址*/
	moveq sp,#4096		/*相等，则为nand启动，设置栈指针位内部SRAM的顶部地址*/
	streq r3,[r0]		/*恢复备份*/

	/*点灯*/
	/*设置GPF4,5,6,7为输出模式*/
	ldr r0,=0x56000050
	ldr r1,=0x5500
	str r1,[r0]
	/*控制GPF4,5,6,7输出低电平*/
	ldr r0,=0x56000054
	ldr r1,=0xf0
	str r1,[r0]

	//bl main			/*跳转到C语言处执行 */
	

halt:
	b halt

	



	
	

	


