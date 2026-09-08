# Build by Gemini, didnt wanted to make one

BUILD_DIR = build
INCLUDE_DIR = include

# All object files now output to the build/ directory
OBJECTS = $(BUILD_DIR)/loader.o \
          $(BUILD_DIR)/kmain.o \
          $(BUILD_DIR)/io.o \
          $(BUILD_DIR)/gdt.o \
          $(BUILD_DIR)/gdt_load.o \
          $(BUILD_DIR)/idt.o \
          $(BUILD_DIR)/idt_load.o \
          $(BUILD_DIR)/idt_flush.o \
          $(BUILD_DIR)/interrupt.o \
          $(BUILD_DIR)/pic.o \
          $(BUILD_DIR)/framebuffer.o \
          $(BUILD_DIR)/serial.o

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -masm=intel -I $(INCLUDE_DIR)
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
	            -b boot/grub/stage2_eltorito    \
	            -no-emul-boot                   \
	            -boot-load-size 4               \
	            -A os                           \
	            -input-charset utf8             \
	            -quiet                          \
	            -boot-info-table                \
	            -o os.iso                       \
	            iso

run: os.iso
	bochs -f bochsrc.txt -q

# --- C Source Compilation Rules ---
$(BUILD_DIR)/%.o: kernel/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: drivers/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

# --- Assembly Source Compilation Rules ---
$(BUILD_DIR)/%.o: boot/%.s
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: kernel/%.s
	@mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# --- Cleanup ---
clean:
	rm -rf $(BUILD_DIR) kernel.elf os.iso bochslog.txt com1.out