key:Start.o mem.o uart.o led.o main.o interrupt.o
	arm-linux-ld -T init.lds $^ -o key.elf
	arm-linux-objcopy -O binary -S key.elf key.bin
	arm-linux-objdump -D key.elf > key.dis
clean:
	rm *.dis *.bin *.elf *.o
%.o:%.c
	arm-linux-gcc -c $< -o $@
%.o:%.S
	arm-linux-gcc -c $< -o $@
.PHONY: clean
	


