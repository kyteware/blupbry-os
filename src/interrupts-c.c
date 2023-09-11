#include "rpi.h"
#include "rpi-interrupts.h"

// initialize global interrupt state.
void int_init(void) {
    // put interrupt flags in known state. 
    //  BCM2835 manual, section 7.5 , 112
    PUT32(Disable_IRQs_1, 0xffffffff);
    PUT32(Disable_IRQs_2, 0xffffffff);
    dev_barrier();

    /*
     * Copy in interrupt vector table and FIQ handler _table and _table_end
     * are symbols defined in the interrupt assembly file, at the beginning
     * and end of the table and its embedded constants.
     */
    extern unsigned _interrupt_table;
    extern unsigned _interrupt_table_end;

    // where the interrupt handlers go.
#   define RPI_VECTOR_START  0
    unsigned *dst = (void*)RPI_VECTOR_START,
                 *src = &_interrupt_table,
                 n = &_interrupt_table_end - src;
    for(int i = 0; i < n; i++)
        dst[i] = src[i];
}

void interrupt_vector(unsigned pc) {
    dev_barrier();

    printk("just got an interrupt!");
}

static inline uint32_t cpsr_get(void) {
    uint32_t cpsr;
    asm volatile("mrs %0,cpsr" : "=r"(cpsr));
    return cpsr;
}

// this is used for syscalls.
int software_interrupt_vector(unsigned pc, uint32_t r0) {
	uint32_t inst, sys_num, mode;
    sys_num = r0;
    uint32_t spsr;
    asm volatile("mrs %0,spsr" : "=r"(spsr));

    mode = spsr & (uint32_t)((1 << 5)-1);

    // put spsr mode in <mode>
    if(mode == 0b10000)
        panic("mode = %b: expected %b\n", mode, 0b10000);
    else
        trace("success: spsr is at user level\n");

    // we do a very trivial hello and exit just to show the difference
    switch(sys_num) {
    case 1: 
            trace("syscall: hello world\n");
            return 0;
    case 2: 
            trace("exiting!\n");
            clean_reboot();
    default: 
            printk("illegal system call = %d!\n", sys_num);
            return -1;
    }
}

#define UNHANDLED(msg,r) \
	panic("ERROR: unhandled exception <%s> at PC=%x\n", msg,r)

void fast_interrupt_vector(unsigned pc) {
	UNHANDLED("fast", pc);
}

void reset_vector(unsigned pc) {
	UNHANDLED("reset vector", pc);
}
void undefined_instruction_vector(unsigned pc) {
	UNHANDLED("undefined instruction", pc);
}
void prefetch_abort_vector(unsigned pc) {
	UNHANDLED("prefetch abort", pc);
}
void data_abort_vector(unsigned pc) {
	UNHANDLED("data abort", pc);
}
