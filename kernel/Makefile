# Makefile for GRUB multiboot kernel
CC = clang
LD = ld
NASM = nasm
GRUB_MKRESCUE = grub-mkrescue

# flags
CFLAGS = -target i386-pc-none-elf -ffreestanding -m32 -c -O0 -fno-pic
LDFLAGS = -T linker.ld -m elf_i386

# files
KERNEL_C = kernel.c
MULTIBOOT = multiboot.s
KERNEL_BIN = kernel.bin
ISO_DIR = iso
ISO_FILE = LuminosityOS.iso

# default: build ISO
all: iso

# build kernel with multiboot header
$(KERNEL_BIN): $(MULTIBOOT) $(KERNEL_C)
	$(NASM) -f elf32 $(MULTIBOOT) -o multiboot.o
	$(CC) $(CFLAGS) $(KERNEL_C) -o kernel.o
	$(LD) $(LDFLAGS) multiboot.o kernel.o -o $(KERNEL_BIN)

# build ISO using GRUB
iso: $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/kernel.bin
	@echo 'set timeout=0' > $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'set default=0' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'menuentry "LuminosityOS" {' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    multiboot /boot/kernel.bin' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    boot' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '}' >> $(ISO_DIR)/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o $(ISO_FILE) $(ISO_DIR)

# clean
clean:
	rm -f *.o *.bin
	rm -rf $(ISO_DIR)
	rm -f $(ISO_FILE)

.PHONY: all iso clean
