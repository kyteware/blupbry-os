// part2: test GPIO input.
//   - if we get a signal on the input pin 21, turn the LED on.
#include "rpi.h"
#include "timer-interrupt.h"
#include "asm-funcs.h"

void notmain(void) {
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

void interrupt_vector(unsigned pc) {

}
