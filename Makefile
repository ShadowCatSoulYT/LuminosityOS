# Makefile for tiny kernel

# compiler + linker
CC = clang
LD = ld
NASM = nasm

# flags
CFLAGS = -target i386-pc-none-elf -ffreestanding -m32 -c -O0 -fno-pic
LDFLAGS = -T linker.ld -m elf_i386 --oformat binary

# files
KERNEL = kernel.c
BOOT = boot.s
OUT = os.img

all:
	$(NASM) -f bin $(BOOT) -o boot.bin
	$(CC) $(CFLAGS) $(KERNEL) -o kernel.o
	$(LD) $(LDFLAGS) -o kernel.bin kernel.o
	cat boot.bin kernel.bin > $(OUT)
	truncate -s 1474560 $(OUT)

clean:
	rm -f *.o *.bin $(OUT)
