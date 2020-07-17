C_SOURCES = $(wildcard kernel/*.c drivers/*.h)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

default: osImage.bin

osImage.bin: boot/boot_sector.bin kernel.bin
	cat $^ > osImage.bin
	@echo "[INFO]: Build completed successfully"


%.bin: %.asm
	nasm -f bin $^ -o $@

kernel.bin: kernel/enter_kernel.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 --oformat binary $^

%.o: %.asm
	nasm $< -f elf -o $@

%.o: %.c ${HEADERS}#temporary headers for simplicity
	gcc -ffreestanding -m32 -fno-pic -c $< -o $@

.PHONY: clean
clean:
	rm -f *.bin *.o
	rm -rf kernel/*.o boot/*.bin drivers/*.o 