// part2: test GPIO input.
//   - if we get a signal on the input pin 21, turn the LED on.
#include "rpi.h"
#include "timer-interrupt.h"

static volatile unsigned cnt;

void interrupt_vector(unsigned pc) {
    dev_barrier();
    cnt++;
}


void notmain(void) {
    printk("bello");
    uart_init();
	
    printk("about to install handlers\n");
    int_init();

    printk("setting up timer interrupts\n");
    // Q: if you change 0x100?
    timer_interrupt_init(0x100);

    printk("gonna enable ints globally!\n");
    // Q: what happens (&why) if you don't do?
    system_enable_interrupts();
    printk("enabled!\n");

    const int led = 20;
    const int flasher = 21;
    const int input = 16;

    gpio_set_output(led);
    gpio_set_output(flasher);
    gpio_set_input(input);

    while(1) {
        if(gpio_read(input))
            gpio_set_on(led);
        else
            gpio_set_off(led);
    }
}
