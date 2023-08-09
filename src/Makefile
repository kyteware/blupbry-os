# makefile based on the makefiles/4-example note.
#
# while there's many more lines, they just do the stuff that is
# already in the 4-example makefile: nothing special.
#
# what's different:
#  - we are cross-compiling, so more steps to go from .elf->.bin.
#  - similarly: there are more tools and make VAR names for them.
#  - we adopt the convention that any file whose name starts with 
#     a number is a test program ("[0-9]-*.c")

PROG_SRC = kernel.c
PROG_OBJS = $(PROG_SRC:.c=.o)
PROGS = $(PROG_SRC:.c=.bin)

# we give you these.
LIBPI_OBJS = gpio.o delay.o timer-interrupt.o
ASM_SRC = start.S $(filter-out start.S, $(wildcard *.S))
ASM_OBJS = $(ASM_SRC:.S=.o)

# make sure to compute dependencies for all source files.
all_objs = $(PROG_OBJS) $(LIBPI_OBJS) $(ASM_OBJS)
dep = $(all_objs:.o=.d)

# linker script to lay out the executable (the .bin that runs on the pi)
MEMMAP := ./memmap

# recompile everything if Makefile changes.
DEPS := ./Makefile

# the different tools we use.
ARM = arm-none-eabi
CC = $(ARM)-gcc
LD  = $(ARM)-ld
AS  = $(ARM)-as
OD  = $(ARM)-objdump
OCP = $(ARM)-objcopy
AR  = $(ARM)-ar

# The gcc compiler flags
#    -Wall: warn about a bunch of suss things.
#    -Werror = must fix errors
#    -O: optimize (which allows for more -Wall error checking)
CFLAGS = -O -Wall -Wno-unused-variable -Werror \
         -MMD\
          -nostdlib -nostartfiles -ffreestanding  -march=armv6 -std=gnu99  

# the assembler flags (for start.S)
ASFLAGS = --warn --fatal-warnings -mcpu=arm1176jzf-s -march=armv6zk

all:  $(PROGS)

# include the generated dependency rules.
# open up a .d file in your editor to see 
# why this works!
-include $(dep)

#####################################################################
# all the pattern matching rules to make the 
# different file types.

%.o: %.c $(DEPS)
	echo "converting c to o"
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S $(DEPS)
	echo "converting s to o"
	$(AS) -c $(ASFLAGS) $< -o $@

# rules to generate .elf->.list->.bin
%.elf: %.o $(LIBPI_OBJS) $(ASM_OBJS) $(MEMMAP) $(DEPS) 
	echo "converting o to elf"
	$(CC) $(CFLAGS) $(ASM_OBJS) $< $(LIBPI_OBJS) -T $(MEMMAP) -o $@ 

%.list: %.elf
	$(OD) -D  $< > $@

%.bin: %.list
	echo "converting list to bin"
	$(OCP) $*.elf -O binary $*.bin

clean:
	rm -rf *.o *.bin *~ tags *.elf *.list *.d Makefile.bak 

.PHONY: all clean 
# stop make from deleting these suffix'd files.
.PRECIOUS: %.list %.elf %.o
