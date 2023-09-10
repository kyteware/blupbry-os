/*
 * use interrupts to implement a simple statistical profiler.
 *	- interrupt code is a replication of ../timer-int/timer.c
 *	- you'll need to implement kmalloc so you can allocate 
 *	  a histogram table from the heap.
 *	- implement functions so that given a pc value, you can increment
 *	  its associated count
 */
#include "rpi.h"
#include "timer-interrupt.h"

// defines C externs for the labels defined by the linker script
// libpi/memmap.
// 
// you can use these to get the size of the code segment, data segment,
// etc.
#include "memmap.h"


/***************************************************************************
 * gprof implementation:
 *	- allocate a table with one entry for each instruction.
 *	- gprof_init(void) - call before starting.
 *	- gprof_inc(pc) will increment pc's associated entry.
 *	- gprof_dump will print out all samples.
 */


volatile uint32_t *gprof_table;
uint32_t gprof_table_size = 0;

// allocate table.
//    few lines of code
static unsigned gprof_init(void) {
    gprof_table_size = (uint32_t)__code_end__ - (uint32_t)__code_start__;
    printk("CODE start: %p\ncode end: %p\nCODE size: %x\n", __code_start__, __code_end__, gprof_table_size);
    gprof_table = kmalloc(gprof_table_size * 4);
    for (int i=0; i<gprof_table_size; i++) {
        gprof_table[i] = 0;
    }
    gprof_table[5]=5;
    return 0;
}

// increment histogram associated w/ pc.
//    few lines of code
static void gprof_inc(unsigned pc) {
    uint32_t index;
    dev_barrier();
    index = pc - (uint32_t)__code_start__;
    gprof_table[index] = gprof_table[index] + 1;
    //if (index > gprof_table_size) { printk("YIKES: %d < %d (%p)\n", gprof_table_size, index, pc); }
    dev_barrier();
}

// print out all samples whose count > min_val
//
// make sure sampling does not pick this code up!
static void gprof_dump(unsigned min_val) {
    printk("pc: count\n----------\n");
    for (int i=0; i<gprof_table_size; i++) {
        uint32_t val = gprof_table[i];
        if (val > min_val) {
            printk("%p: %d\n", (uint32_t)i + (uint32_t)__code_start__, val);
        }
    }
}


/***********************************************************************
 * timer interrupt code from before, now calls gprof update.
 */
// Q: if you make not volatile?
static volatile unsigned cnt;
static volatile unsigned period;

// client has to define this.
void interrupt_vector(unsigned pc) {
    dev_barrier();
    unsigned pending = GET32(IRQ_basic_pending);

    // if this isn't true, could be a GPU interrupt (as discussed in Broadcom):
    // just return.  [confusing, since we didn't enable!]
    if((pending & RPI_BASIC_ARM_TIMER_IRQ) == 0)
        return;
    /* 
     * Clear the ARM Timer interrupt - it's the only interrupt we have
     * enabled, so we want don't have to work out which interrupt source
     * caused us to interrupt 
     *
     * Q: if we delete?
     */
    PUT32(arm_timer_IRQClear, 1);
    cnt++;

    // increment the counter for <pc>.
    gprof_inc(pc);

    // this doesn't need to stay here.
    static unsigned last_clk = 0;
    unsigned clk = timer_get_usec();
    period = last_clk ? clk - last_clk : 0;
    last_clk = clk;
	
    // Q: if we put a print statement?
}

// trivial program to test gprof implementation.
// 	- look at output: do you see weird patterns?
void notmain() {
    printk("about to install handlers\n");
    int_init();

    printk("setting up timer interrupts\n");
    // Q: if you change 0x100?
    timer_interrupt_init(0x10);

    printk("gonna enable ints globally!\n");

    // Q: if you move these below interrupt enable?
    uint32_t oneMB = 1024*1024;
    kmalloc_init_set_start((void*)oneMB, oneMB);
    gprof_init();

    // Q: if you don't do?
    printk("gonna enable ints globally!\n");
    system_enable_interrupts();
    printk("enabled!\n");

    // enable_cache(); 	// Q: what happens if you enable cache?
    unsigned iter = 0;
    while(cnt<2000) {
        printk("iter=%d: cnt = %d, period = %dusec, %x\n",
                iter,cnt, period,period);
        iter++;
        if(iter % 100 == 0)
            gprof_dump(0);
    }
    clean_reboot();
}
