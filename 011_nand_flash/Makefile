nand:Start.o init.o nand_flash.o uart.o led.o interrupt.o irq_source.o nor_flash.o string.o main.o
	arm-linux-ld -T init.lds $^ -o nand.elf
	arm-linux-objcopy -O binary -S nand.elf nand.bin
	arm-linux-objdump -D nand.elf > nand.dis
clean:
	rm *.dis *.bin *.elf *.o
%.o:%.c
	arm-linux-gcc -march=armv4 -c $< -o $@
%.o:%.S
	arm-linux-gcc -march=armv4 -c $< -o $@
cps:
	cp ../011* /mnt/hgfs/vm_share -rf
.PHONY: clean cps
	


