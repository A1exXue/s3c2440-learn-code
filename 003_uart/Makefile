led:Start.o main.o uart.o led.o
	arm-linux-ld -Ttext 0 $^ -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
clean:
	rm *.dis *.bin *.elf *.o
%.o:%.c
	arm-linux-gcc -c $< -o $@
%.o:%.S
	arm-linux-gcc -c $< -o $@
.PHONY: clean
	


