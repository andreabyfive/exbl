INCDIRS	=

#
# Include the make variables (CC, etc...)
#
CC           := riscv64-unknown-elf-gcc
READELF       := riscv64-unknown-elf-readelf
OBJCOPY       := riscv64-unknown-elf-objcopy
OBJDUMP       := riscv64-unknown-elf-objdump
AR            := riscv64-unknown-elf-ar
RANLIB        := riscv64-unknown-elf-ranlib
LD            := $(CC)
BIN2HEX				:= $(UTILDIR)/bin2hex
BIN2BIN				:= $(UTILDIR)/bin2bin

CFLAGS        := -Wall -D__NO_INLINE__ -mcmodel=medany -std=gnu99
CFLAGS				+= -O0 -g
CFLAGS				+= -Wno-unused -Wno-attributes -fno-delete-null-pointer-checks

LIBS          := -lgcc

LDFLAGS       := -Wl,--build-id=none -nostartfiles -static



#
# Target rules
#
$(OBJDIR)/%.o: $(SRCDIR)/%.S
	@mkdir -p $(OBJDIR)
	$(CC) -MMD -MP $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -MMD -MP $(CFLAGS) -c $< -o $@

$(OUTDIR)/%.elf: $(OBJS) $(ASMS)
	@mkdir -p $(OUTDIR)
	$(LD) $(LDFLAGS) -T linker.ld $^ -o $@

$(OUTDIR)/%.dis: $(OUTDIR)/%.elf
	$(OBJDUMP) -DSx $< > $@

$(OUTDIR)/%.bin: $(OUTDIR)/%.elf $(OUTDIR)/%.dis
	$(OBJCOPY) -O binary $< $@
#	$(BIN2BIN) $@ 16 -size_word -little > $(patsubst %.bin,%.big.bin,$@)

#$(OUTDIR)/%.hex: $(OUTDIR)/%.bin
#	$(BIN2HEX) $< 1 -size_word -little > $@
