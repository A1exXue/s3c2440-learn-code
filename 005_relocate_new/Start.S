.text
.global _start
_start:
	/*�رտ��Ź�*/
	ldr r0,=0x53000000
	mov r1,#0
	str r1,[r0]

	/*��ʼ��ʱ��
	*1.LOCKTIMEʹ��Ĭ��ֵ
	*2.CLKDIVN����HDIVN��PDIVNʹ�� FCLK : HCLK : PCLK = 8 : 2 : 1,��HCLK = 100Hz,PCLK = 50Hz
	*3.ע��:��Ҫ����CPU�������첽ģʽ
	*4.MPLLCON����MDIV = 0x5c��PDIV = 0x1��SDIV = 0x01ʹ��PLL���400MHz��FCLK
	*һ������MPLLCON��CPU������locktimeֱ��FCLK�ȶ����л���FCLKִ��(���MPLLCON�������������)
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
	ldr r1,=(92<<12)|(1<<4)|(1<<0)
	str r1,[r0]

	/*�жϵ�ǰ��flash����,������sp*/
	mov r1,#0
	ldr r0,[r1]
	str r1,[r1]		/*����0��ַ�����ݱ���*/
	ldr r2,[r0]		/*��0��ַ��д��2*/
	cmp r1,r2		/*�Ƚ�0��ַ�������Ƿ��޸�*/
	ldr sp,=0x40000000+4096		/*����ȣ���Ϊnor����������ջָ��λ�ڲ�SRAM�Ķ�����ַ*/
	moveq sp,#4096		/*��ȣ���Ϊnand����������ջָ��λ�ڲ�SRAM�Ķ�����ַ*/
	streq r0,[r1]		/*�ָ�����*/


	/*��ʼ��UART*/
	
	bl sdram_init
	/*relocate data*/
	ldr r1,=0
	ldr r2,=_start
	ldr r3,=__bss_start
_relocate:
	ldr r4,[r1]
	str r4,[r2]
	add r1,r1,#4
	add r2,r2,#4
	cmp r2,r3
	ble _relocate

	mov r3,#0
	ldr r1,=__bss_start
	ldr r2,=_end
_bss_relocate:
	str r3,[r1]
	add r1,r1,#4
	cmp r1,r2
	ble _bss_relocate
	
	ldr pc,=main
halt:
	b halt

	



	
	

	

