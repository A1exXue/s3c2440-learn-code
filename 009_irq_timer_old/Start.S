.text
.global _start



_start:
	b _reset			/*vector 0x00 : reset exception*/
	ldr pc, _und_exception		/*vector 0x04 : undefine instruction exception*/
	ldr pc, _swi_exception		/*vector 0x08 : software interrupt exception*/
	b halt				/*vector 0x0c : prefetch abort exception*/
	b halt				/*vector 0x10 : data abort exception*/
	b halt				/*vector 0x14 : resvered*/
	ldr pc, _irq_exception		/*vector 0x18 : irq*/
	b halt				/*vector 0x1c : fiq*/

_und_exception:
	.word _und_exception_fun
_swi_exception:
	.word _swi_exception_fun
_irq_exception:
	.word _irq_exception_fun
.align 4
_irq_exception_fun:
	ldr sp,=0x33d00000
	sub lr,lr,#4
	stmdb sp!,{r0-r12,lr}
	bl irq_handle
	ldmia sp!,{r0-r12,pc}^

.align 4
_swi_exception_fun:
	ldr sp,=0x33e00000
	stmdb sp!,{r0-r12,lr}
	sub r4,lr,#4
	ldr r0,[r4]
	bic r0,r0,#0xff000000
	bl print
	ldr r0,=_enter_string
	bl puts

	ldr r0,=_swi_string
	bl puts
	mrs r0,cpsr
	bl print
	ldr r0,=_enter_string
	bl puts
	ldmia sp!,{r0-r12,pc}^
_swi_string:
	.string "swi exception\n"


.align 4
_und_exception_fun:
	ldr sp,=0x33f00000
	stmdb sp!,{r0-r12,lr}
	ldr r0,=_und_string
	bl puts
	mrs r0,cpsr
	bl print
	ldr r0,=_enter_string
	bl puts
	ldmia sp!,{r0-r12,pc}^
_und_string:
	.string "undefine exception\n"
_enter_string:
	.string "\n"

.align 4
_reset:
	ldr r0,=0x53000000
	mov r1,#0
	str r1,[r0]

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

	mov r1,#0
	ldr r0,[r1]
	str r1,[r1]
	ldr r2,[r0]
	cmp r1,r2
	ldr sp,=0x40000000+4096 /*nand flash*/
	moveq sp,#4096 /*nor flash*/
	streq r0,[r1]


	bl sdram_init
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
	
	ldr pc,=__sdram /*go to sdram*/
__sdram:
	bl uart0_init
	
	/*
	ldr r0,=_test_string
	bl puts
	mrs r0,cpsr
	bl print
	ldr r0,=_enter_string
	bl puts
	*/

	ldr r0,=_ch_mode_string
	bl puts

	mrs r0,cpsr
	bic r0,r0,#0xf
	bic r0,r0,#(1 << 7)
	msr cpsr,r0
	ldr sp,=0x34000000
	bl print
	ldr r0,=_enter_string
	bl puts


	ldr r0,=_deadcode_string
	bl puts
	.word 0xdeadc0de
	
	ldr r0,=_swicode_string
	bl puts
	swi #123
	
	ldr r0,=_main_string	
	bl puts

	ldr pc,=main

.align 4
halt:
	b halt

.align 4
_test_string:
	.string "test1\n"
.align 4
_ch_mode_string:
	.string "now jump to usr mode\n"
.align 4
_deadcode_string:
	.string "dead code\n"
.align 4
_swicode_string:
	.string "swi code\n"
.align 4
_main_string:
	.string "now jump to main\n"


	
	

	


