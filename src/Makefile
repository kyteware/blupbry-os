# need the makefile to give an error if this doesn't exist
PROGS := kernel.c
COMMON_SRC := interrupts-c.c interrupts-asm.S timer-interrupt.c

# uncomment if you want it to automatically run.
RUN=1

# define this if you need to give the device for your pi
TTYUSB = 
BOOTLOADER = pi-install

include libpi/mk/Makefile.template
