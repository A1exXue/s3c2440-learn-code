mem:Start.o main.o uart.o mem.o led.o
	arm-linux-ld -Ttext 0 $^ -o mem.elf
	arm-linux-objcopy -O binary -S mem.elf mem.bin
	arm-linux-objdump -D mem.elf > mem.dis
clean:
	rm *.dis *.bin *.elf *.o
%.o:%.c
	arm-linux-gcc -c $< -o $@
%.o:%.S
	arm-linux-gcc -c $< -o $@
.PHONY: clean
	


