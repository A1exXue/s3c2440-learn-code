led:Start.S
	arm-linux-gcc -c Start.S -o Start.o
	arm-linux-ld -Ttext 0 Start.o -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
clean:
	rm *.dis *.bin *.elf *.o

.PHONY: clean
	


