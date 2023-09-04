// part2: test GPIO input.
//   - if we get a signal on the input pin 21, turn the LED on.
#include "rpi.h"
#include "gpio.h"
#include "timer-interrupt.h"

static volatile unsigned status = 0;

const int led = 20;
const int flasher = 21;
const int input = 16;

void interrupt_vector(unsigned pc) {
    dev_barrier();

    unsigned pending = GET32(IRQ_basic_pending);

    // if this isn't true, could be a GPU interrupt (as discussed in Broadcom):
    // just return.  [confusing, since we didn't enable!]
    if((pending & RPI_BASIC_ARM_TIMER_IRQ)) {
        PUT32(arm_timer_IRQClear, 1);
        dev_barrier();
        status ^= 1;
        gpio_write(21, status);
        printk("flipped\n");
    }

    if(gpio_event_detected(16)) {
        if(gpio_read(input))
            gpio_set_on(led);
        else
            gpio_set_off(led);
        gpio_event_clear(16);
    }
}


void notmain(void) {
    uart_init();
	
    printk("about to install handlers\n");
    int_init();

    printk("setting up timer interrupts\n");
    // Q: if you change 0x100?
    timer_interrupt_init(0x100000);

    printk("gonna enable ints globally!\n");
    // Q: what happens (&why) if you don't do?
    system_enable_interrupts();
    printk("enabled!\n");

    gpio_set_output(led);
    gpio_set_output(flasher);
    gpio_int_rising_edge(input);
    gpio_int_falling_edge(input);

    while(1) {
        // if(gpio_read(input))
        //     gpio_set_on(led);
        // else
        //     gpio_set_off(led);
    }
}
