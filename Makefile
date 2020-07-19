C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

#-g Debugging symbols in gcc
CFLAGS = -g

default: osImage.bin

osImage.bin: boot/boot_sector.bin kernel.bin
	cat $^ > $@
	@echo "[INFO]: Build completed successfully"


%.bin: %.asm
	nasm -f bin $^ -o $@

kernel.bin: kernel/enter_kernel.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 --oformat binary $^

%.o: %.asm
	nasm $< -f elf -o $@

%.o: %.c ${HEADERS}#gcc doesn't meed the headers as parameters, but they're a requirement for compilation
	gcc ${CFLAGS} -ffreestanding -m32 -fno-pic -c $< -o $@


.PHONY: clean debug
clean:
	rm -f *.bin *.o *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o  

kernel.elf: kernel/enter_kernel.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^


debug: kernel.elf osImage.bin
	qemu-system-x86_64 -s -S osImage.bin &
	gdb -ex "set architecture i386:x86-64:intel" -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"
