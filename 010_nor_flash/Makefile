nor:Start.o mem.o uart.o led.o main.o interrupt.o irq_source.o nor_flash.o string.o
	arm-linux-ld -T init.lds $^ -o nor.elf
	arm-linux-objcopy -O binary -S nor.elf nor.bin
	arm-linux-objdump -D nor.elf > nor.dis
clean:
	rm *.dis *.bin *.elf *.o
%.o:%.c
	arm-linux-gcc -march=armv4 -c $< -o $@
%.o:%.S
	arm-linux-gcc -march=armv4 -c $< -o $@
cps:
	cp ../010_nor_flash /mnt/hgfs/vm_share -rf
.PHONY: clean cps
	


