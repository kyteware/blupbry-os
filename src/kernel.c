// part2: test GPIO input.
//   - if we get a signal on the input pin 21, turn the LED on.
#include "rpi.h"
#include "gpio.h"
#include "timer-interrupt.h"

static volatile unsigned status = 0;

const int led = 20;
const int flasher = 21;
const int input = 16;

void run_user_code_asm(void (*fn)(void), void *stack);
void syscall_hello();

void user_code(void) {
    printk("entered user code\n");
    printk("calling syscall\n");
    syscall_hello();
    printk("done syscall\n");
}

void run_user_code(void (*fn)(void), void *stack) {
    assert(stack);
    demand((unsigned)stack % 8 == 0, "stack must be 8 byte aligned\n");

    run_user_code_asm(fn, stack);
    not_reached();
}

void notmain(void) {
    uart_init();
	
    printk("about to install handlers\n");
    int_init();

    printk("gonna enable ints globally!\n");
    // Q: what happens (&why) if you don't do?
    system_enable_interrupts();
    printk("enabled!\n");

    printk("running user code\n");
    uint64_t *sp = (uint64_t*)500000;
    run_user_code(user_code, sp);
    printk("doone");
    clean_reboot();
}
