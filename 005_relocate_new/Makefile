CODE_DIR=$(shell pwd)
WIN_DIR=/mnt/hgfs/vm_share/
mem:Start.o mem.o uart.o led.o main.o
	arm-linux-ld -T init.lds $^ -o mem.elf
	arm-linux-objcopy -O binary -S mem.elf mem.bin
	arm-linux-objdump -D mem.elf > mem.dis
#	echo $(CODE_DIR)
	cp $(CODE_DIR) $(WIN_DIR) -rf
clean:
	rm *.dis *.bin *.elf *.o
%.o:%.c
	arm-linux-gcc -c $< -o $@
%.o:%.S
	arm-linux-gcc -c $< -o $@
.PHONY: clean
	


