timer0:Start.o mem.o uart.o led.o main.o interrupt.o irq_source.o
	arm-linux-ld -T init.lds $^ -o timer0.elf
	arm-linux-objcopy -O binary -S timer0.elf timer0.bin
	arm-linux-objdump -D timer0.elf > timer0.dis
clean:
	rm *.dis *.bin *.elf *.o
%.o:%.c
	arm-linux-gcc -march=armv4 -c $< -o $@
%.o:%.S
	arm-linux-gcc -march=armv4 -c $< -o $@
.PHONY: clean
	


