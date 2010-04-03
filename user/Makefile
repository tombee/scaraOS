GCC    := $(CROSS_COMPILE)gcc
CC     := $(CROSS_COMPILE)gcc
LD     := $(CROSS_COMPILE)ld
AR     := $(CROSS_COMPILE)ar
STRIP  := $(CROSS_COMPILE)strip
TOPDIR :=  .

.PHONY: all clean boot_floppy
TARGET: all

LDFLAGS := -melf_i386 -nostdlib -N --strip-all
CFLAGS  := -pipe -ggdb -Os -Wall -ffreestanding -fno-stack-protector \
	-Wsign-compare -Wcast-align -Waggregate-return \
	-Wstrict-prototypes -Wmissing-prototypes \
	-Wmissing-declarations -Wmissing-noreturn \
	-Wmissing-format-attribute -m32 \
	-I$(TOPDIR)/../include $(EXTRA_DEFS)

%.o: %.c Makefile
	@echo " [C] $@"
	@$(GCC) $(CFLAGS) -c -o $@ $<
%.o: %.S Makefile
	@echo " [ASM] $@"
	@$(GCC) $(CFLAGS) -D__ASM__ -c -o $@ $<
%.a:
	@echo " [AR] $@"
	@$(AR) crs $@ $^
%.d: %.c Makefile
#	@echo " [DEP:C] $@"
	@$(GCC) $(CFLAGS) -MM $< -MF $@ -MT $(patsubst %.d, %.o, $@)
%.d: %.S Makefile
#	@echo " [DEP:ASM] $@"
	@$(GCC) $(CFLAGS) -MM $< -MF $@ -MT $(patsubst %.d, %.o, $@)

C_RUNTIME := crt0.a
CRT_ASM_SOURCES := _crt0.S
CRT_C_SOURCES := _exit.c
CRT_OBJ :=  $(patsubst %.S, %.o, $(CRT_ASM_SOURCES)) \
		$(patsubst %.c, %.o, $(CRT_C_SOURCES))
$(C_RUNTIME): $(CRT_OBJ)

INIT_C_SOURCES := init.c
INIT_OBJ := $(patsubst %.c, %.o, $(INIT_C_SOURCES))
init: $(INIT_OBJ) $(C_RUNTIME)
	@echo " [LINK] $@"
	@$(LD) $(LDFLAGS) -o $@ $^

ALL_TARGETS := $(C_RUNTIME) init

ALL_OBJ := $(CRT_OBJ) $(INIT_OBJ)
ALL_ASM := $(CRT_ASM_SOURCES)
ALL_C   := $(CRT_C_SOURCES) $(INIT_C_SOURCES)

ALL_DEP :=  $(patsubst %.S, %.d, $(ALL_ASM)) \
		$(patsubst %.c, %.d, $(ALL_C) )

ifneq ($(MAKECMDGOALS),clean)
include $(ALL_DEP)
endif

all: Makefile $(ALL_TARGETS)

clean:
	rm -f $(ALL_OBJ) $(ALL_DEP) $(ALL_TARGETS)