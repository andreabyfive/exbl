GCCDIR = /opt/toolchain/bin
SRCDIR = src
OBJDIR = obj
OUTDIR = output
UTILDIR = ../utils


ASMS = $(OBJDIR)/mentry.o
ASMS+= $(OBJDIR)/rv_cache.o

OBJS =  $(OBJDIR)/uart.o
OBJS += $(OBJDIR)/exbl.o
OBJS += $(OBJDIR)/boot.o
OBJS += $(OBJDIR)/sfls.o
OBJS += $(OBJDIR)/ddr.o
OBJS += $(OBJDIR)/dma.o
OBJS += $(OBJDIR)/wdt.o
OBJS += $(OBJDIR)/aes.o
OBJS += $(OBJDIR)/sha.o
OBJS += $(OBJDIR)/chksum.o
OBJS += $(OBJDIR)/print.o
OBJS += $(OBJDIR)/rv_utils.o
OBJS += $(OBJDIR)/uart_regcontrol.o

#
#
#
include config.mk

sw_hex = $(OUTDIR)/exbl.bin

all: clean  $(sw_hex)


.PRECIOUS: $(OUTDIR)/%.elf $(OUTDIR)/%.dis $(OUTDIR)/%.bin

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/* $(OUTDIR)/*

cp_reg:
	make -C ../../REG_GEN
	cp ../../REG_GEN/reg.h ./src

