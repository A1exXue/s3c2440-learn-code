led:start.S
	arm-linux-gcc -c start.S -o start.o
	arm-linux-ld -Ttext 0 start.o -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
clean:
	rm *.dis *.bin *.elf *.o

.PHONY: clean
	


